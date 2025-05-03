#ifndef RUBICON_DANCER_CONTROLLER_H
#define RUBICON_DANCER_CONTROLLER_H

#include "scene/main/node.h"
#include "scene/animation/animation_player.h"
#include "modules/rubicon/data/rubicon_dancer_data.h"
#include "modules/rubicon/beat_syncer.h"
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
    AnimationPlayer *animation_player;
    BeatSyncer *beat_syncer;

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

    void set_animation_player(AnimationPlayer *p_animation_player);
    AnimationPlayer* get_animation_player();
    
    void set_beat_syncer(BeatSyncer *p_beat_syncer);
    BeatSyncer* get_beat_syncer();

protected:
    static void _bind_methods();
};

#endif