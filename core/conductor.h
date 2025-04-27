#ifndef CONDUCTOR_H
#define CONDUCTOR_H

#include "core/object/object.h"

#include "core/object/class_db.h"

class Conductor : public Object {
    GDCLASS(Conductor, Object);

public:
    Conductor();
    ~Conductor();

    static Conductor *get_singleton();

    float measure_to_ms(float p_measure, float p_bpm, float p_time_signature_numerator) const;

protected:
    static Conductor *singleton;

	static void _bind_methods();
};

#endif // CONDUCTOR_H