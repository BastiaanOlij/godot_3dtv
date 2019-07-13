////////////////////////////////////////////////////////////////////////////
// This is a simple module that outputs 3D stereo side by side output for
// use with a 3D monitor or TV. 

// Written by Bastiaan "Mux213" Olij, with loads of help from Thomas "Karroffel" Herzog

#ifndef ARVR_INTERFACE_H
#define ARVR_INTERFACE_H

#include "GodotCalls.h"

extern const godot_arvr_interface_gdnative interface_struct;

#define DTR 0.0174532925

typedef struct arvr_data_struct {
	godot_object * instance;
	bool is_initialised;
	float iod_cm;
	float fov;
	float look_at_dist;
	float eye_height;
} arvr_data_struct;

#endif /* !ARVR_INTERFACE_H */
