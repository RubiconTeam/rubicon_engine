#include "register_types.h"

#include "core/config/engine.h"
#include "core/object/class_db.h"
#include "core/conductor.h"

static Conductor *ConductorPtr;

void initialize_rubicon_plus_plus_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		return;

    GDREGISTER_CLASS(Conductor);
    ConductorPtr = memnew(Conductor);
    Engine::get_singleton()->add_singleton(Engine::Singleton("Conductor", Conductor::get_singleton()));   
}

void uninitialize_rubicon_plus_plus_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		return;

    Engine::get_singleton()->remove_singleton("Conductor");
	memdelete(ConductorPtr);
}