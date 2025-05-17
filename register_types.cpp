#include "register_types.h"
#include "core/object/class_db.h"
#include "rubicon_beat_syncer.h"
#include "data/rubicon_dancer_data.h"
#include "environment/rubicon_dancer_controller.h"
#include "environment/rubicon_dancer_2d.h"
#include "environment/rubicon_dancer_3d.h"

void initialize_rubicon_engine_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		return;

	// Rubicon
	GDREGISTER_CLASS(RubiconBeatSyncer);

	// Rubicon.Environment
	GDREGISTER_CLASS(RubiconDancerController);
	//GDREGISTER_CLASS(RubiconDancer2D);
	//GDREGISTER_CLASS(RubiconDancer3D);

	// Rubicon.Data
	GDREGISTER_CLASS(RubiconBeatSyncerData);
	GDREGISTER_CLASS(RubiconDancerData);
}

void uninitialize_rubicon_engine_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		return;
}