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

    float MeasureToMs(float measure, float bpm, float timeSignatureNumerator) const;
    float BeatsToMs(float beat, float bpm);
    float StepsToMs(float step, float bpm, float timeSignatureDenominator);
    //float MsToMeasures()

protected:
    static Conductor *singleton;

	static void _bind_methods();
};

#endif // CONDUCTOR_H