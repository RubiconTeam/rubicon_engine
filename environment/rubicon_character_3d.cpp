#include "rubicon_character_3d.h"

void RubiconCharacter3D::set_reference_visual(Node3D* p_visual) {
    reference_visual = p_visual;
}

Node3D* RubiconCharacter3D::get_reference_visual() const {
    if (reference_visual)
        return reference_visual;
    
    return Object::cast_to<Node3D>(Variant());
}

RubiconCharacterController* RubiconCharacter3D::get_character_controller() const {
    if (_character_controller)
        return _character_controller;
    
    return Object::cast_to<RubiconCharacterController>(Variant());
}

PackedStringArray RubiconCharacter3D::get_configuration_warnings() const {
    PackedStringArray warnings = Node3D::get_configuration_warnings();

    if (_character_controller == nullptr)
        warnings.push_back(RTR("This node has no controller, so it won't have any functionality beyond a regular Node3D.\nConsider adding a node that at least inherits RubiconCharacterController."));
    
    return warnings;
}

void RubiconCharacter3D::_notification(int p_what) {
    switch (p_what) {
        case NOTIFICATION_CHILD_ORDER_CHANGED: {
            for (int i = 0; i < get_child_count(); i++) {
                Node* child = get_child(i);
                
                _character_controller = Object::cast_to<RubiconCharacterController>(child);
                if (_character_controller)
                    break;
            }
        } break;
    }
}

void RubiconCharacter3D::_bind_methods() {
    // Getters and Setters
    ClassDB::bind_method(D_METHOD("set_reference_visual", "visual"), &RubiconCharacter3D::set_reference_visual);
    ClassDB::bind_method("get_reference_visual", &RubiconCharacter3D::get_reference_visual);
    
    // Properties
    ADD_GROUP("References", "reference_");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "reference_visual", PROPERTY_HINT_NODE_TYPE, "Node3D"), "set_reference_visual", "get_reference_visual");

    // Methods
    ClassDB::bind_method("get_character_controller", &RubiconCharacter3D::get_character_controller);
}