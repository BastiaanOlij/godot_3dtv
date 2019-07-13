////////////////////////////////////////////////////////////////////////////
// This is a simple module that outputs 3D stereo side by side output for
// use with a 3D monitor or TV. 


// Written by Bastiaan "Mux213" Olij, with loads of help from Thomas "Karroffel" Herzog

#include "godot_3dtv.h"

void GDN_EXPORT godot_gdnative_singleton() {
	if (arvr_api != NULL) {
		arvr_api->godot_arvr_register_interface(&interface_struct);
	}
}

void GDN_EXPORT godot_nativescript_init(void *p_handle) {
	if (nativescript_api != NULL) {
		// nothing to do here yet
	}
}