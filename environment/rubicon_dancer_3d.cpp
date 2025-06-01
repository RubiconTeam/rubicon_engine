#include "rubicon_dancer_3d.h"

void RubiconDancer3D::set_reference_visual(Node3D* p_visual) {
    reference_visual = p_visual;
}

Node3D* RubiconDancer3D::get_reference_visual() const {
    return reference_visual;
}

RubiconDancerController* RubiconDancer3D::get_dancer_controller() const {
    return _dancer_controller;
}

PackedStringArray RubiconDancer3D::get_configuration_warnings() const {
    PackedStringArray warnings = Node3D::get_configuration_warnings();

    if (_dancer_controller == nullptr)
        warnings.push_back(RTR("This node has no controller, so it won't have any functionality beyond a regular Node3D.\nConsider adding a node that at least inherits RubiconDancerController."));
    
    return warnings;
}

void RubiconDancer3D::_notification(int p_what) {
    switch (p_what) {
        case NOTIFICATION_CHILD_ORDER_CHANGED: {
            for (int i = 0; i < get_child_count(); i++) {
                Node* child = get_child(i);

                _dancer_controller = Object::cast_to<RubiconDancerController>(child);
                if (_dancer_controller)
                    break;
            }
        } break;
    }
}

void RubiconDancer3D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_reference_visual", "visual"), &RubiconDancer3D::set_reference_visual);
    ClassDB::bind_method("get_reference_visual", &RubiconDancer3D::get_reference_visual);
    
    ADD_GROUP("References", "reference_");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "reference_visual", PROPERTY_HINT_NODE_TYPE, "Node2D"), "set_reference_visual", "get_reference_visual");

    ClassDB::bind_method("get_dancer_controller", &RubiconDancer3D::get_dancer_controller);
}