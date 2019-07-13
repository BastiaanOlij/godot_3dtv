////////////////////////////////////////////////////////////////////////////////////////////////
// Just some code setting up access to our APIs in Godot

#ifndef GODOT_CALLS_H
#define GODOT_CALLS_H

#include <gdnative_api_struct.gen.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// forward declarations
extern const godot_gdnative_core_api_struct *api;
extern const godot_gdnative_ext_arvr_api_struct *arvr_api;
extern const godot_gdnative_ext_nativescript_api_struct *nativescript_api;

#ifdef __cplusplus
extern "C" {
#endif

void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *p_options);
void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *p_options);

// callbacks
int64_t ___godot_icall_int(godot_method_bind *mb, godot_object *inst);
godot_vector2 ___godot_icall_Vector2_int(godot_method_bind *mb, godot_object *inst, const int arg0);

#ifdef __cplusplus
}
#endif

#endif /* !GODOT_CALLS_H */
