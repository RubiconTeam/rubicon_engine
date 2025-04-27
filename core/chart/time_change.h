#ifndef TIME_CHANGE_H
#define TIME_CHANGE_H

#include "core/object/ref_counted.h"

#include "core/object/class_db.h"

#include "core/object/object.h"

class TimeChange : public RefCounted {
    GDCLASS(TimeChange, RefCounted);

public:
    float Time;
    float Bpm;
    float TimeSignatureNumerator = 4;
    float TimeSignatureDenominator = 4;

    float MsTime = 0.0;

    void SetTime(const float time);
	float GetTime() const;

    float GetMeasureValue();
    float GetBeatValue();
    float GetStepValue();

protected:
    static void _bind_methods();

};

#endif // TIME_CHANGE_H