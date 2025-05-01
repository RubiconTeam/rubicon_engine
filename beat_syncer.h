#ifndef BEAT_SYNCER_H
#define BEAT_SYNCER_H

#include "scene/main/node.h"
#include "modules/rubicon_core/chart/time_change.h"
#include "core/object/class_db.h"

class BeatSyncer : public Node {
    GDCLASS(BeatSyncer, Node);

public:
    enum TimeValue {
        TIME_VALUE_MEASURE,
        TIME_VALUE_BEAT,
        TIME_VALUE_STEP,
    };

    bool enabled = true;
    TimeValue type = TIME_VALUE_MEASURE;
    float value;

    void set_enabled(const bool p_enabled);
    bool get_enabled() const;

    void set_type(const TimeValue p_type);
    TimeValue get_type() const;

    void set_value(const float p_value);
    bool get_value() const;

protected:
    void _notification(int p_notification);
    static void _bind_methods();

private:
    Ref<TimeChange> _current_bpm;
        
    int _bump_step = 4; // This is DIFFERENT from TimeValue.Step!!!
    int _step_offset = 0;

    float _cached_step = 0.0f;
    float _cached_beat = 0.0f;
    float _bump_measure = 0.5f;

    bool _initialized = false;

    void _step_hit(const int p_step);
    void _bpm_changed(const Ref<TimeChange> p_current_bpm);
    void _set_bump_measure(const float p_value);
};

VARIANT_ENUM_CAST(BeatSyncer::TimeValue);

#endif // BEAT_SYNCER_H