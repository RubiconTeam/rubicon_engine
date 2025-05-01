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
        case NOTIFICATION_READY:
            _initialized = true;

            Conductor* conductor = Conductor::get_singleton();

            conductor->connect(SNAME("step_hit"), Callable(this, "_step_hit"));
            conductor->connect(SNAME("bpm_changed"), Callable(this, "_bpm_changed"));

            _bpm_changed(conductor->get_time_changes()[conductor->get_time_change_index()]);
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

bool BeatSyncer::get_value() const {
    return value;
}

void BeatSyncer::_step_hit(const int p_step) {
    if (!enabled)
        return;

    if ((p_step - _step_offset) % _bump_step == 0){
        emit_signal("bumped");
    }
}

void BeatSyncer::_bpm_changed(const Ref<TimeChange> p_current_bpm) {
    _step_offset += _current_bpm.is_null() ? 0 : Math::floor((p_current_bpm->time - p_current_bpm->time) * p_current_bpm->time_signature_numerator * p_current_bpm->time_signature_denominator);

    _current_bpm = p_current_bpm;
    _set_bump_measure(_bump_measure);
}

void BeatSyncer::_set_bump_measure(const float p_value) {
    if (!_initialized)
        _notification(13);
    
    _bump_measure = p_value;
    _cached_beat = Conductor::get_singleton()->measure_to_beats(_bump_measure, 4.0f);
    _cached_step = Conductor::get_singleton()->measure_to_steps(_bump_measure, 4.0f, 4.0f);

    _bump_step = Math::floor(_current_bpm->time_signature_numerator * _current_bpm->time_signature_denominator * _bump_measure);
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
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "value"), "set_value", "get_value");

    ADD_SIGNAL(MethodInfo("bumped"));

    
}