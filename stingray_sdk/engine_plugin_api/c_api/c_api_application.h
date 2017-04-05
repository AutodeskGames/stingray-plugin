#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ApplicationCApi
{
	unsigned	(*num_worlds) ();
	WorldPtr	(*world) (unsigned index);
	WorldPtr	(*new_world) (ConstWorldConfigPtr optional);
	WorldPtr	(*main_world) ();
	void		(*release_world) (WorldPtr);
	void		(*render_world) (WorldPtr, ConstCameraPtr, ConstViewportPtr, ConstShadingEnvironmentPtr, ConstWindowPtr optional);
	CApiWorldConfig (*get_default_world_settings) ();

	const char* (*build) ();
	const char* (*platform) ();
	const char* (*build_identifier) ();
	const char* (*sysinfo) ();
	ConstConfigRootPtr (*settings_root) ();

	ViewportPtr (*create_viewport) (WorldPtr, unsigned viewport_template_name_id32);
	void		(*destroy_viewport) (WorldPtr, ViewportPtr);
	unsigned	(*can_get) (uint64_t type_id64, uint64_t name_id64);

	void		(*quit) (int exit_code);

	double							(*time_since_launch) ();
	void							(*sleep) (unsigned milliseconds);
	void							(*set_time_step_policy) (const struct TimeStepPolicyWrapper* const policies, unsigned num_policies);
	struct TimeStepPolicyWrapper	(*get_time_step_policy) (enum TimeStepPolicyType type);

	/*	The argv strings will be returned through the MultipleStringsBuffer you provide.
		The function call returns the total number of bytes required to store all argv in the buffer.	*/
	unsigned (*argv) (struct MultipleStringsBuffer* const out_result, unsigned buffer_size);
};

#ifdef __cplusplus
}
#endif
