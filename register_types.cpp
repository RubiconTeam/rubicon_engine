#include "register_types.h"
#include "core/object/class_db.h"
#include "modules/rubicon/beat_syncer.h"

void initialize_rubicon_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		return;

	// Register classes
	
	GDREGISTER_CLASS(BeatSyncer);
}

void uninitialize_rubicon_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		return;
}