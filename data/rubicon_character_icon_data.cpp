#include "rubicon_character_icon_data.h"

void RubiconCharacterIconData::set_icon(Ref<SpriteFrames> p_icon) {
    icon = p_icon;
}

Ref<SpriteFrames> RubiconCharacterIconData::get_icon() const {
    return icon;
}

void RubiconCharacterIconData::set_offset(Point2 p_offset) {
    offset = p_offset;
}

Point2 RubiconCharacterIconData::get_offset() const {
    return offset;
}

void RubiconCharacterIconData::set_scale(Point2 p_scale) {
    scale = p_scale;
}

Point2 RubiconCharacterIconData::get_scale() const {
    return scale;
}

void RubiconCharacterIconData::set_color(Color p_color) {
    icon = p_color;
}

Color RubiconCharacterIconData::get_color() const {
    return color;
}

void RubiconCharacterIconData::set_filter(TextureFilter p_filter) {
    icon = p_filter;
}

TextureFilter RubiconCharacterIconData::get_filter() const {
    return filter;
}

void RubiconCharacterIconData::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_icon", "icon"), &RubiconCharacterIconData::set_icon);
    ClassDB::bind_method("get_icon", &RubiconCharacterIconData::get_icon);

    ClassDB::bind_method(D_METHOD("set_offset", "offset"), &RubiconCharacterIconData::set_offset);
    ClassDB::bind_method("get_offset", &RubiconCharacterIconData::get_offset);

    ClassDB::bind_method(D_METHOD("set_scale", "scale"), &RubiconCharacterIconData::set_scale);
    ClassDB::bind_method("get_scale", &RubiconCharacterIconData::get_scale);

    ClassDB::bind_method(D_METHOD("set_color", "color"), &RubiconCharacterIconData::set_color);
    ClassDB::bind_method("get_color", &RubiconCharacterIconData::get_color);

    ClassDB::bind_method(D_METHOD("set_filter", "filter"), &RubiconCharacterIconData::set_filter);
    ClassDB::bind_method("get_filter", &RubiconCharacterIconData::get_filter);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "SpriteFrames"), "set_icon", "get_icon");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "offset"), "set_offset", "get_offset");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "scale"), "set_scale", "get_scale");
    ADD_PROPERTY(PropertyInfo(Variant::COLOR, "color"), "set_color", "get_color");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "filter", PROPERTY_HINT_ENUM, "Inherit,Nearest,Linear"), "set_filter", "get_filter");
}