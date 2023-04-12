#include "register_types.h"

#include "audio_stream_flac.h"

#ifdef TOOLS_ENABLED
#include "core/config/engine.h"
#include "resource_importer_flac.h"
#endif

void initialize_flac_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

#ifdef TOOLS_ENABLED
	if (Engine::get_singleton()->is_editor_hint()) {
		Ref<ResourceImporterFLAC> flac_import;
		flac_import.instantiate();
		ResourceFormatImporter::get_singleton()->add_importer(flac_import);
	}
#endif
	GDREGISTER_CLASS(AudioStreamFLAC);
}

void uninitialize_flac_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}
