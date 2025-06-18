#include "rubicon_character_controller.h"
#include "modules/rubicon_core/rubicon_conductor.h"

typedef RubiconCharacterController::HoldStyle HoldStyle;

void RubiconCharacterController::set_icon(const Ref<RubiconCharacterIconData> p_value) {
    icon = p_value;
}

Ref<RubiconCharacterIconData> RubiconCharacterController::get_icon() const {
    return icon;
}

void RubiconCharacterController::set_sing_duration(const float p_value) {
    sing_duration = p_value;
}

float RubiconCharacterController::get_sing_duration() const {
    return sing_duration;
}

void RubiconCharacterController::set_hold_style(const HoldStyle p_value) {
    hold_style = p_value;
}

HoldStyle RubiconCharacterController::get_hold_style() const {
    return hold_style;
}

void RubiconCharacterController::set_repeat_loop_point(const float p_value) {
    repeat_loop_point = p_value;
}

float RubiconCharacterController::get_repeat_loop_point() const {
    return repeat_loop_point;
}

void RubiconCharacterController::set_animation_sing_animations(const PackedStringArray &p_value) {
    animation_sing_animations = p_value;
}

PackedStringArray RubiconCharacterController::get_animation_sing_animations() const {
    return animation_sing_animations;
}

void RubiconCharacterController::set_animation_miss_prefix(const String p_value) {
    animation_miss_prefix = p_value;
}

String RubiconCharacterController::get_animation_miss_prefix() const {
    return animation_miss_prefix;
}

void RubiconCharacterController::set_animation_miss_suffix(const String p_value) {
    animation_miss_suffix = p_value;
}

String RubiconCharacterController::get_animation_miss_suffix() const {
    return animation_miss_suffix;
}

void RubiconCharacterController::set_special_animation_name(const StringName &p_value) {
    special_animation_name = p_value;
}

StringName RubiconCharacterController::get_special_animation_name() const {
    return special_animation_name;
}

void RubiconCharacterController::set_special_animation_override_dance(const bool p_value) {
    special_animation_override_dance = p_value;
}

bool RubiconCharacterController::get_special_animation_override_dance() const {
    return special_animation_override_dance;
}

void RubiconCharacterController::set_special_animation_override_sing(const bool p_value) {
    special_animation_override_sing = p_value;
}

bool RubiconCharacterController::get_special_animation_override_sing() const {
    return special_animation_override_sing;
}

void RubiconCharacterController::set_special_animation_start_time(const float p_value) {
    special_animation_start_time = p_value;
}

float RubiconCharacterController::get_special_animation_start_time() const {
    return special_animation_start_time;
}

void RubiconCharacterController::set_singing(const bool p_value) {
    singing = p_value;
}

bool RubiconCharacterController::get_singing() const {
    return singing;
}

void RubiconCharacterController::set_holding(const bool p_value) {
    holding = p_value;
}

bool RubiconCharacterController::get_holding() const {
    return holding;
}

void RubiconCharacterController::set_sing_timer(const float p_value) {
    sing_timer = p_value;
}

float RubiconCharacterController::get_sing_timer() const {
    return sing_timer;
}

void RubiconCharacterController::set_missed(const bool p_value) {
    missed = p_value;
}

bool RubiconCharacterController::get_missed() const {
    return missed;
}

void RubiconCharacterController::set_freeze_singing(const bool p_value) {
    freeze_singing = p_value;
}

bool RubiconCharacterController::get_freeze_singing() const {
    return freeze_singing;
}

TypedDictionary<int, bool> RubiconCharacterController::get_directions_holding() const {
    return _directions_holding;
}

void RubiconCharacterController::set_internal_sing(const bool p_value) {
    _internal_sing_enabled = p_value;
}

bool RubiconCharacterController::is_internally_singing() const {
    return _internal_sing_enabled;
}

void RubiconCharacterController::set_internal_play_special_animation(const bool p_value) {
    _internal_play_special_animation_enabled = p_value;
}

bool RubiconCharacterController::is_internally_playing_special_animation() const {
    return _internal_play_special_animation_enabled;
}

