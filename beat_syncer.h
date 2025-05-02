#ifndef BEAT_SYNCER_H
#define BEAT_SYNCER_H

#include "scene/main/node.h"
#include "data/beat_syncer_data.h"
#include "modules/rubicon_core/chart/time_change.h"
#include "core/object/class_db.h"

class BeatSyncer : public Node {
    GDCLASS(BeatSyncer, Node);

public:
    bool enabled = true;

    void set_enabled(const bool p_enabled);
    bool get_enabled() const;

    void set_data(const Ref<BeatSyncerData> p_data);
    Ref<BeatSyncerData> get_data() const;

protected:
    void _notification(int p_notification);
    static void _bind_methods();

private:
    Ref<TimeChange> _current_time_change;
    Ref<BeatSyncerData> _data;
        
    int _bump_step = 4; // This is DIFFERENT from TimeValue.Step!!!
    int _step_offset = 0;

    bool _initialized = false;

    void _step_hit(const int p_step);
    void _time_change_reached(const Ref<TimeChange> p_current_time_change);
    void _update_values();
};

#endif // BEAT_SYNCER_H