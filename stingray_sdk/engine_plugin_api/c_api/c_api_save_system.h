#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct SaveSystemCApi
{
	int		(*exists) ();
	void	(*close) (SaveToken);

	struct SaveSystemProgress	(*get_progress) (SaveToken);
	enum SaveSystemError		(*get_loaded_data) (SaveToken, save_system_data_callback);

	SaveToken (*auto_load) (const char* filename);
	SaveToken (*auto_save) (const char* filename, struct SaveParameter* parameter_array, unsigned num_parameters);
};

#ifdef __cplusplus
}
#endif
