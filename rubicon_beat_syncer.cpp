#include "rubicon_beat_syncer.h"
#include "modules/rubicon_core/rubicon_conductor.h"
#include "core/math/math_funcs.h"

void RubiconBeatSyncer::set_type(const TimeValue p_type) {
    type = p_type;
}

RubiconBeatSyncer::TimeValue RubiconBeatSyncer::get_type() const {
    return type;
}

void RubiconBeatSyncer::set_enabled(bool p_enabled) {
    enabled = p_enabled;
}

bool RubiconBeatSyncer::get_enabled() const {
    return enabled;
}

void RubiconBeatSyncer::set_value(const float p_value) {
    switch(RubiconBeatSyncer::get_type()) {
        default:
            _set_bump_measure(p_value);
            break;

        case TIME_VALUE_BEAT:
            _set_bump_measure(RubiconConductor::beats_to_measures(p_value,4.0f));
            break;

        case TIME_VALUE_STEP:
            _set_bump_measure(RubiconConductor::steps_to_measures(p_value,4.0f,4.0f));
            break;
    }
}

float RubiconBeatSyncer::get_value() const {
    switch(RubiconBeatSyncer::get_type()) {
        default:
            return _bump_measure;

        case TIME_VALUE_BEAT:
            return RubiconConductor::measure_to_beats(_bump_measure, 4.0f);

        case TIME_VALUE_STEP:
            return RubiconConductor::measure_to_steps(_bump_measure, 4.0f, 4.0f);
    }
}

void RubiconBeatSyncer::_notification(int p_notification) {
    switch(p_notification) {
        case NOTIFICATION_READY: {
            if (_initialized)
                return;

            _initialized = true;

            RubiconConductor::get_singleton()->connect(SNAME("step_hit"), callable_mp(this, &RubiconBeatSyncer::_step_hit));
            RubiconConductor::get_singleton()->connect(SNAME("time_change_reached"), callable_mp(this, &RubiconBeatSyncer::_time_change_reached));

            _time_change_reached(RubiconConductor::get_singleton()->get_current_time_change());
        }   break;
        case NOTIFICATION_PREDELETE: {
            if (!_initialized)
                return;

            RubiconConductor::get_singleton()->disconnect(SNAME("step_hit"), callable_mp(this, &RubiconBeatSyncer::_step_hit));
            RubiconConductor::get_singleton()->disconnect(SNAME("time_change_reached"), callable_mp(this, &RubiconBeatSyncer::_time_change_reached));
        }   break;
    }
}

void RubiconBeatSyncer::_step_hit(const int p_step) {
    if (!enabled)
        return;

    if ((p_step - _step_offset) % _bump_step == 0)
        emit_signal("bumped");
}

void RubiconBeatSyncer::_time_change_reached(const Ref<RubiconTimeChange> p_current_time_change) {
    if (p_current_time_change.is_null())
        return;
    
    _step_offset += _current_time_change.is_null() ? 0 : int(Math::floor((p_current_time_change->time - _current_time_change->time) * _current_time_change->time_signature_numerator * _current_time_change->time_signature_denominator));

    _current_time_change = p_current_time_change;
    _set_bump_measure(_bump_measure);
}

void RubiconBeatSyncer::_set_bump_measure(const float p_value) {
    if (!_initialized)
        _notification(NOTIFICATION_READY);
    
    _bump_measure = p_value;
    _cached_beat = RubiconConductor::measure_to_beats(_bump_measure, 4.0f);
    _cached_step = RubiconConductor::measure_to_steps(_bump_measure, 4.0f, 4.0f);

    if (_current_time_change.is_null())
        return;
    
    _bump_step = int(Math::floor(_current_time_change->time_signature_numerator * _current_time_change->time_signature_denominator * _bump_measure));
}

void RubiconBeatSyncer::_bind_methods() {
    BIND_ENUM_CONSTANT(TIME_VALUE_MEASURE);
    BIND_ENUM_CONSTANT(TIME_VALUE_BEAT);
    BIND_ENUM_CONSTANT(TIME_VALUE_STEP);

    ClassDB::bind_method(D_METHOD("set_type", "type"), &RubiconBeatSyncer::set_type);
    ClassDB::bind_method("get_type", &RubiconBeatSyncer::get_type);
    ClassDB::bind_method(D_METHOD("set_value", "value"), &RubiconBeatSyncer::set_value);
    ClassDB::bind_method("get_value", &RubiconBeatSyncer::get_value);
    ClassDB::bind_method(D_METHOD("set_enabled", "enabled"), &RubiconBeatSyncer::set_enabled);
    ClassDB::bind_method("get_enabled", &RubiconBeatSyncer::get_enabled);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "Measure,Beat,Step"), "set_type", "get_type");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "value"), "set_value", "get_value");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "enabled"), "set_enabled", "get_enabled");

    ADD_SIGNAL(MethodInfo("bumped"));
}