void RubiconCharacterController::set_internal_hold(const bool p_value) {
    _internal_hold_enabled = p_value;
}

bool RubiconCharacterController::is_internally_holding() const {
    return _internal_hold_enabled;
}

void RubiconCharacterController::sing(const int p_direction, const bool p_holding, const bool p_miss, const String &p_custom_prefix, const String &p_custom_suffix) {
    if (special_animation_override_sing)
        return;
    
    if (_internal_sing_enabled) {
        bool was_holding = _directions_holding.has(p_direction) && _directions_holding[p_direction];
        _directions_holding[p_direction] = p_holding;
        bool should_be_holding = _directions_holding.values().has(true);

        sing_timer = 0.0;
        singing = true;
        holding = should_be_holding;
        missed = p_miss && !should_be_holding;

        if (!(was_holding && !p_holding && !missed)) {
            String base_anim = animation_sing_animations[p_direction];

            String prefix = p_custom_prefix;
            if (prefix.is_empty())
                prefix = global_prefix + (missed ? animation_miss_prefix : "");
            
            String suffix = p_custom_suffix;
            if (suffix.is_empty())
                suffix = (missed ? animation_miss_suffix : "") + global_suffix;
            
            String anim_name = prefix + base_anim + suffix;
            if (get_animation_player()->has_animation(anim_name)) {
                get_animation_player()->play(anim_name);
            } else if (get_animation_player()->has_animation(base_anim)) {
                WARN_PRINT(vformat("Animation player has no animation called \"%s\", defaulting to base animation \"%s\"", anim_name, base_anim));
                get_animation_player()->play(base_anim);
            } else {
                WARN_PRINT(vformat("Animation player has no animation called \"%s\" and no base animation \"%s\".", anim_name, base_anim));
            }

            if (reset_animation_progress)
                get_animation_player()->seek(0.0, true);
        }
    }

    GDVIRTUAL_CALL(_sing, p_direction, p_holding, p_miss, p_custom_prefix, p_custom_suffix);
}

void RubiconCharacterController::play_special_animation(const StringName &p_name, const bool p_override_dance, const bool p_override_sing, const float p_start_time) {
    if (_internal_play_special_animation_enabled) {
        special_animation_name = p_name;
        special_animation_override_dance = p_override_dance;
        special_animation_override_sing = p_override_sing;
        special_animation_start_time = p_start_time;

        if (get_animation_player()->has_animation(p_name)) {
            get_animation_player()->play(p_name);
            get_animation_player()->seek(p_start_time, true);
        } else {
            WARN_PRINT(vformat("Animation \"%s\" not found when trying to play a special animation.", p_name));
        }
    }

    GDVIRTUAL_CALL(_play_special_animation, p_name, p_override_dance, p_override_sing, p_start_time);
}

void RubiconCharacterController::hold() {
    if (_internal_hold_enabled) {
        sing_timer = 0.0;

        switch (hold_style) {
            case HOLD_STYLE_STEP_REPEAT: {
                int cur_step = int(Math::floor(RubiconConductor::get_singleton()->get_current_step()));
                if (_last_step != cur_step) 
                    get_animation_player()->seek(0.0);
                
                    _last_step = cur_step;
            } break;
            case HOLD_STYLE_REPEAT: {
                double current_time = get_animation_player()->get_current_animation_position();
                if (current_time < repeat_loop_point)
                    break;
                
                get_animation_player()->seek(0.0);
            } break;
            case HOLD_STYLE_FREEZE: {
                get_animation_player()->seek(0.0);
            } break;
        }
    }

    GDVIRTUAL_CALL(_hold);
}

void RubiconCharacterController::reset_special_animation_parameters() {
    special_animation_name = "";
    special_animation_override_dance = false;
    special_animation_override_sing = false;
    special_animation_start_time = 0.0;
}

void RubiconCharacterController::_animation_player_unbind() {
    if (get_animation_player())
        get_animation_player()->disconnect(SNAME("animation_finished"), callable_mp(this, &RubiconCharacterController::_animation_finished));

    RubiconDancerController::_animation_player_unbind();
}

