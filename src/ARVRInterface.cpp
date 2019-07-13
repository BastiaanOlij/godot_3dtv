////////////////////////////////////////////////////////////////////////////
// This is a simple module that outputs 3D stereo side by side output for
// use with a 3D monitor or TV. 

// Written by Bastiaan "Mux213" Olij, with loads of help from Thomas "Karroffel" Herzog

#include "ARVRInterface.h"
#include "OS.h"

#include <math.h>

void *godot_arvr_constructor(godot_object *p_instance) {
	godot_string ret;

	arvr_data_struct *arvr_data = (arvr_data_struct *)api->godot_alloc(sizeof(arvr_data_struct));
	arvr_data->instance = p_instance;
	arvr_data->is_initialised = false;
	arvr_data->fov = 60;
	arvr_data->look_at_dist = 1.0;
	arvr_data->iod_cm = 6.1;
	arvr_data->eye_height = 1.80;

	return arvr_data;
}

void godot_arvr_destructor(void *p_data) {
	if (p_data != NULL) {
		api->godot_free(p_data);
	}
}

godot_string godot_arvr_get_name(const void *p_data) {
	godot_string ret;

	char name[] = "3DTV";
	api->godot_string_new(&ret);
	api->godot_string_parse_utf8(&ret, name);

	return ret;
}

godot_int godot_arvr_get_capabilities(const void *p_data) {
	godot_int ret;

	ret = 2; // 2 = ARVR_STEREO

	return ret;
}

godot_bool godot_arvr_get_anchor_detection_is_enabled(const void *p_data) {
	godot_bool ret;

	ret = false; // does not apply here

	return ret;
}

void godot_arvr_set_anchor_detection_is_enabled(void *p_data, bool p_enable) {
	// we ignore this, not supported in this interface!
}

godot_bool godot_arvr_is_stereo(const void *p_data) {
	godot_bool ret;

	// printf("godot_3dtv.arvr_is_stereo()\n");
	ret = true;

	return ret;
}

godot_bool godot_arvr_is_initialized(const void *p_data) {
	godot_bool ret;
	arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;

	ret = arvr_data == NULL ? false : arvr_data->is_initialised;

	return ret;
}
 
godot_bool godot_arvr_initialize(void *p_data) {
	godot_bool ret;
	arvr_data_struct * arvr_data = (arvr_data_struct *) p_data;

	if (!arvr_data->is_initialised) {
		// initialise this interface, so initialize any 3rd party libraries, open up HMD window if required, etc.


		// note, this will be made the primary interface by ARVRInterfaceGDNative
		arvr_data->is_initialised = true;
	}

	// and return our result
	ret = arvr_data->is_initialised;
	return ret;
}

void godot_arvr_uninitialize(void *p_data) {
	arvr_data_struct * arvr_data = (arvr_data_struct *) p_data;

	if (arvr_data->is_initialised) {
		// note, this will already be removed as the primary interface by ARVRInterfaceGDNative

		// cleanup if needed

		arvr_data->is_initialised = false;
	}
}

godot_vector2 godot_arvr_get_recommended_render_targetsize(const void *p_data) {
	godot_vector2 size;

	// printf("godot_3dtv.arvr_get_recommended_render_targetsize()\n");
	size = OS::get_singleton()->get_screen_size();

	return size;
}

godot_transform godot_arvr_get_transform_for_eye(void *p_data, godot_int p_eye, godot_transform *p_cam_transform) {
	arvr_data_struct * arvr_data = (arvr_data_struct *) p_data;
	godot_transform transform_for_eye;
	godot_transform hmd_transform;
	godot_transform reference_frame = arvr_api->godot_arvr_get_reference_frame();
	godot_transform ret;
	godot_vector3 offset;
	godot_real world_scale = arvr_api->godot_arvr_get_worldscale();

	// printf("godot_3dtv.arvr_get_transform_for_eye()\n");

	// create our transform from head center to eye
	api->godot_transform_new_identity(&transform_for_eye);

/* we don't move the camera, it's already taken into account in the projection matrix
	if (p_eye == 1) {
		// left eye
		api->godot_vector3_new(&offset, -arvr_data->iod_cm * 0.01 * 0.5 * world_scale, 0.0, 0.0);
		transform_for_eye = api->godot_transform_translated(&transform_for_eye, &offset);
	} else if (p_eye == 2) {
		// right eye
		api->godot_vector3_new(&offset, arvr_data->iod_cm * 0.01 * 0.5 * world_scale, 0.0, 0.0);
		transform_for_eye = api->godot_transform_translated(&transform_for_eye, &offset);
	} else {
		// leave in the middle, mono
	}
*/

	// now determine our HMD positional tracking, we have none in this interface...
	api->godot_transform_new_identity(&hmd_transform);
	api->godot_vector3_new(&offset, 0.0, arvr_data->eye_height * world_scale, 0.0);
	hmd_transform = api->godot_transform_translated(&hmd_transform, &offset);

	// Now construct our full transform, the order may be in reverse, have to test :)
	ret = *p_cam_transform;
	ret = api->godot_transform_operator_multiply(&ret, &reference_frame);
	ret = api->godot_transform_operator_multiply(&ret, &hmd_transform);
	ret = api->godot_transform_operator_multiply(&ret, &transform_for_eye);

	return ret;
}

