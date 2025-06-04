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

    Ref<RubiconCharacterIconData> data_icon;
    PackedStringArray data_sing_animations = static_cast<PackedStringArray>(GLOBAL_GET("rubicon_engine/environment/characters/default_sing_animations"));
    float data_sing_duration = 4.0;
    HoldStyle data_hold_style = HoldStyle::HOLD_STYLE_FREEZE;
    float data_repeat_loop_point = 0.125;

    StringName special_animation_name;
    bool special_animation_override_dance = false;
    bool special_animation_override_sing = false;
    float special_animation_start_time = 0.0;

    bool status_singing = false;
    bool status_holding = false;
    float status_sing_timer = 0.0;
    bool status_missed = false;
    bool status_freeze_singing = false;

    void set_data_icon(const Ref<RubiconCharacterIconData> p_value);
    Ref<RubiconCharacterIconData> get_data_icon() const;
    void set_data_sing_duration(const float p_value);
    float get_data_sing_duration() const;
    void set_data_hold_style(const HoldStyle p_value);
    HoldStyle get_data_hold_style() const;
    void set_data_repeat_loop_point(const float p_value);
    float get_data_repeat_loop_point() const;

    void set_special_animation_name(const StringName &p_value);
    StringName get_special_animation_name() const;
    void set_special_animation_override_dance(const bool p_value);
    bool get_special_animation_override_dance() const;
    void set_special_animation_override_sing(const bool p_value);
    bool get_special_animation_override_sing() const;
    void set_special_animation_start_time(const float p_value);
    float get_special_animation_start_time() const;

    void set_status_singing(const bool p_value);
    bool get_status_singing() const;
    void set_status_holding(const bool p_value);
    bool get_status_holding() const;
    void set_status_sing_timer(const float p_value);
    float get_status_sing_timer() const;
    void set_status_missed(const bool p_value);
    bool get_status_missed() const;
    void set_status_freeze_singing(const bool p_value);
    bool get_status_freeze_singing() const;

    void sing(const int p_direction, const bool p_holding, const bool p_miss, const String &p_custom_prefix, const String &p_custom_suffix);
    void play_special_animation(const StringName &p_name, const bool p_override_dance = true, const bool p_override_sing = true, const float p_start_time = 0.0);

protected:
    void _notification(int p_what);
    static void _bind_methods();

    void hold();

    GDVIRTUAL5(_sing, int, bool, bool, String, String);
    GDVIRTUAL4(_play_special_animation, StringName, bool, bool, float);
    GDVIRTUAL0(_hold);

private:
    int _last_step = 0;
    TypedDictionary<int, bool> _indexes_holding;
};

VARIANT_ENUM_CAST(RubiconCharacterController::HoldStyle);

#endif // RUBICON_CHARACTER_CONTROLLER_H