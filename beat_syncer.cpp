#include "beat_syncer.h"
#include "modules/rubicon_core/conductor.h"
#include "core/math/math_funcs.h"

void BeatSyncer::set_enabled(bool p_enabled) {
    enabled = p_enabled;
}

bool BeatSyncer::get_enabled() const {
    return enabled;
}

void BeatSyncer::set_type(const TimeValue p_type) {
    type = p_type;
}

BeatSyncer::TimeValue BeatSyncer::get_type() const {
    return type;
}

void BeatSyncer::_notification(int p_notification) {
    switch(p_notification) {
        case NOTIFICATION_READY: {
            if (_initialized)
                return;

            _initialized = true;

            Conductor* conductor = Conductor::get_singleton();

            conductor->connect(SNAME("step_hit"), callable_mp(this, &BeatSyncer::_step_hit));
            conductor->connect(SNAME("time_change_reached"), callable_mp(this, &BeatSyncer::_time_change_reached));

            _time_change_reached(conductor->get_current_time_change());
        }   break;
        case NOTIFICATION_PREDELETE: {
            Conductor* conductor = Conductor::get_singleton();
            conductor->disconnect(SNAME("step_hit"), callable_mp(this, &BeatSyncer::_step_hit));
            conductor->disconnect(SNAME("time_change_reached"), callable_mp(this, &BeatSyncer::_time_change_reached));
        }   break;
    }
}

void BeatSyncer::set_value(const float p_value) {
    switch(BeatSyncer::get_type()) {
        default:
            _set_bump_measure(p_value);
            break;

        case TIME_VALUE_BEAT:
            _set_bump_measure(Conductor::get_singleton()->beats_to_measures(p_value,4.0f));
            break;

        case TIME_VALUE_STEP:
            _set_bump_measure(Conductor::get_singleton()->steps_to_measures(p_value,4.0f,4.0f));
            break;
    }
}

float BeatSyncer::get_value() const {
    switch(BeatSyncer::get_type()) {
        default:
            return _bump_measure;

        case TIME_VALUE_BEAT:
            return Conductor::get_singleton()->measure_to_beats(_bump_measure, 4.0f);

        case TIME_VALUE_STEP:
            return Conductor::get_singleton()->measure_to_steps(_bump_measure, 4.0f, 4.0f);
    }
}

void BeatSyncer::_step_hit(const int p_step) {
    if (!enabled)
        return;

    if ((p_step - _step_offset) % _bump_step == 0)
        emit_signal("bumped");
}

void BeatSyncer::_time_change_reached(const Ref<TimeChange> p_current_time_change) {
    if (p_current_time_change.is_null())
        return;
    
    _step_offset += _current_time_change.is_null() ? 0 : int(Math::floor((p_current_time_change->time - _current_time_change->time) * _current_time_change->time_signature_numerator * _current_time_change->time_signature_denominator));

    _current_time_change = p_current_time_change;
    _set_bump_measure(_bump_measure);
}

void BeatSyncer::_set_bump_measure(const float p_value) {
    if (!_initialized)
        _notification(NOTIFICATION_READY);
    
    _bump_measure = p_value;
    _cached_beat = Conductor::get_singleton()->measure_to_beats(_bump_measure, 4.0f);
    _cached_step = Conductor::get_singleton()->measure_to_steps(_bump_measure, 4.0f, 4.0f);

    if (_current_time_change.is_null())
        return;
    
    _bump_step = int(Math::floor(_current_time_change->time_signature_numerator * _current_time_change->time_signature_denominator * _bump_measure));
}

void BeatSyncer::_bind_methods() {
    BIND_ENUM_CONSTANT(TIME_VALUE_MEASURE);
    BIND_ENUM_CONSTANT(TIME_VALUE_BEAT);
    BIND_ENUM_CONSTANT(TIME_VALUE_STEP);

    ClassDB::bind_method(D_METHOD("set_enabled", "enabled"), &BeatSyncer::set_enabled);
    ClassDB::bind_method("get_enabled", &BeatSyncer::get_enabled);
    ClassDB::bind_method(D_METHOD("set_type", "type"), &BeatSyncer::set_type);
    ClassDB::bind_method("get_type", &BeatSyncer::get_type);
    ClassDB::bind_method(D_METHOD("set_value", "value"), &BeatSyncer::set_value);
    ClassDB::bind_method("get_value", &BeatSyncer::get_value);
    
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "enabled"), "set_enabled", "get_enabled");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "Measure,Beat,Step"), "set_type", "get_type");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "value"), "set_value", "get_value");

    ADD_SIGNAL(MethodInfo("bumped"));
}