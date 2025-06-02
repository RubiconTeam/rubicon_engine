#ifndef RUBICON_CHARACTER_CONTROLLER_H
#define RUBICON_CHARACTER_CONTROLLER_H

#include "core/object/class_db.h"
#include "core/variant/typed_dictionary.h"
#include "rubicon_dancer_controller.h"

template <typename K, typename V>
class TypedDictionary;

class RubiconCharacterController : public RubiconDancerController {
    GDCLASS(RubiconCharacterController, Node);

public:
    float data_sing_duration = 4.0;
    float data_sing_timer = 0.0;

    StringName special_animation_name;
    bool special_animation_override_dance = false;
    bool special_animation_override_sing = false;
    float special_animation_start_time = 0.0;

    bool status_singing = false;
    bool status_holding = false;
    bool status_missed = false;
    bool status_freeze_singing = false;

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

#endif // RUBICON_CHARACTER_CONTROLLER_H