#ifndef RUBICON_DANCER_DATA_H
#define RUBICON_DANCER_DATA_H

#include "core/io/resource.h"
#include "beat_syncer_data.h"

class RubiconDancerData : public Resource {
    GDCLASS(RubiconDancerData, Resource);

public:
    // should prob make TimeValue its own thing instead of using beat_syncer_data's
    BeatSyncerData::TimeValue time_value;

    PackedStringArray dance_list = PackedStringArray({"idle"});
    float time_interval;
    bool force_dancing = true;
    bool reset_animation_progress = true;

    void set_time_value(const BeatSyncerData::TimeValue p_time_value);
    BeatSyncerData::TimeValue get_time_value() const;

    void set_dance_list(const PackedStringArray p_dance_list);
    PackedStringArray get_dance_list() const;

    void set_time_interval(const float p_time_interval);
    float get_time_interval() const;

    void set_force_dancing(const bool p_force_dancing);
    bool get_force_dancing() const;

    void set_reset_animation_progress(const bool p_reset_animation_progress);
    bool get_reset_animation_progress() const;

protected:
    static void _bind_methods();
};

#endif