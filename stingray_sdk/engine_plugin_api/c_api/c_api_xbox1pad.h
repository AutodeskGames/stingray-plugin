#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct XBoxOnePadCApi
{
	unsigned (*user_id)(CApiInputControllerPtr xboxone_pad_input_controller);
};

#ifdef __cplusplus
}
#endif
