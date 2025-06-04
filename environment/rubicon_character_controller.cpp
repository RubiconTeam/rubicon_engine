#include "rubicon_character_controller.h"

typedef RubiconCharacterController::HoldStyle HoldStyle;

void RubiconCharacterController::set_data_icon(const Ref<RubiconCharacterIconData> p_value) {
    data_icon = p_value;
}

Ref<RubiconCharacterIconData> RubiconCharacterController::get_data_icon() const {
    return data_icon;
}

void RubiconCharacterController::set_data_sing_duration(const float p_value) {
    data_sing_duration = p_value;
}

float RubiconCharacterController::get_data_sing_duration() const {
    return data_sing_duration;
}

void RubiconCharacterController::set_data_hold_style(const HoldStyle p_value) {
    data_hold_style = p_value;
}

HoldStyle RubiconCharacterController::get_data_hold_style() const {
    return data_hold_style;
}

void RubiconCharacterController::set_data_repeat_loop_point(const float p_value) {
    data_repeat_loop_point = p_value;
}

float RubiconCharacterController::get_data_repeat_loop_point() const {
    return data_repeat_loop_point;
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

void RubiconCharacterController::set_status_singing(const bool p_value) {
    status_singing = p_value;
}

bool RubiconCharacterController::get_status_singing() const {
    return status_singing;
}

void RubiconCharacterController::set_status_holding(const bool p_value) {
    status_holding = p_value;
}

bool RubiconCharacterController::get_status_holding() const {
    return status_holding;
}

void RubiconCharacterController::set_status_sing_timer(const float p_value) {
    status_sing_timer = p_value;
}

float RubiconCharacterController::get_status_sing_timer() const {
    return status_sing_timer;
}

void RubiconCharacterController::set_status_missed(const bool p_value) {
    status_missed = p_value;
}

bool RubiconCharacterController::get_status_missed() const {
    return status_missed;
}

void RubiconCharacterController::set_status_freeze_singing(const bool p_value) {
    status_freeze_singing = p_value;
}

bool RubiconCharacterController::get_status_freeze_singing() const {
    return status_freeze_singing;
}

void RubiconCharacterController::sing(const int p_direction, const bool p_holding, const bool p_miss, const String &p_custom_prefix, const String &p_custom_suffix) {
    if (special_animation_override_sing)
        return;
    
    bool was_holding = _indexes_holding.has(p_direction) && _indexes_holding[p_direction];
    _indexes_holding[p_direction] = p_holding;
    bool should_be_holding = _indexes_holding.values().has(true);

    status_sing_timer = 0.0;
    status_singing = true;
    status_holding = should_be_holding;
    status_missed = p_miss && !should_be_holding;

    if (was_holding && !p_holding && !status_missed)
        return;
    
    String base_anim = data_sing_animations[p_direction];

    String prefix = p_custom_prefix;
    if (prefix.is_empty())
        prefix = status_global_prefix;
    
    String suffix = p_custom_suffix;
    if (suffix.is_empty())
        suffix = status_global_suffix;
    
    String anim_name = prefix + base_anim + suffix;
    //if (status_missed && get_animation_player()->has_animation)
}

void RubiconCharacterController::_bind_methods() {
    BIND_ENUM_CONSTANT(HOLD_STYLE_NONE);
    BIND_ENUM_CONSTANT(HOLD_STYLE_REPEAT);
    BIND_ENUM_CONSTANT(HOLD_STYLE_STEP_REPEAT);
    BIND_ENUM_CONSTANT(HOLD_STYLE_FREEZE);

    GLOBAL_DEF_BASIC(PropertyInfo(Variant::PACKED_STRING_ARRAY, "rubicon_engine/environment/characters/default_sing_animations"), PackedStringArray({"singLEFT", "singDOWN", "singUP", "singRIGHT"}));
}