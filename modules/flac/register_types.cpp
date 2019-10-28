#include "register_types.h"

#include "audio_stream_flac.h"

#ifdef TOOLS_ENABLED
#include "core/engine.h"
#include "resource_importer_flac.h"
#endif

void register_flac_types() {

#ifdef TOOLS_ENABLED
	if (Engine::get_singleton()->is_editor_hint()) {
		Ref<ResourceImporterFLAC> flac_import;
		flac_import.instance();
		ResourceFormatImporter::get_singleton()->add_importer(flac_import);
	}
#endif
	ClassDB::register_class<AudioStreamFLAC>();
}

void unregister_flac_types() {
}
