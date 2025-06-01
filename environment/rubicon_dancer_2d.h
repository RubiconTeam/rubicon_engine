#ifndef RUBICON_DANCER_2D_H
#define RUBICON_DANCER_2D_H

#include "core/object/class_db.h"
#include "rubicon_dancer_controller.h"
#include "scene/2d/node_2d.h"
#include "scene/main/node.h"

class RubiconDancer2D : public Node2D {
    GDCLASS(RubiconDancer2D, Node2D);

public:
    Node2D* reference_visual = nullptr;

    void set_reference_visual(Node2D* p_visual);
    Node2D* get_reference_visual() const;

    RubiconDancerController* get_dancer_controller() const;

    PackedStringArray get_configuration_warnings() const override;

protected:
    void _notification(int p_what);
    static void _bind_methods();

private:
    RubiconDancerController* _dancer_controller = nullptr;
};

#endif