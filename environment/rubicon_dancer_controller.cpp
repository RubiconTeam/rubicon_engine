#include "rubicon_dancer_controller.h"

void RubiconDancerController::set_data_dance_animations(const PackedStringArray p_value) {
    data_dance_animations = p_value;
}

PackedStringArray RubiconDancerController::get_data_dance_animations() const {
    return data_dance_animations;
}

void RubiconDancerController::set_data_force_dancing(const bool p_value) {
    data_force_dancing = p_value;
}

bool RubiconDancerController::get_data_force_dancing() const {
    return data_force_dancing;
}

void RubiconDancerController::set_data_reset_animation_progress(const bool p_value) {
    data_reset_animation_progress = p_value;
}

bool RubiconDancerController::get_data_reset_animation_progress() const {
    return data_reset_animation_progress;
}

void RubiconDancerController::set_status_global_prefix(const String p_global_prefix) {
    status_global_prefix = p_global_prefix;
}

String RubiconDancerController::get_status_global_prefix() const {
    return status_global_prefix;
}

void RubiconDancerController::set_status_global_suffix(const String p_global_suffix) {
    status_global_suffix = p_global_suffix;
}

String RubiconDancerController::get_status_global_suffix() const {
    return status_global_suffix;
}

void RubiconDancerController::set_status_dance_index(const int p_dance_index) {
    status_dance_index = p_dance_index;
}

int RubiconDancerController::get_status_dance_index() const {
    return status_dance_index;
}

void RubiconDancerController::set_status_freeze_dancing(const bool p_freeze_dancing) {
    status_freeze_dancing = p_freeze_dancing;
}

bool RubiconDancerController::get_status_freeze_dancing() const {
    return status_freeze_dancing;
}

void RubiconDancerController::set_internal_dance_behavior(const bool p_enabled) {
    _internal_dance_enabled = p_enabled;
}

bool RubiconDancerController::is_internally_dancing() const {
    return _internal_dance_enabled;
}

AnimationPlayer* RubiconDancerController::get_animation_player() const {
    return _animation_player;
}

RubiconBeatSyncer* RubiconDancerController::get_beat_syncer() const {
	return _beat_syncer;
}

void RubiconDancerController::dance(const String &p_custom_prefix, const String &p_custom_suffix) {
    if (_internal_dance_enabled) {
        String prefix = p_custom_prefix.is_empty() ? status_global_prefix : p_custom_prefix;
        String suffix = p_custom_suffix.is_empty() ? status_global_suffix : p_custom_suffix;

        String anim_name = data_dance_animations[status_dance_index];
        if (_animation_player->has_animation(prefix + anim_name + suffix))
            anim_name = prefix + anim_name + suffix;
        else
            WARN_PRINT("No animation found with prefix and suffix, playing regular animation.");

        if (_animation_player->has_animation(anim_name)) 
            _animation_player->play(anim_name);
        
        if (data_reset_animation_progress)
            _animation_player->seek(0.0, true);
    }
    
    GDVIRTUAL_CALL(_dance, p_custom_prefix, p_custom_suffix);
    status_dance_index = (status_dance_index + 1) % data_dance_animations.size();
}

PackedStringArray RubiconDancerController::get_configuration_warnings() const {
    PackedStringArray warnings = Node::get_configuration_warnings();

    if (_animation_player == nullptr)
        warnings.push_back(RTR("This controller has no AnimationPlayer, so it can not play any animations.\nConsider adding an AnimationPlayer as a child."));
    
    if (_beat_syncer == nullptr)
        warnings.push_back(RTR("This controller has no BeatSyncer, so it doesn't know when to play animations.\nConsider adding a BeatSyncer as a child."));

    return warnings;
}

void RubiconDancerController::_notification(int p_notification) {
    switch(p_notification) {
        case NOTIFICATION_READY: {
            if (Engine::get_singleton()->is_editor_hint())
                return;

            dance();
        } break;
        case NOTIFICATION_CHILD_ORDER_CHANGED: {
            _animation_player = nullptr;
            
            if (_beat_syncer)
                _beat_syncer->disconnect(SNAME("bumped"), callable_mp(this, &RubiconDancerController::_try_dance));
            
            _beat_syncer = nullptr;

            for (int i = 0; i < get_child_count(); i++) {
                Node* child = get_child(i);

                AnimationPlayer* anim_player_child = Object::cast_to<AnimationPlayer>(child);
                if (anim_player_child)
                    _animation_player = anim_player_child;
                
                RubiconBeatSyncer* beat_syncer_child = Object::cast_to<RubiconBeatSyncer>(child);
                if (beat_syncer_child) {
                    _beat_syncer = beat_syncer_child;
                    _beat_syncer->connect(SNAME("bumped"), callable_mp(this, &RubiconDancerController::_try_dance));
                }
            }
        } break;
    }
}

