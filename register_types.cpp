#include "register_types.h"
#include "core/object/class_db.h"
#include "modules/rubicon/beat_syncer.h"
#include "modules/rubicon/data/rubicon_dancer_data.h"
#include "modules/rubicon/environment/rubicon_dancer_controller.h"

void initialize_rubicon_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		return;

	// Rubicon
	GDREGISTER_CLASS(BeatSyncer);

	// Rubicon.Environment
	GDREGISTER_CLASS(RubiconDancerController)

	// Rubicon.Data
	GDREGISTER_CLASS(BeatSyncerData);
	GDREGISTER_CLASS(RubiconDancerData)
}

void uninitialize_rubicon_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		return;
}