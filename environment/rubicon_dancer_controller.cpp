#include "rubicon_dancer_controller.h"

void RubiconDancerController::_notification(int p_notification) {
    switch(p_notification) {
        case NOTIFICATION_READY: {
            RubiconBeatSyncer* syncer = get_internal_beat_syncer();
            syncer = memnew(RubiconBeatSyncer);
            syncer->set_name("RubiconBeatSyncer");
            syncer->connect("bumped", callable_mp(this, &RubiconDancerController::_try_dance));
            add_child(syncer);
        }   break;
    }
}

void RubiconDancerController::dance(const String &p_custom_prefix, const String &p_custom_suffix) {
    String prefix = p_custom_prefix.is_empty() ? global_prefix : p_custom_prefix;
    String suffix = p_custom_suffix.is_empty() ? global_suffix : p_custom_suffix;

    AnimationPlayer* anim_player = get_reference_animation_player();
    String anim_name = dancer_data->dance_list[dance_index];
    if (anim_player->has_animation(prefix + anim_name + suffix))
        anim_name = prefix + anim_name + suffix;
    else
        WARN_PRINT("No animation found with prefix and suffix, playing regular animation.");

    if (anim_player->has_animation(anim_name)) 
        anim_player->play(anim_name);
    
    if (dancer_data->reset_animation_progress)
        anim_player->seek(0.0, true);
    
    dance_index = (dance_index + 1) % dancer_data->dance_list.size();
}

void RubiconDancerController::_try_dance() {
    AnimationPlayer* anim_player = get_reference_animation_player();

    bool is_current_anim_dance = anim_player->is_playing() && anim_player->get_current_animation().contains(dancer_data->dance_list[dance_index]);
    bool is_current_dance_done = !is_current_anim_dance || anim_player->get_current_animation_position() >= anim_player->get_current_animation_length();

    if((dancer_data->force_dancing || (!dancer_data->force_dancing && is_current_dance_done)) && !freeze_dancing)
        dance();
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

    ClassDB::bind_method(D_METHOD("set_reference_animation_player", "animation_player"), &RubiconDancerController::set_reference_animation_player);
    ClassDB::bind_method("get_reference_animation_player", &RubiconDancerController::get_reference_animation_player);

    ClassDB::bind_method(D_METHOD("set_internal_beat_syncer", "beat_syncer"), &RubiconDancerController::set_internal_beat_syncer);
    ClassDB::bind_method("get_internal_beat_syncer", &RubiconDancerController::get_internal_beat_syncer);

    ADD_PROPERTY(PropertyInfo(Variant::STRING, "global_prefix"), "set_global_prefix", "get_global_prefix");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "global_suffix"), "set_global_suffix", "get_global_suffix");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "dance_index"), "set_dance_index", "get_dance_index");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "freeze_dancing"), "set_freeze_dancing", "get_freeze_dancing");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "dancer_data", PROPERTY_HINT_RESOURCE_TYPE, "RubiconDancerData"), "set_dancer_data", "get_dancer_data");

    ADD_GROUP("References", "reference_");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "reference_animation_player", PROPERTY_HINT_NODE_TYPE, "AnimationPlayer"), "set_reference_animation_player", "get_reference_animation_player");

    ADD_GROUP("Internals", "internal_");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "internal_beat_syncer", PROPERTY_HINT_NODE_TYPE, "RubiconBeatSyncer"), "set_internal_beat_syncer", "get_internal_beat_syncer");
}

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

void RubiconDancerController::set_reference_animation_player(AnimationPlayer *p_animation_player) {
    reference_animation_player = p_animation_player;
}

AnimationPlayer* RubiconDancerController::get_reference_animation_player() const {
    return reference_animation_player;
}

void RubiconDancerController::set_internal_beat_syncer(RubiconBeatSyncer *p_beat_syncer) {
    if (internal_beat_syncer != nullptr) {
        internal_beat_syncer->disconnect(SNAME("bumped"), callable_mp(this, &RubiconDancerController::_try_dance));
    }

    internal_beat_syncer = p_beat_syncer;
    p_beat_syncer->connect(SNAME("bumped"), callable_mp(this, &RubiconDancerController::_try_dance));
}

RubiconBeatSyncer* RubiconDancerController::get_internal_beat_syncer() const {
	return internal_beat_syncer;
}