void RubiconDancerController::_try_dance() {
    bool is_current_anim_dance = _animation_player->is_playing() && _animation_player->get_current_animation().contains(data_dance_animations[status_dance_index]);
    bool is_current_dance_done = !is_current_anim_dance || _animation_player->get_current_animation_position() >= _animation_player->get_current_animation_length();

    if((data_force_dancing || (!data_force_dancing && is_current_dance_done)) && !status_freeze_dancing)
        dance();
}

void RubiconDancerController::_bind_methods() {
    // Getters and Setters
    ClassDB::bind_method(D_METHOD("set_data_dance_animations", "value"), &RubiconDancerController::set_data_dance_animations);
    ClassDB::bind_method("get_data_dance_animations", &RubiconDancerController::get_data_dance_animations);
    
    ClassDB::bind_method(D_METHOD("set_data_force_dancing", "force_dancing"), &RubiconDancerController::set_data_force_dancing);
    ClassDB::bind_method("get_data_force_dancing", &RubiconDancerController::get_data_force_dancing);
    
    ClassDB::bind_method(D_METHOD("set_data_reset_animation_progress", "reset_animation_progress"), &RubiconDancerController::set_data_reset_animation_progress);
    ClassDB::bind_method("get_data_reset_animation_progress", &RubiconDancerController::get_data_reset_animation_progress);

    ClassDB::bind_method(D_METHOD("set_status_global_prefix", "global_prefix"), &RubiconDancerController::set_status_global_prefix);
    ClassDB::bind_method("get_status_global_prefix", &RubiconDancerController::get_status_global_prefix);

    ClassDB::bind_method(D_METHOD("set_status_global_suffix", "global_suffix"), &RubiconDancerController::set_status_global_suffix);
    ClassDB::bind_method("get_status_global_suffix", &RubiconDancerController::get_status_global_suffix);

    ClassDB::bind_method(D_METHOD("set_status_dance_index", "dance_index"), &RubiconDancerController::set_status_dance_index);
    ClassDB::bind_method("get_status_dance_index", &RubiconDancerController::get_status_dance_index);

    ClassDB::bind_method(D_METHOD("set_status_freeze_dancing", "freeze_dancing"), &RubiconDancerController::set_status_freeze_dancing);
    ClassDB::bind_method("get_status_freeze_dancing", &RubiconDancerController::get_status_freeze_dancing);

    // Properties
    ADD_GROUP("Data", "data_");
    ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "data_dance_animations"), "set_data_dance_animations", "get_data_dance_animations");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "data_force_dancing"), "set_data_force_dancing", "get_data_force_dancing");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "data_reset_animation_progress"), "set_data_reset_animation_progress", "get_data_reset_animation_progress");

    ADD_GROUP("Status", "status");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "status_global_prefix"), "set_status_global_prefix", "get_status_global_prefix");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "status_global_suffix"), "set_status_global_suffix", "get_status_global_suffix");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "status_dance_index"), "set_status_dance_index", "get_status_dance_index");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "status_freeze_dancing"), "set_status_freeze_dancing", "get_status_freeze_dancing");

    ClassDB::bind_method("get_animation_player", &RubiconDancerController::get_animation_player);
    ClassDB::bind_method("get_beat_syncer", &RubiconDancerController::get_beat_syncer);

    ClassDB::bind_method(D_METHOD("set_internal_dance_behavior", "enabled"), &RubiconDancerController::set_internal_dance_behavior);
    ClassDB::bind_method("is_internally_dancing", &RubiconDancerController::is_internally_dancing);

    ClassDB::bind_method(D_METHOD("dance", "custom_prefix", "custom_suffix"), &RubiconDancerController::dance);
    
    GDVIRTUAL_BIND(_dance, "custom_prefix", "custom_suffix")
}