#ifndef RUBICON_DANCER_3D_H
#define RUBICON_DANCER_3D_H

#include "rubicon_dancer_controller.h"
#include "scene/3d/node_3d.h"

class RubiconDancer3D : public Node3D {
    GDCLASS(RubiconDancer3D, Node3D);

public:
    Ref<RubiconDancerData> dancer_data;
    Ref<RubiconDancerController> dancer_controller;
    Ref<Node3D> sprite;
    
    void set_dancer_data(const Ref<RubiconDancerData> p_dancer_data);
    Ref<RubiconDancerData> get_dancer_data() const;

    void set_dancer_controller(const Ref<RubiconDancerController> p_dancer_controller);
    Ref<RubiconDancerController> get_dancer_controller() const;

    void set_sprite(const Ref<Node3D> p_sprite);
    Ref<Node3D> get_sprite() const;

protected:
    static void _bind_methods();
};

#endif