#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct TouchInputCApi
{
	CApiVector3 (*accelerator_resolution)(CApiInputControllerPtr touch_input_controller);
	CApiVector2 (*resolution)(CApiInputControllerPtr touch_input_controller);
	unsigned (*is_touch_up)(CApiInputControllerPtr touch_input_controller, unsigned contact_id);
	unsigned (*is_touch_down)(CApiInputControllerPtr touch_input_controller, unsigned contact_id);
	unsigned (*gesture_tap)(CApiInputControllerPtr touch_input_controller, CApiVector2 *out_location);
	unsigned (*gesture_tap_sequence)(CApiInputControllerPtr touch_input_controller, CApiVector2 *out_location_sequence);
	unsigned (*gesture_long_press)(CApiInputControllerPtr touch_input_controller, CApiVector2 *out_location);
	unsigned (*gesture_pinch)(CApiInputControllerPtr touch_input_controller, TouchPinchGesture *out_pinch_gesture);
	unsigned (*gesture_rotate)(CApiInputControllerPtr touch_input_controller, TouchRotationGesture *out_rotation_gesture);
	enum SwipeDirection (*gesture_swipe)(CApiInputControllerPtr touch_input_controller);
	unsigned (*is_primary)(CApiInputControllerPtr touch_input_controller, unsigned contact_id);
	float (*size)(CApiInputControllerPtr touch_input_controller, unsigned contact_id);
	float (*minor_axis_size)(CApiInputControllerPtr touch_input_controller, unsigned contact_id);
	float (*major_axis_size)(CApiInputControllerPtr touch_input_controller, unsigned contact_id);
	float (*pressure)(CApiInputControllerPtr touch_input_controller, unsigned contact_id);
	enum TouchEdge (*edge)(CApiInputControllerPtr touch_input_controller, unsigned contact_id);
	CApiVector3 (*location)(CApiInputControllerPtr touch_input_controller, unsigned contact_id);
	CApiVector3 (*location_delta)(CApiInputControllerPtr touch_input_controller, unsigned contact_id);
	unsigned (*has_contact)(CApiInputControllerPtr touch_input_controller, unsigned contact_id);
	unsigned (*contacts)(CApiInputControllerPtr touch_input_controller, unsigned out_contact_ids[MAX_TOUCH_CONTACTS]);
	unsigned (*num_contacts)(CApiInputControllerPtr touch_input_controller);
	void (*set_enabled)(CApiInputControllerPtr simulated_touch_input_controller, unsigned enabled);
};

#ifdef __cplusplus
}
#endif
