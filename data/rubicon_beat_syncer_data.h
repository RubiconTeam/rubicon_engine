#ifndef RUBICON_BEAT_SYNCER_DATA_H
#define RUBICON_BEAT_SYNCER_DATA_H

#include "core/io/resource.h"

class RubiconBeatSyncerData : public Resource {
    GDCLASS(RubiconBeatSyncerData, Resource);

public:
    enum TimeValue {
        TIME_VALUE_MEASURE,
        TIME_VALUE_BEAT,
        TIME_VALUE_STEP,
    };

    TimeValue type = TIME_VALUE_MEASURE;

    void set_type(const TimeValue p_type);
    TimeValue get_type() const;

    void set_value(const float p_value);
    float get_value() const;

    float get_value_as_measure() const;

protected:
    static void _bind_methods();
    
private:
    float _bump_measure = 0.5f;
    float _cached_step = 0.0f;
    float _cached_beat = 0.0f;

    void _set_bump_measure(const float p_value);
};

VARIANT_ENUM_CAST(RubiconBeatSyncerData::TimeValue);

#endif