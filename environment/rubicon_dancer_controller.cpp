#include "rubicon_dancer_controller.h"

void RubiconDancerController::set_global_prefix(const String p_global_prefix) {
    global_prefix = p_global_prefix;
}

String RubiconDancerController::get_global_prefix() const {
    return global_prefix;
}

void RubiconDancerController::set_global_suffix(const String p_global_suffix) {
    global_suffix = p_global_suffix;
}

String RubiconDancerController::get_global_suffix() const {
    return global_suffix;
}

void RubiconDancerController::set_dance_index(const int p_dance_index) {
    dance_index = p_dance_index;
}

int RubiconDancerController::get_dance_index() const {
    return dance_index;
}

void RubiconDancerController::set_freeze_dancing(const bool p_freeze_dancing) {
    freeze_dancing = p_freeze_dancing;
}

bool RubiconDancerController::get_freeze_dancing() const {
    return freeze_dancing;
}

void RubiconDancerController::set_dancer_data(const Ref<RubiconDancerData> p_dancer_data) {
    dancer_data = p_dancer_data;
}

Ref<RubiconDancerData> RubiconDancerController::get_dancer_data() const {
    return dancer_data;
}

void RubiconDancerController::set_animation_player(AnimationPlayer *p_animation_player) {
    animation_player = p_animation_player;
}

AnimationPlayer* RubiconDancerController::get_animation_player() {
    return animation_player;
}

void RubiconDancerController::set_beat_syncer(Ref<BeatSyncer> p_beat_syncer) {
    beat_syncer = p_beat_syncer;
}

Ref<BeatSyncer> RubiconDancerController::get_beat_syncer() {
    return beat_syncer;
}

void RubiconDancerController::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_global_prefix", "global_prefix"), &RubiconDancerController::set_global_prefix);
    ClassDB::bind_method("get_global_prefix", &RubiconDancerController::get_global_prefix);

    ClassDB::bind_method(D_METHOD("set_global_suffix", "global_suffix"), &RubiconDancerController::set_global_suffix);
    ClassDB::bind_method("get_global_suffix", &RubiconDancerController::get_global_suffix);

    ClassDB::bind_method(D_METHOD("set_dance_index", "dance_index"), &RubiconDancerController::set_dance_index);
    ClassDB::bind_method("get_dance_index", &RubiconDancerController::get_dance_index);

    ClassDB::bind_method(D_METHOD("set_freeze_dancing", "freeze_dancing"), &RubiconDancerController::set_freeze_dancing);
    ClassDB::bind_method("get_freeze_dancing", &RubiconDancerController::get_freeze_dancing);

    ClassDB::bind_method(D_METHOD("set_dancer_data", "dancer_data"), &RubiconDancerController::set_dancer_data);
    ClassDB::bind_method("get_dancer_data", &RubiconDancerController::get_dancer_data);

    ClassDB::bind_method(D_METHOD("set_animation_player", "animation_player"), &RubiconDancerController::set_animation_player);
    ClassDB::bind_method("get_animation_player", &RubiconDancerController::get_animation_player);

    ClassDB::bind_method(D_METHOD("set_beat_syncer", "beat_syncer"), &RubiconDancerController::set_beat_syncer);
    ClassDB::bind_method("get_beat_syncer", &RubiconDancerController::get_beat_syncer);*/

    ADD_PROPERTY(PropertyInfo(Variant::STRING, "global_prefix"), "set_global_prefix", "get_global_prefix");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "global_suffix"), "set_global_suffix", "get_global_suffix");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "dance_index"), "set_dance_index", "get_dance_index");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "freeze_dancing"), "set_freeze_dancing", "get_freeze_dancing");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "dancer_data", PROPERTY_HINT_RESOURCE_TYPE, "RubiconDancerData"), "set_dancer_data", "get_dancer_data");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "animation_player", PROPERTY_HINT_NODE_TYPE, "AnimationPlayer"), "set_animation_player", "get_animation_player");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "beat_syncer", PROPERTY_HINT_NODE_TYPE, "BeatSyncer"), "set_beat_syncer", "get_beat_syncer");
}