void arvr_set_frustum(godot_real *p_projection, godot_real p_left, godot_real p_right, godot_real p_bottom, godot_real p_top, godot_real p_near, godot_real p_far) {
	godot_real x = 2.0 * p_near / (p_right - p_left);
	godot_real y = 2.0 * p_near / (p_top - p_bottom);

	godot_real a = (p_right + p_left) / (p_right - p_left);
	godot_real b = (p_top + p_bottom) / (p_top - p_bottom);
	godot_real c = -(p_far + p_near) / (p_far - p_near);
	godot_real d = -2.0 * p_far * p_near / (p_far - p_near);

	p_projection[0] = x;
	p_projection[1] = 0.0;
	p_projection[2] = 0.0;
	p_projection[3] = 0.0;
	p_projection[4] = 0.0;
	p_projection[5] = y;
	p_projection[6] = 0.0;
	p_projection[7] = 0.0;
	p_projection[8] = a;
	p_projection[9] = b;
	p_projection[10] = c;
	p_projection[11] = -1.0;
	p_projection[12] = 0.0;
	p_projection[13] = 0.0;
	p_projection[14] = d;
	p_projection[15] = 0.0;
}

void godot_arvr_fill_projection_for_eye(void *p_data, godot_real *p_projection, godot_int p_eye, godot_real p_aspect, godot_real p_z_near, godot_real p_z_far) {
	arvr_data_struct * arvr_data = (arvr_data_struct *) p_data;

	float	fovy	= arvr_data->fov;
	float	radians	= DTR * fovy / 2.0;
	float	wd2		= p_z_near * tan(radians);
	float	ndf1	= p_z_near / arvr_data->look_at_dist;
	float	left	= -p_aspect * wd2;
	float	right	=  p_aspect * wd2;
	float	top		=  wd2;
	float	bottom	= -wd2;

	if (p_eye == 1) { // left
		left	-= 0.5 * arvr_data->iod_cm * ndf1 * 0.01;
		right	-= 0.5 * arvr_data->iod_cm * ndf1 * 0.01;
	} else if (p_eye == 2) { // right
		left	+= 0.5 * arvr_data->iod_cm * ndf1 * 0.01;
		right	+= 0.5 * arvr_data->iod_cm * ndf1 * 0.01;
	};
	
	arvr_set_frustum(p_projection, left, right, bottom, top, p_z_near, p_z_far);
}

void godot_arvr_commit_for_eye(void *p_data, godot_int p_eye, godot_rid *p_render_target, godot_rect2 *p_screen_rect) {
	// This function is responsible for outputting the final render buffer for each eye. 
	// p_screen_rect will only have a value when we're outputting to the main viewport.

	// For an interface that must output to the main viewport (such as with mobile VR) we should give an error when p_screen_rect is not set
	// For an interface that outputs to an external device we should render a copy of one of the eyes to the main viewport if p_screen_rect is set, and only output to the external device if not.

	arvr_api->godot_arvr_blit(p_eye, p_render_target, p_screen_rect);
}

void godot_arvr_process(void *p_data) {
	// this method gets called before every frame is rendered, here is where you should update tracking data, update controllers, etc.

}

int godot_arvr_get_external_texture_for_eye(void *p_data, int p_eye) {
	// nothing to do here for now.

	return 0;
}

void godot_arvr_notification(void *p_data, int p_what) {
	// nothing to do here for now.
}

const godot_arvr_interface_gdnative interface_struct = {
	GODOTVR_API_MAJOR, GODOTVR_API_MINOR,
	godot_arvr_constructor,
	godot_arvr_destructor,
	godot_arvr_get_name,
	godot_arvr_get_capabilities,
	godot_arvr_get_anchor_detection_is_enabled,
	godot_arvr_set_anchor_detection_is_enabled,
	godot_arvr_is_stereo,
	godot_arvr_is_initialized,
	godot_arvr_initialize,
	godot_arvr_uninitialize,
	godot_arvr_get_recommended_render_targetsize,
	godot_arvr_get_transform_for_eye,
	godot_arvr_fill_projection_for_eye,
	godot_arvr_commit_for_eye,
	godot_arvr_process,
	// only available in Godot 3.2+
	godot_arvr_get_external_texture_for_eye,
	godot_arvr_notification
};
