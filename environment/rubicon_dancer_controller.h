#ifndef RUBICON_DANCER_CONTROLLER_H
#define RUBICON_DANCER_CONTROLLER_H

#include "scene/main/node.h"
#include "scene/animation/animation_player.h"
#include "../data/rubicon_dancer_data.h"
#include "../rubicon_beat_syncer.h"
#include "core/object/class_db.h"
#include "core/object/gdvirtual.gen.inc"
#include "core/variant/typed_array.h"

template <typename T>
class TypedArray;

class RubiconDancerController : public Node {
    GDCLASS(RubiconDancerController, Node);

public:
    String global_prefix;
    String global_suffix;
    int dance_index = 0;
    bool freeze_dancing = false;

    Ref<RubiconDancerData> dancer_data;

    void set_global_prefix(const String p_global_prefix);
    String get_global_prefix() const;

    void set_global_suffix(const String p_global_suffix);
    String get_global_suffix() const;

    void set_dance_index(const int p_dance_index);
    int get_dance_index() const;

    void set_freeze_dancing(const bool p_freeze_dancing);
    bool get_freeze_dancing() const;

    void set_dancer_data(const Ref<RubiconDancerData> p_dancer_data);
    Ref<RubiconDancerData> get_dancer_data() const;

    void set_internal_dance_behavior(const bool p_enabled);
    bool is_internally_dancing() const;

    AnimationPlayer* get_animation_player() const;
    RubiconBeatSyncer* get_beat_syncer() const;

    void dance(const String &p_custom_prefix = "", const String &p_custom_suffix = "");

    PackedStringArray get_configuration_warnings() const override;

protected:
    void _notification(int p_notification);
    void _try_dance();

    static void _bind_methods();

    GDVIRTUAL2(_dance, String, String);

private:
    AnimationPlayer* _animation_player = nullptr;
    RubiconBeatSyncer* _beat_syncer = nullptr;

    bool _internal_dance_enabled = true;
};

#endif