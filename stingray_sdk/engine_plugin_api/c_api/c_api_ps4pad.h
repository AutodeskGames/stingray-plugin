#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* This class is solely for managing PS4 Gamepads connected to a PC. */
struct PS4PadCApi
{
	void (*set_light_bar_color)(CApiInputControllerPtr ps4pad_input_controller, ConstQuaternionPtr color);
	unsigned (*user_id)(CApiInputControllerPtr ps4pad_input_controller);
};

#ifdef __cplusplus
}
#endif
