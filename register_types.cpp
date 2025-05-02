#include "register_types.h"
#include "core/object/class_db.h"
#include "modules/rubicon/beat_syncer.h"

void initialize_rubicon_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		return;

	// Rubicon
	GDREGISTER_CLASS(BeatSyncer);

	// Rubicon.Data
	GDREGISTER_CLASS(BeatSyncerData);
}

void uninitialize_rubicon_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		return;
}