////////////////////////////////////////////////////////////////////////////
// This is a simple module that outputs 3D stereo side by side output for
// use with a 3D monitor or TV. 

// Written by Bastiaan "Mux213" Olij, with loads of help from Thomas "Karroffel" Herzog

#ifndef GODOT_3DTV_H
#define GODOT_3DTV_H

#include "GodotCalls.h"
#include "ARVRInterface.h"

// declare our public functions for our ARVR Interface
#ifdef __cplusplus
extern "C" {
#endif

void GDN_EXPORT godot_gdnative_singleton();
void GDN_EXPORT godot_nativescript_init(void *p_handle);

#ifdef __cplusplus
}
#endif

#endif /* !GODOT_3DTV_H */
