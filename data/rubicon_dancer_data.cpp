#include "rubicon_dancer_data.h"
#include "beat_syncer_data.h"

void RubiconDancerData::set_time_value(const BeatSyncerData::TimeValue p_time_value) {
    time_value = p_time_value;
}

BeatSyncerData::TimeValue RubiconDancerData::get_time_value() const {
    return time_value;
}

void RubiconDancerData::set_dance_list(const PackedStringArray p_dance_list) {
    dance_list = p_dance_list;
}

PackedStringArray RubiconDancerData::get_dance_list() const {
    return dance_list;
}

void RubiconDancerData::set_time_interval(const float p_time_interval) {
    time_interval = p_time_interval;
}

float RubiconDancerData::get_time_interval() const {
    return time_interval;
}

void RubiconDancerData::set_force_dancing(const bool p_force_dancing) {
    force_dancing = p_force_dancing;
}

bool RubiconDancerData::get_force_dancing() const {
    return force_dancing;
}

void RubiconDancerData::set_reset_animation_progress(const bool p_reset_animation_progress) {
    reset_animation_progress = p_reset_animation_progress;
}

bool RubiconDancerData::get_reset_animation_progress() const {
    return reset_animation_progress;
}

void RubiconDancerData::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_time_value", "time_value"), &RubiconDancerData::set_time_value);
    ClassDB::bind_method("get_time_value", &RubiconDancerData::get_time_value);
    
    ClassDB::bind_method(D_METHOD("set_dance_list", "dance_list"), &RubiconDancerData::set_dance_list);
    ClassDB::bind_method("get_dance_list", &RubiconDancerData::get_dance_list);
    
    ClassDB::bind_method(D_METHOD("set_time_interval", "time_interval"), &RubiconDancerData::set_time_interval);
    ClassDB::bind_method("get_time_interval", &RubiconDancerData::get_time_interval);
    
    ClassDB::bind_method(D_METHOD("set_force_dancing", "force_dancing"), &RubiconDancerData::set_force_dancing);
    ClassDB::bind_method("get_force_dancing", &RubiconDancerData::get_force_dancing);
    
    ClassDB::bind_method(D_METHOD("set_reset_animation_progress", "reset_animation_progress"), &RubiconDancerData::set_reset_animation_progress);
    ClassDB::bind_method("get_reset_animation_progress", &RubiconDancerData::get_reset_animation_progress);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "time_value", PROPERTY_HINT_ENUM, "Measure,Beat,Step"), "set_time_value", "get_time_value");
    ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "dance_list"), "set_dance_list", "get_dance_list");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "time_interval"), "set_time_interval", "get_time_interval");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "force_dancing"), "set_force_dancing", "get_force_dancing");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "reset_animation_progress"), "set_reset_animation_progress", "get_reset_animation_progress");
}