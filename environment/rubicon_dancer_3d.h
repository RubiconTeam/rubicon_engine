#ifndef RUBICON_DANCER_3D_H
#define RUBICON_DANCER_3D_H

#include "core/object/class_db.h"
#include "rubicon_dancer_controller.h"
#include "scene/3d/node_3d.h"
#include "scene/main/node.h"

class RubiconDancer3D : public Node3D {
    GDCLASS(RubiconDancer3D, Node3D);

public:
    Ref<RubiconDancerData> dancer_data;
    Node3D* reference_visual = nullptr;

    void set_reference_visual(Node3D* p_visual);
    Node3D* get_reference_visual() const;

    RubiconDancerController* get_dancer_controller() const;

    PackedStringArray get_configuration_warnings() const override;

protected:
    void _notification(int p_what);
    static void _bind_methods();

private:
    RubiconDancerController* _dancer_controller = nullptr;
};

#endif