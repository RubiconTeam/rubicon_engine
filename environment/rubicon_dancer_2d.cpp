#include "rubicon_dancer_2d.h"

void RubiconDancer2D::set_reference_visual(Node2D* p_visual) {
    reference_visual = p_visual;
}

Node2D* RubiconDancer2D::get_reference_visual() const {
    if (reference_visual)
        return reference_visual;
    
    return Object::cast_to<Node2D>(Variant());
}

RubiconDancerController* RubiconDancer2D::get_dancer_controller() const {
    if (_dancer_controller)
        return _dancer_controller;
    
    return Object::cast_to<RubiconDancerController>(Variant());
}

PackedStringArray RubiconDancer2D::get_configuration_warnings() const {
    PackedStringArray warnings = Node2D::get_configuration_warnings();

    if (_dancer_controller == nullptr)
        warnings.push_back(RTR("This node has no controller, so it won't have any functionality beyond a regular Node2D.\nConsider adding a node that at least inherits RubiconDancerController."));
    
    return warnings;
}

void RubiconDancer2D::_notification(int p_what) {
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

void RubiconDancer2D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_reference_visual", "visual"), &RubiconDancer2D::set_reference_visual);
    ClassDB::bind_method("get_reference_visual", &RubiconDancer2D::get_reference_visual);
    
    ADD_GROUP("References", "reference_");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "reference_visual", PROPERTY_HINT_NODE_TYPE, "Node2D"), "set_reference_visual", "get_reference_visual");

    ClassDB::bind_method("get_dancer_controller", &RubiconDancer2D::get_dancer_controller);
}