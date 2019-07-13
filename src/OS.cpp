////////////////////////////////////////////////////////////////////////////////////////////////
// Just exposing an interface to the OS functions reachable in GDNative
// Basically just ported some of the functions in the cpp_bindings for use in C

// Note, even though this is pure C code, we're using the C++ compiler as
// Microsoft never updated their C compiler to understand more modern dialects
// and openvr uses pesky things such as namespaces

#include "OS.h"

OS *OS::_singleton = NULL;

int64_t OS::get_ticks_msec() {
	static godot_method_bind *mb = NULL;
	if (mb == NULL) {
		mb = api->godot_method_bind_get_method("_OS", "get_ticks_msec");
	}
	return ___godot_icall_int(mb, _owner);
}

godot_vector2 OS::get_screen_size(const int64_t screen) {
	static godot_method_bind *mb = NULL;
	if (mb == NULL) {
		mb = api->godot_method_bind_get_method("_OS", "get_screen_size");
	}
	return ___godot_icall_Vector2_int(mb, _owner, screen);
}

OS::OS() {
	_owner = api->godot_global_get_singleton((char *)"OS");
}
