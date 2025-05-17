#ifndef RUBICON_CHARACTER_ICON_DATA_H
#define RUBICON_CHARACTER_ICON_DATA_H

#include "core/io/resource.h"
#include "scene/resources/sprite_frames.h"

typedef RenderingServer::CanvasItemTextureFilter TextureFilter;

class RubiconCharacterIconData : public Resource {
    GDCLASS(RubiconCharacterIconData, Resource);

public:
    Ref<SpriteFrames> icon;
    Point2 offset;
    Point2 scale;
    Color color = Color(1, 1, 1, 1);
    TextureFilter filter = TextureFilter::CANVAS_ITEM_TEXTURE_FILTER_LINEAR;

    void set_icon(const Ref<SpriteFrames> p_icon);
    Ref<SpriteFrames> get_icon() const;

    void set_offset(const Point2 p_offset);
    Point2 get_offset() const;

    void set_scale(const Point2 p_scale);
    Point2 get_scale() const;

    void set_color(const Color p_color);
    Color get_color() const;

    void set_filter(const TextureFilter p_filter);
    TextureFilter get_filter() const;

protected:
    static void _bind_methods();
};

#endif