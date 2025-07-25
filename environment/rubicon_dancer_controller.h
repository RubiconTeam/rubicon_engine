#ifndef RUBICON_DANCER_CONTROLLER_H
#define RUBICON_DANCER_CONTROLLER_H

#include "scene/main/node.h"
#include "scene/animation/animation_player.h"
#include "../rubicon_beat_syncer.h"
#include "core/object/class_db.h"
#include "core/object/gdvirtual.gen.inc"
#include "core/variant/typed_array.h"
#include "core/config/project_settings.h"

template <typename T>
class TypedArray;

class RubiconDancerController : public Node {
    GDCLASS(RubiconDancerController, Node);

public:
    PackedStringArray dance_animations = static_cast<PackedStringArray>(GLOBAL_GET("rubicon_engine/environment/dancers/default_dance_animations"));
    bool force_dancing = true;
    bool reset_animation_progress = true;

    String global_prefix;
    String global_suffix;
    int dance_index = 0;
    bool freeze_dancing = false;

    void set_dance_animations(const PackedStringArray p_value);
    PackedStringArray get_dance_animations() const;

    void set_force_dancing(const bool p_value);
    bool get_force_dancing() const;

    void set_reset_animation_progress(const bool p_value);
    bool get_reset_animation_progress() const;

    void set_global_prefix(const String p_global_prefix);
    String get_global_prefix() const;

    void set_global_suffix(const String p_global_suffix);
    String get_global_suffix() const;

    void set_dance_index(const int p_dance_index);
    int get_dance_index() const;

    void set_freeze_dancing(const bool p_freeze_dancing);
    bool get_freeze_dancing() const;

    void set_internal_dance_behavior(const bool p_enabled);
    bool is_internally_dancing() const;

    AnimationPlayer* get_animation_player() const;
    RubiconBeatSyncer* get_beat_syncer() const;

    void dance(const String &p_custom_prefix = "", const String &p_custom_suffix = "");
    void dance_internal(const String &p_custom_prefix = "", const String &p_custom_suffix = "");

    PackedStringArray get_configuration_warnings() const override;

protected:
    void _notification(int p_notification);
    virtual void _try_dance();

    virtual void _animation_player_unbind();
    virtual void _animation_player_bind(AnimationPlayer *p_animation_player);

    static void _bind_methods();

    GDVIRTUAL2(_dance, String, String);

private:
    AnimationPlayer* _animation_player = nullptr;
    RubiconBeatSyncer* _beat_syncer = nullptr;

    bool _internal_dance_enabled = true;
};

#endif // RUBICON_DANCER_CONTROLLER_H