#ifndef RUBICON_CHARACTER_CONTROLLER_H
#define RUBICON_CHARACTER_CONTROLLER_H

#include "core/object/class_db.h"
#include "core/variant/typed_dictionary.h"
#include "core/config/project_settings.h"
#include "../data/rubicon_character_icon_data.h"
#include "rubicon_dancer_controller.h"

template <typename K, typename V>
class TypedDictionary;

class RubiconCharacterController : public RubiconDancerController {
    GDCLASS(RubiconCharacterController, Node);

public:
    enum HoldStyle {
        HOLD_STYLE_NONE,
        HOLD_STYLE_REPEAT,
        HOLD_STYLE_STEP_REPEAT,
        HOLD_STYLE_FREEZE
    };

    Ref<RubiconCharacterIconData> icon;
    float sing_duration = 4.0;
    HoldStyle hold_style = HoldStyle::HOLD_STYLE_FREEZE;
    float repeat_loop_point = 0.125;

    PackedStringArray animation_sing_animations = static_cast<PackedStringArray>(GLOBAL_GET("rubicon_engine/environment/characters/default_sing_animations"));
    String animation_miss_prefix = static_cast<String>(GLOBAL_GET("rubicon_engine/environment/characters/miss/prefix"));
    String animation_miss_suffix = static_cast<String>(GLOBAL_GET("rubicon_engine/environment/characters/miss/suffix"));

    StringName special_animation_name;
    bool special_animation_override_dance = false;
    bool special_animation_override_sing = false;
    float special_animation_start_time = 0.0;

    bool singing = false;
    bool holding = false;
    float sing_timer = 0.0;
    bool missed = false;
    bool freeze_singing = false;

    void set_icon(const Ref<RubiconCharacterIconData> p_value);
    Ref<RubiconCharacterIconData> get_icon() const;
    void set_sing_duration(const float p_value);
    float get_sing_duration() const;
    void set_hold_style(const HoldStyle p_value);
    HoldStyle get_hold_style() const;
    void set_repeat_loop_point(const float p_value);
    float get_repeat_loop_point() const;

    void set_animation_sing_animations(const PackedStringArray &p_value);
    PackedStringArray get_animation_sing_animations() const;
    void set_animation_miss_prefix(const String p_value);
    String get_animation_miss_prefix() const;
    void set_animation_miss_suffix(const String p_value);
    String get_animation_miss_suffix() const;

    void set_special_animation_name(const StringName &p_value);
    StringName get_special_animation_name() const;
    void set_special_animation_override_dance(const bool p_value);
    bool get_special_animation_override_dance() const;
    void set_special_animation_override_sing(const bool p_value);
    bool get_special_animation_override_sing() const;
    void set_special_animation_start_time(const float p_value);
    float get_special_animation_start_time() const;

    void set_singing(const bool p_value);
    bool get_singing() const;
    void set_holding(const bool p_value);
    bool get_holding() const;
    void set_sing_timer(const float p_value);
    float get_sing_timer() const;
    void set_missed(const bool p_value);
    bool get_missed() const;
    void set_freeze_singing(const bool p_value);
    bool get_freeze_singing() const;

    TypedDictionary<int, bool> get_directions_holding() const;

    void sing(const int p_direction, const bool p_holding, const bool p_miss, const String &p_custom_prefix, const String &p_custom_suffix);
    void play_special_animation(const StringName &p_name, const bool p_override_dance = true, const bool p_override_sing = true, const float p_start_time = 0.0);
    void hold();
    
    void reset_special_animation_parameters();

    void set_internal_sing(const bool p_value);
    bool is_internally_singing() const;
    void set_internal_play_special_animation(const bool p_value);
    bool is_internally_playing_special_animation() const;
    void set_internal_hold(const bool p_value);
    bool is_internally_holding() const;

    void sing_internal(const int p_direction, const bool p_holding, const bool p_miss, const String &p_custom_prefix, const String &p_custom_suffix);
    void play_special_animation_internal(const StringName &p_name, const bool p_override_dance = true, const bool p_override_sing = true, const float p_start_time = 0.0);
    void hold_internal();

protected:
    void _notification(int p_what);
    static void _bind_methods();

    GDVIRTUAL5(_sing, int, bool, bool, String, String);
    GDVIRTUAL4(_play_special_animation, StringName, bool, bool, float);
    GDVIRTUAL0(_hold);

private:
    int _last_step = 0;
    TypedDictionary<int, bool> _directions_holding;

    bool _internal_sing_enabled = true;
    bool _internal_play_special_animation_enabled = true;
    bool _internal_hold_enabled = true;

    void _animation_player_unbind() override;
    void _animation_player_bind(AnimationPlayer *p_animation_player) override;

    void _try_dance() override;

    void _animation_finished(const StringName &p_anim_name);
};

VARIANT_ENUM_CAST(RubiconCharacterController::HoldStyle);

#endif // RUBICON_CHARACTER_CONTROLLER_H