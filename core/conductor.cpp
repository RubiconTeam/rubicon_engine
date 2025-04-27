#include "modules/rubicon_plus_plus/core/conductor.h"

Conductor *Conductor::singleton = nullptr;

Conductor *Conductor::get_singleton() {
	return singleton;
}

float Conductor::measure_to_ms(float p_measure, float p_bpm, float p_time_signature_numerator) const {
    return p_measure * (60000.0 / (p_bpm / p_time_signature_numerator));
}

void Conductor::_bind_methods() {
    ClassDB::bind_method(D_METHOD("measure_to_ms", "measure", "bpm", "time_signature_numerator"), &Conductor::measure_to_ms);
}

Conductor::Conductor() {
	singleton = this;
}

Conductor::~Conductor() {
	if (singleton == this) {
		singleton = nullptr;
	}
}