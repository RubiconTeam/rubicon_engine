#include "beat_syncer_data.h"
#include "modules/rubicon_core/conductor.h"

void BeatSyncerData::set_type(const TimeValue p_type) {
    type = p_type;
}

BeatSyncerData::TimeValue BeatSyncerData::get_type() const {
    return type;
}

void BeatSyncerData::set_value(const float p_value) {
    switch(BeatSyncerData::get_type()) {
        default:
            _set_bump_measure(p_value);
            break;

        case TIME_VALUE_BEAT:
            _set_bump_measure(Conductor::beats_to_measures(p_value,4.0f));
            break;

        case TIME_VALUE_STEP:
            _set_bump_measure(Conductor::steps_to_measures(p_value,4.0f,4.0f));
            break;
    }

    emit_signal(SNAME("value_changed"));
}

float BeatSyncerData::get_value() const {
    switch(BeatSyncerData::get_type()) {
        default:
            return _bump_measure;

        case TIME_VALUE_BEAT:
            return Conductor::measure_to_beats(_bump_measure, 4.0f);

        case TIME_VALUE_STEP:
            return Conductor::measure_to_steps(_bump_measure, 4.0f, 4.0f);
    }
}

float BeatSyncerData::get_value_as_measure() const {
    return _bump_measure;
}

void BeatSyncerData::_set_bump_measure(const float p_value) {
    _bump_measure = p_value;
    _cached_beat = Conductor::measure_to_beats(_bump_measure, 4.0f);
    _cached_step = Conductor::measure_to_steps(_bump_measure, 4.0f, 4.0f);
}

void BeatSyncerData::_bind_methods() {
    BIND_ENUM_CONSTANT(TIME_VALUE_MEASURE);
    BIND_ENUM_CONSTANT(TIME_VALUE_BEAT);
    BIND_ENUM_CONSTANT(TIME_VALUE_STEP);

    ClassDB::bind_method(D_METHOD("set_type", "type"), &BeatSyncerData::set_type);
    ClassDB::bind_method("get_type", &BeatSyncerData::get_type);
    ClassDB::bind_method(D_METHOD("set_value", "value"), &BeatSyncerData::set_value);
    ClassDB::bind_method("get_value", &BeatSyncerData::get_value);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "Measure,Beat,Step"), "set_type", "get_type");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "value"), "set_value", "get_value");

    ADD_SIGNAL(MethodInfo("value_changed"));
}