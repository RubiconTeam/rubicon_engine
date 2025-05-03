#include "rubicon_dancer_2d.h"

void RubiconDancer2D::set_dancer_data(const Ref<RubiconDancerData> p_dancer_data) {
    dancer_data = p_dancer_data;
}

Ref<RubiconDancerData> RubiconDancer2D::get_dancer_data() const {
    return dancer_data;
}

void RubiconDancer2D::set_dancer_controller(const Ref<RubiconDancerController> p_dancer_controller) {
    dancer_controller = p_dancer_controller;
}

Ref<RubiconDancerController> RubiconDancer2D::get_dancer_controller() const {
    return dancer_controller;
}

void RubiconDancer2D::set_sprite(const Ref<Node2D> p_sprite) {
    sprite = p_sprite;
}

Ref<Node2D> RubiconDancer2D::get_sprite() const {
    return sprite;
}

void RubiconDancer2D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_dancer_data", "dancer_data"), &RubiconDancer2D::set_dancer_data);
    ClassDB::bind_method("get_dancer_data", &RubiconDancer2D::get_dancer_data);
    
    ClassDB::bind_method(D_METHOD("set_dancer_controller", "dancer_controller"), &RubiconDancer2D::set_dancer_controller);
    ClassDB::bind_method("get_dancer_controller", &RubiconDancer2D::get_dancer_controller);
    
    ClassDB::bind_method(D_METHOD("set_sprite", "sprite"), &RubiconDancer2D::set_sprite);
    ClassDB::bind_method("get_sprite", &RubiconDancer2D::get_sprite);
    
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "dancer_data", PROPERTY_HINT_RESOURCE_TYPE, "RubiconDancerData"), "set_dancer_data", "get_dancer_data");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "dancer_controller", PROPERTY_HINT_NODE_TYPE, "RubiconDancerController"), "set_dancer_controller", "get_dancer_controller");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "sprite", PROPERTY_HINT_NODE_TYPE, "Node2D"), "set_sprite", "get_sprite");
}