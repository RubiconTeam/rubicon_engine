#include "modules/rubicon_plus_plus/core/chart/time_change.h"
#include "modules/rubicon_plus_plus/core/conductor.h"

void TimeChange::SetTime(const float time) {
    Time = time;
}

float TimeChange::GetTime() const {
    return Time;
}

float TimeChange::GetMeasureValue() {
    return Conductor::get_singleton()->MeasureToMs(1.0f, Bpm, TimeSignatureNumerator);
}

float TimeChange::GetBeatValue() {
    return Conductor::get_singleton()->BeatsToMs(1.0f, Bpm);
}

float TimeChange::GetStepValue() {
    return Conductor::get_singleton()->StepsToMs(1.0f, Bpm, TimeSignatureDenominator);
}

void TimeChange::_bind_methods() {
    // Methods
    ClassDB::bind_method("GetMeasureValue", &TimeChange::GetMeasureValue);
    ClassDB::bind_method("GetBeatValue", &TimeChange::GetBeatValue);
    ClassDB::bind_method("GetStepValue", &TimeChange::GetStepValue);

    // Getters and Setters
    ClassDB::bind_method(D_METHOD("SetTime", "time"), &TimeChange::SetTime);
	ClassDB::bind_method(D_METHOD("GetTime"), &TimeChange::GetTime);

    // Fields
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Time"), "SetTime", "GetTime");
}