#ifndef RUBICON_DANCER_2D_H
#define RUBICON_DANCER_2D_H

#include "rubicon_dancer_controller.h"
#include "scene/2d/node_2d.h"

class RubiconDancer2D : public Node2D {
    GDCLASS(RubiconDancer2D, Node2D);

public:
    Ref<RubiconDancerData> dancer_data;
    Ref<RubiconDancerController> dancer_controller;
    Ref<Node2D> sprite;
    
    void set_dancer_data(const Ref<RubiconDancerData> p_dancer_data);
    Ref<RubiconDancerData> get_dancer_data() const;

    void set_dancer_controller(const Ref<RubiconDancerController> p_dancer_controller);
    Ref<RubiconDancerController> get_dancer_controller() const;

    void set_sprite(const Ref<Node2D> p_sprite);
    Ref<Node2D> get_sprite() const;

protected:
    static void _bind_methods();
};

#endif