#ifndef RUBICON_CHARACTER_2D_H
#define RUBICON_CHARACTER_2D_H

#include "core/object/class_db.h"
#include "scene/2d/node_2d.h"
#include "scene/animation/animation_player.h"
#include "rubicon_character_controller.h"

class RubiconCharacter2D : public Node2D {
    GDCLASS(RubiconCharacter2D, Node2D);

public:
    Node2D* reference_visual = nullptr;

    void set_reference_visual(Node2D* p_visual);
    Node2D* get_reference_visual() const;

    RubiconCharacterController* get_character_controller() const;

    PackedStringArray get_configuration_warnings() const override;

protected:
    void _notification(int p_what);
    static void _bind_methods();

private:
    RubiconCharacterController* _character_controller = nullptr;
};

#endif // RUBICON_CHARACTER_2D_H