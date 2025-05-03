#include "rubicon_dancer_data.h"
#include "beat_syncer_data.h"

void RubiconDancerData::set_beat_data(const Ref<BeatSyncerData> p_data) {
    beat_data = p_data;

    emit_signal(SNAME("beat_data_changed"));
}

Ref<BeatSyncerData> RubiconDancerData::get_beat_data() const {
    return beat_data;
}

void RubiconDancerData::set_dance_list(const PackedStringArray p_dance_list) {
    dance_list = p_dance_list;
}

PackedStringArray RubiconDancerData::get_dance_list() const {
    return dance_list;
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
    ClassDB::bind_method(D_METHOD("set_beat_data", "beat_data"), &RubiconDancerData::set_beat_data);
    ClassDB::bind_method("get_beat_data", &RubiconDancerData::get_beat_data);
    
    ClassDB::bind_method(D_METHOD("set_dance_list", "dance_list"), &RubiconDancerData::set_dance_list);
    ClassDB::bind_method("get_dance_list", &RubiconDancerData::get_dance_list);
    
    ClassDB::bind_method(D_METHOD("set_force_dancing", "force_dancing"), &RubiconDancerData::set_force_dancing);
    ClassDB::bind_method("get_force_dancing", &RubiconDancerData::get_force_dancing);
    
    ClassDB::bind_method(D_METHOD("set_reset_animation_progress", "reset_animation_progress"), &RubiconDancerData::set_reset_animation_progress);
    ClassDB::bind_method("get_reset_animation_progress", &RubiconDancerData::get_reset_animation_progress);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "beat_data", PROPERTY_HINT_RESOURCE_TYPE, "BeatSyncerData"), "set_beat_data", "get_beat_data");
    ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "dance_list"), "set_dance_list", "get_dance_list");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "force_dancing"), "set_force_dancing", "get_force_dancing");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "reset_animation_progress"), "set_reset_animation_progress", "get_reset_animation_progress");

    ADD_SIGNAL(MethodInfo("beat_data_changed"));
}