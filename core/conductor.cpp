#include "modules/rubicon_plus_plus/core/conductor.h"

Conductor *Conductor::singleton = nullptr;

Conductor *Conductor::get_singleton() {
	return singleton;
}

float Conductor::MeasureToMs(float measure, float bpm, float timeSignatureNumerator) const {
    return measure * (60000.0f / (bpm / timeSignatureNumerator));
}

float Conductor::BeatsToMs(float beat, float bpm) {
    return beat * (60000.0f / bpm);
}

float Conductor::StepsToMs(float step, float bpm, float timeSignatureDenominator) {
    return step * (60000.0f / bpm / timeSignatureDenominator);
}

void Conductor::_bind_methods() {
    ClassDB::bind_method(D_METHOD("MeasuresToMs", "measure", "bpm", "time_signature_numerator"), &Conductor::MeasureToMs);
}

Conductor::Conductor() {
	singleton = this;
}

Conductor::~Conductor() {
	if (singleton == this) {
		singleton = nullptr;
	}
}