#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct InputControllerCApi
{
	enum InputCategory (*category)(CApiInputControllerPtr input_controller);
	const char *(*type)(CApiInputControllerPtr input_controller);
	const char *(*name)(CApiInputControllerPtr input_controller);

	unsigned (*num_buttons)(CApiInputControllerPtr input_controller);
	float (*button)(CApiInputControllerPtr input_controller, unsigned id);
	int (*pressed)(CApiInputControllerPtr input_controller, unsigned id);
	int (*released)(CApiInputControllerPtr input_controller, unsigned id);
	unsigned (*any_pressed)(CApiInputControllerPtr input_controller);
	unsigned (*any_released)(CApiInputControllerPtr input_controller);
	void (*set_down_threshold)(CApiInputControllerPtr input_controller, float threshold);
	float (*down_threshold)(CApiInputControllerPtr input_controller);
	int (*num_axes)(CApiInputControllerPtr input_controller);
	struct CApiVector3 (*axis)(CApiInputControllerPtr input_controller, unsigned axis_index, struct DeadZoneSetting *optional_deadzone_setting);
	void (*dead_zone)(CApiInputControllerPtr input_controller, unsigned axis_index, struct DeadZoneSetting *out_deadzone_setting);
	void (*set_dead_zone)(CApiInputControllerPtr input_controller, unsigned axis_index, struct DeadZoneSetting *deadzone_setting);
	void (*set_rumble_enabled)(CApiInputControllerPtr input_controller, unsigned enabled);
	unsigned(*num_rumble_motors)(CApiInputControllerPtr input_controller);
	void (*set_rumble)(CApiInputControllerPtr input_controller, unsigned motor_id, float value);
	unsigned (*rumble_effect)(CApiInputControllerPtr input_controller, unsigned motor_id, struct RumbleParameters *rumble_parameters);
	void (*stop_rumble_effect)(CApiInputControllerPtr input_controller, unsigned motor_id, unsigned rumble_effect_id);
	unsigned (*is_rumble_effect_playing)(CApiInputControllerPtr input_controller, unsigned motor_id, unsigned rumble_effect_id);
	void (*stop_all_rumble_effects)(CApiInputControllerPtr input_controller, unsigned motor_id);
	const char *(*button_name)(CApiInputControllerPtr input_controller, unsigned button_id);
	const char *(*button_locale_name)(CApiInputControllerPtr input_controller, unsigned button_id);
	unsigned (*button_id)(CApiInputControllerPtr input_controller, unsigned button_name_id32);
	const char *(*axis_name)(CApiInputControllerPtr input_controller, unsigned axis_id);
	unsigned (*axis_id)(CApiInputControllerPtr input_controller, unsigned axis_name_id32);
	const char *(*rumble_motor_name)(CApiInputControllerPtr input_controller, unsigned motor_id);
	unsigned (*rumble_motor_id)(CApiInputControllerPtr input_controller, unsigned rumble_motor_name_id32);

	unsigned (*active)(CApiInputControllerPtr input_controller);
	unsigned (*connected)(CApiInputControllerPtr input_controller);
	unsigned (*disconnected)(CApiInputControllerPtr input_controller);
};

#ifdef __cplusplus
}
#endif
