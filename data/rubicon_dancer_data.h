#ifndef RUBICON_DANCER_DATA_H
#define RUBICON_DANCER_DATA_H

#include "core/io/resource.h"
#include "rubicon_beat_syncer_data.h"

class RubiconDancerData : public Resource {
    GDCLASS(RubiconDancerData, Resource);

public:
    PackedStringArray dance_list = PackedStringArray({"idle"});
    bool force_dancing = true;
    bool reset_animation_progress = true;

    void set_dance_list(const PackedStringArray p_dance_list);
    PackedStringArray get_dance_list() const;

    void set_force_dancing(const bool p_force_dancing);
    bool get_force_dancing() const;

    void set_reset_animation_progress(const bool p_reset_animation_progress);
    bool get_reset_animation_progress() const;

protected:
    static void _bind_methods();
};

#endif