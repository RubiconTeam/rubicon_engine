#ifndef BEAT_SYNCER_H
#define BEAT_SYNCER_H

#include "scene/main/node.h"
#include "modules/rubicon_core/rubicon_conductor.h"
#include "modules/rubicon_core/chart/rubicon_time_change.h"
#include "core/object/class_db.h"

class RubiconBeatSyncer : public Node {
    GDCLASS(RubiconBeatSyncer, Node);

public:
    enum TimeValue {
        TIME_VALUE_MEASURE,
        TIME_VALUE_BEAT,
        TIME_VALUE_STEP,
    };

    TimeValue type = TIME_VALUE_MEASURE;
    bool enabled = true;

    void set_type(const TimeValue p_type);
    TimeValue get_type() const;

    void set_value(const float p_value);
    float get_value() const;

    void set_enabled(const bool p_enabled);
    bool get_enabled() const;

    void set_conductor(RubiconConductor* p_value);
    RubiconConductor* get_conductor();

protected:
    void _notification(int p_notification);
    static void _bind_methods();

private:
    Ref<RubiconTimeChange> _current_time_change;
        
    int _bump_step = 4; // This is DIFFERENT from TimeValue.Step!!!
    int _step_offset = 0;

    float _cached_step = 0.0f;
    float _cached_beat = 0.0f;
    float _bump_measure = 0.5f;

    RubiconConductor* _conductor;

    void _step_hit(const int p_step);
    void _time_change_reached(const Ref<RubiconTimeChange> p_current_time_change);
    void _set_bump_measure(const float p_value);
};

VARIANT_ENUM_CAST(RubiconBeatSyncer::TimeValue);

#endif // BEAT_SYNCER_H