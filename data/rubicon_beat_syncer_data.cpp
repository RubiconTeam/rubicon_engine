#include "rubicon_beat_syncer_data.h"
#include "modules/rubicon_core/rubicon_conductor.h"

void RubiconBeatSyncerData::set_type(const TimeValue p_type) {
    type = p_type;
}

RubiconBeatSyncerData::TimeValue RubiconBeatSyncerData::get_type() const {
    return type;
}

void RubiconBeatSyncerData::set_value(const float p_value) {
    switch(RubiconBeatSyncerData::get_type()) {
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

    emit_signal(SNAME("value_changed"));
}

float RubiconBeatSyncerData::get_value() const {
    switch(RubiconBeatSyncerData::get_type()) {
        default:
            return _bump_measure;

        case TIME_VALUE_BEAT:
            return RubiconConductor::measure_to_beats(_bump_measure, 4.0f);

        case TIME_VALUE_STEP:
            return RubiconConductor::measure_to_steps(_bump_measure, 4.0f, 4.0f);
    }
}

float RubiconBeatSyncerData::get_value_as_measure() const {
    return _bump_measure;
}

void RubiconBeatSyncerData::_set_bump_measure(const float p_value) {
    _bump_measure = p_value;
    _cached_beat = RubiconConductor::measure_to_beats(_bump_measure, 4.0f);
    _cached_step = RubiconConductor::measure_to_steps(_bump_measure, 4.0f, 4.0f);
}

void RubiconBeatSyncerData::_bind_methods() {
    BIND_ENUM_CONSTANT(TIME_VALUE_MEASURE);
    BIND_ENUM_CONSTANT(TIME_VALUE_BEAT);
    BIND_ENUM_CONSTANT(TIME_VALUE_STEP);

    ClassDB::bind_method(D_METHOD("set_type", "type"), &RubiconBeatSyncerData::set_type);
    ClassDB::bind_method("get_type", &RubiconBeatSyncerData::get_type);
    ClassDB::bind_method(D_METHOD("set_value", "value"), &RubiconBeatSyncerData::set_value);
    ClassDB::bind_method("get_value", &RubiconBeatSyncerData::get_value);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "Measure,Beat,Step"), "set_type", "get_type");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "value"), "set_value", "get_value");

    ADD_SIGNAL(MethodInfo("value_changed"));
}