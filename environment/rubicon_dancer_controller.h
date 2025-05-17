#ifndef RUBICON_DANCER_CONTROLLER_H
#define RUBICON_DANCER_CONTROLLER_H

#include "scene/main/node.h"
#include "scene/animation/animation_player.h"
#include "../data/rubicon_dancer_data.h"
#include "../rubicon_beat_syncer.h"
#include "core/object/class_db.h"

class RubiconDancerController : public Node {
    GDCLASS(RubiconDancerController, Node);

public:
    String global_prefix;
    String global_suffix;
    int dance_index = 0;
    bool freeze_dancing = false;

    // no idea if these should be references but just in case
    Ref<RubiconDancerData> dancer_data;
    AnimationPlayer* reference_animation_player = nullptr;
    RubiconBeatSyncer* internal_beat_syncer = nullptr;

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

    void set_reference_animation_player(AnimationPlayer *p_animation_player);
    AnimationPlayer* get_reference_animation_player() const;
    
    void set_internal_beat_syncer(RubiconBeatSyncer *p_beat_syncer);
    RubiconBeatSyncer* get_internal_beat_syncer() const;

    void dance(const String &p_custom_prefix = "", const String &p_custom = "");

protected:
    static void _bind_methods();
    
    void _notification(int p_notification);

    void _try_dance();
};

#endif