#include "register_types.h"
#include "core/object/class_db.h"
#include "rubicon_beat_syncer.h"
#include "data/rubicon_character_icon_data.h"
#include "environment/rubicon_dancer_controller.h"
#include "environment/rubicon_dancer_2d.h"
#include "environment/rubicon_dancer_3d.h"
#include "environment/rubicon_character_controller.h"

void initialize_rubicon_engine_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		return;

	// Rubicon
	GDREGISTER_CLASS(RubiconBeatSyncer);

	// Rubicon.Data
	GDREGISTER_CLASS(RubiconCharacterIconData);

	// Rubicon.Environment
	GDREGISTER_CLASS(RubiconDancerController);
	GDREGISTER_CLASS(RubiconDancer2D);
	GDREGISTER_CLASS(RubiconDancer3D);
	GDREGISTER_CLASS(RubiconCharacterController);
}

void uninitialize_rubicon_engine_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		return;
}