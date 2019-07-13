////////////////////////////////////////////////////////////////////////////////////////////////
// Just exposing an interface to the ImageTexture functions reachable in GDNative

#ifndef OS_H
#define OS_H

#include "GodotCalls.h"

class OS {
private:
	godot_object *_owner;
	static OS *_singleton;

public:
	static inline OS *get_singleton() {
		if (!OS::_singleton) {
			OS::_singleton = new OS();
		}
		return OS::_singleton;
	}

	int64_t get_ticks_msec();
	godot_vector2 get_screen_size(const int64_t screen = -1);

	OS();
};

#endif /* !OS_H */