void RubiconCharacterController::_animation_player_bind(AnimationPlayer *p_animation_player) {
    RubiconDancerController::_animation_player_bind(p_animation_player);
    
    if (get_animation_player())
        get_animation_player()->connect(SNAME("animation_finished"), callable_mp(this, &RubiconCharacterController::_animation_finished));
}

void RubiconCharacterController::_animation_finished(const StringName &p_anim_name) {
    reset_special_animation_parameters();
}

void RubiconCharacterController::_try_dance() {
    bool is_not_singing = !singing || (singing && !freeze_singing && sing_timer >= RubiconConductor::get_singleton()->get_current_time_change()->get_step_value() * 0.001 * sing_duration);
    bool override_dancing = !special_animation_name.is_empty() && special_animation_override_dance;
    if (override_dancing || !is_not_singing)
        return;
    
    RubiconDancerController::_try_dance();
}

void RubiconCharacterController::_notification(int p_what) {
    switch(p_what) {
        case NOTIFICATION_PROCESS: {
            if (Engine::get_singleton()->is_editor_hint())
                return;
            
            if (holding)
                hold();
            
            sing_timer += get_process_delta_time();
        } break;
    }

    RubiconDancerController::_notification(p_what);
}

void RubiconCharacterController::_bind_methods() {
    // Getters and Setters
    ClassDB::bind_method(D_METHOD("set_icon", "value"), &RubiconCharacterController::set_icon);
    ClassDB::bind_method("get_icon", &RubiconCharacterController::get_icon);
    ClassDB::bind_method(D_METHOD("set_sing_duration", "value"), &RubiconCharacterController::set_sing_duration);
    ClassDB::bind_method("get_sing_duration", &RubiconCharacterController::get_sing_duration);
    ClassDB::bind_method(D_METHOD("set_hold_style", "value"), &RubiconCharacterController::set_hold_style);
    ClassDB::bind_method("get_hold_style", &RubiconCharacterController::get_hold_style);
    ClassDB::bind_method(D_METHOD("set_repeat_loop_point", "value"), &RubiconCharacterController::set_repeat_loop_point);
    ClassDB::bind_method("get_repeat_loop_point", &RubiconCharacterController::get_repeat_loop_point);

    ClassDB::bind_method(D_METHOD("set_animation_sing_animations", "value"), &RubiconCharacterController::set_animation_sing_animations);
    ClassDB::bind_method("get_animation_sing_animations", &RubiconCharacterController::get_animation_sing_animations);
    ClassDB::bind_method(D_METHOD("set_animation_miss_prefix", "value"), &RubiconCharacterController::set_animation_miss_prefix);
    ClassDB::bind_method("get_animation_miss_prefix", &RubiconCharacterController::get_animation_miss_prefix);
    ClassDB::bind_method(D_METHOD("set_animation_miss_suffix", "value"), &RubiconCharacterController::set_animation_miss_suffix);
    ClassDB::bind_method("get_animation_miss_suffix", &RubiconCharacterController::get_animation_miss_suffix);

    ClassDB::bind_method(D_METHOD("set_special_animation_name", "value"), &RubiconCharacterController::set_special_animation_name);
    ClassDB::bind_method("get_special_animation_name", &RubiconCharacterController::get_special_animation_name);
    ClassDB::bind_method(D_METHOD("set_special_animation_override_dance", "value"), &RubiconCharacterController::set_special_animation_override_dance);
    ClassDB::bind_method("get_special_animation_override_dance", &RubiconCharacterController::get_special_animation_override_dance);
    ClassDB::bind_method(D_METHOD("set_special_animation_override_sing", "value"), &RubiconCharacterController::set_special_animation_override_sing);
    ClassDB::bind_method("get_special_animation_override_sing", &RubiconCharacterController::get_special_animation_override_sing);
    ClassDB::bind_method(D_METHOD("set_special_animation_start_time", "value"), &RubiconCharacterController::set_special_animation_start_time);
    ClassDB::bind_method("get_special_animation_start_time", &RubiconCharacterController::get_special_animation_start_time);

    ClassDB::bind_method(D_METHOD("set_singing", "value"), &RubiconCharacterController::set_singing);
    ClassDB::bind_method("get_singing", &RubiconCharacterController::get_singing);
    ClassDB::bind_method(D_METHOD("set_holding", "value"), &RubiconCharacterController::set_holding);
    ClassDB::bind_method("get_holding", &RubiconCharacterController::get_holding);
    ClassDB::bind_method(D_METHOD("set_sing_timer", "value"), &RubiconCharacterController::set_sing_timer);
    ClassDB::bind_method("get_sing_timer", &RubiconCharacterController::get_sing_timer);
    ClassDB::bind_method(D_METHOD("set_missed", "value"), &RubiconCharacterController::set_missed);
    ClassDB::bind_method("get_missed", &RubiconCharacterController::get_missed);
    ClassDB::bind_method(D_METHOD("set_freeze_singing", "value"), &RubiconCharacterController::set_freeze_singing);
    ClassDB::bind_method("get_freeze_singing", &RubiconCharacterController::get_freeze_singing);

    // Proprties
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "RubiconCharacterIconData"), "set_icon", "get_icon");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "sing_duration"), "set_sing_duration", "get_sing_duration");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "hold_style", PROPERTY_HINT_ENUM, "None,Repeat,Step Repeat,Freeze"), "set_hold_style", "get_hold_style");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "repeat_loop_point"), "set_repeat_loop_point", "get_repeat_loop_point");

    ADD_GROUP("Animation", "animation_");
    ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "animation_sing_animations"), "set_animation_sing_animations", "get_animation_sing_animations");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "animation_miss_prefix"), "set_animation_miss_prefix", "get_animation_miss_prefix");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "animation_miss_suffix"), "set_animation_miss_suffix", "get_animation_miss_suffix");

    // Methods
    ClassDB::bind_method(D_METHOD("sing", "direction", "holding", "miss", "custom_prefix", "custom_suffix"), &RubiconCharacterController::sing);
    ClassDB::bind_method(D_METHOD("play_special_animation", "name", "override_dance", "override_sing", "start_time"), &RubiconCharacterController::play_special_animation);
    ClassDB::bind_method("reset_special_animation_parameters", &RubiconCharacterController::reset_special_animation_parameters);

    // Internals
    ClassDB::bind_method(D_METHOD("set_internal_sing", "value"), &RubiconCharacterController::set_internal_sing);
    ClassDB::bind_method("is_internally_singing", &RubiconCharacterController::is_internally_singing);
    ClassDB::bind_method(D_METHOD("set_internal_play_special_animation", "value"), &RubiconCharacterController::set_internal_play_special_animation);
    ClassDB::bind_method("is_internally_playing_special_animation", &RubiconCharacterController::is_internally_playing_special_animation);
    ClassDB::bind_method(D_METHOD("set_internal_hold", "value"), &RubiconCharacterController::set_internal_hold);
    ClassDB::bind_method("is_internally_holding", &RubiconCharacterController::is_internally_holding);

    // Virtual Binds
    GDVIRTUAL_BIND(_sing, "direction", "holding", "miss", "custom_prefix", "custom_suffix");
    GDVIRTUAL_BIND(_play_special_animation, "name", "override_dance", "override_sing", "start_time");
    GDVIRTUAL_BIND(_hold);

    BIND_ENUM_CONSTANT(HOLD_STYLE_NONE);
    BIND_ENUM_CONSTANT(HOLD_STYLE_REPEAT);
    BIND_ENUM_CONSTANT(HOLD_STYLE_STEP_REPEAT);
    BIND_ENUM_CONSTANT(HOLD_STYLE_FREEZE);

    // Basic Project Settings
    GLOBAL_DEF_BASIC(PropertyInfo(Variant::PACKED_STRING_ARRAY, "rubicon_engine/environment/characters/default_sing_animations"), PackedStringArray({"singLEFT", "singDOWN", "singUP", "singRIGHT"}));
    
    // Advanced Project Settings
    GLOBAL_DEF(PropertyInfo(Variant::STRING, "rubicon_engine/environment/characters/miss/prefix"), "");
    GLOBAL_DEF(PropertyInfo(Variant::STRING, "rubicon_engine/environment/characters/miss/suffix"), "miss");
}