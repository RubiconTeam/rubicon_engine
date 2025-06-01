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
        String prefix = p_custom_prefix.is_empty() ? global_prefix : p_custom_prefix;
        String suffix = p_custom_suffix.is_empty() ? global_suffix : p_custom_suffix;

        String anim_name = dancer_data->dance_list[dance_index];
        if (_animation_player->has_animation(prefix + anim_name + suffix))
            anim_name = prefix + anim_name + suffix;
        else
            WARN_PRINT("No animation found with prefix and suffix, playing regular animation.");

        if (_animation_player->has_animation(anim_name)) 
            _animation_player->play(anim_name);
        
        if (dancer_data->reset_animation_progress)
            _animation_player->seek(0.0, true);
    }
    
    GDVIRTUAL_CALL(_dance, p_custom_prefix, p_custom_suffix);
    dance_index = (dance_index + 1) % dancer_data->dance_list.size();
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
    bool is_current_anim_dance = _animation_player->is_playing() && _animation_player->get_current_animation().contains(dancer_data->dance_list[dance_index]);
    bool is_current_dance_done = !is_current_anim_dance || _animation_player->get_current_animation_position() >= _animation_player->get_current_animation_length();

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

    ADD_PROPERTY(PropertyInfo(Variant::STRING, "global_prefix"), "set_global_prefix", "get_global_prefix");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "global_suffix"), "set_global_suffix", "get_global_suffix");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "dance_index"), "set_dance_index", "get_dance_index");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "freeze_dancing"), "set_freeze_dancing", "get_freeze_dancing");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "dancer_data", PROPERTY_HINT_RESOURCE_TYPE, "RubiconDancerData"), "set_dancer_data", "get_dancer_data");

    ClassDB::bind_method("get_animation_player", &RubiconDancerController::get_animation_player);
    ClassDB::bind_method("get_beat_syncer", &RubiconDancerController::get_beat_syncer);

    ClassDB::bind_method(D_METHOD("set_internal_dance_behavior", "enabled"), &RubiconDancerController::set_internal_dance_behavior);
    ClassDB::bind_method("is_internally_dancing", &RubiconDancerController::is_internally_dancing);

    ClassDB::bind_method(D_METHOD("dance", "custom_prefix", "custom_suffix"), &RubiconDancerController::dance);
    
    GDVIRTUAL_BIND(_dance, "custom_prefix", "custom_suffix")
}