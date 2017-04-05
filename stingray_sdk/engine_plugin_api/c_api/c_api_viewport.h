#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ViewportCApi
{
	void (*set_rect) (ViewportPtr, float x, float y, float width, float height);
};

#ifdef __cplusplus
}
#endif
