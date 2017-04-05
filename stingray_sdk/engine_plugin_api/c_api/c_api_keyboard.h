#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct KeyboardCApi
{
	const int *(*keystrokes)(CApiInputControllerPtr keyboard_input_controller, unsigned *out_num_keystrokes);
};

#ifdef __cplusplus
}
#endif


