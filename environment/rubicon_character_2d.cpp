#include "rubicon_character_2d.h"

void RubiconCharacter2D::set_reference_visual(Node2D* p_visual) {
    reference_visual = p_visual;
}

Node2D* RubiconCharacter2D::get_reference_visual() const {
    return reference_visual;
}

RubiconCharacterController* RubiconCharacter2D::get_character_controller() const {
    return _character_controller;
}

PackedStringArray RubiconCharacter2D::get_configuration_warnings() const {
    PackedStringArray warnings = Node2D::get_configuration_warnings();

    if (_character_controller == nullptr)
        warnings.push_back(RTR("This node has no controller, so it won't have any functionality beyond a regular Node2D.\nConsider adding a node that at least inherits RubiconCharacterController."));
    
    return warnings;
}

void RubiconCharacter2D::_notification(int p_what) {
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

void RubiconCharacter2D::_bind_methods() {
    // Getters and Setters
    ClassDB::bind_method(D_METHOD("set_reference_visual", "visual"), &RubiconCharacter2D::set_reference_visual);
    ClassDB::bind_method("get_reference_visual", &RubiconCharacter2D::get_reference_visual);
    
    // Properties
    ADD_GROUP("References", "reference_");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "reference_visual", PROPERTY_HINT_NODE_TYPE, "Node2D"), "set_reference_visual", "get_reference_visual");

    // Methods
    ClassDB::bind_method("get_character_controller", &RubiconCharacter2D::get_character_controller);
}