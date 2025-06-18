#ifndef RUBICON_CHARACTER_3D_H
#define RUBICON_CHARACTER_3D_H

#include "core/object/class_db.h"
#include "scene/3d/node_3d.h"
#include "scene/animation/animation_player.h"
#include "rubicon_character_controller.h"

class RubiconCharacter3D : public Node3D {
    GDCLASS(RubiconCharacter3D, Node3D);

public:
    Node3D* reference_visual = nullptr;

    void set_reference_visual(Node3D* p_visual);
    Node3D* get_reference_visual() const;

    RubiconCharacterController* get_character_controller() const;

    PackedStringArray get_configuration_warnings() const override;

protected:
    void _notification(int p_what);
    static void _bind_methods();

private:
    RubiconCharacterController* _character_controller = nullptr;
};

#endif // RUBICON_CHARACTER_3D_H