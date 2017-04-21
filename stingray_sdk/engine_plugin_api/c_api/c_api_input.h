#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct InputControllerCApi;
struct KeyboardCApi;
struct PS4PadCApi;
struct TouchInputCApi;
struct XBoxOnePadCApi;

struct InputCApi
{
	struct InputControllerCApi *InputController;
	struct KeyboardCApi *Keyboard;
	struct PS4PadCApi *PS4Pad;
	struct TouchInputCApi *Touch;
	struct XBoxOnePadCApi *XBoxOnePad;

	void (*raw_input_queue) (struct RawInputEventWrapper* buffer, unsigned buffer_size);
	unsigned (*raw_input_queue_size) ();
	void (*add_remote_events)(unsigned event_count, struct RemoteEventWrapper* remote_events);

	CApiInputControllerPtr (*keyboard)();
	CApiInputControllerPtr (*mouse)();
	CApiInputControllerPtr (*tablet)();
	CApiInputControllerPtr (*touch_panel)(int index);
	CApiInputControllerPtr (*simulated_touch_panel)();
	int (*num_touch_panels)();
	int (*num_pads)();
	CApiInputControllerPtr (*pad)(int index);

	void (*flush_controllers_state)();

	CApiInputControllerPtr (*synergy_mouse)();
	CApiInputControllerPtr (*synergy_keyboard)();
	void (*synergy_connect)(struct SocketAddressWrapper* address, const char *client_name, int client_width, int client_height);
	const char *(*synergy_clipboard)();

	int (*num_windows_ps4_pads)();
	CApiInputControllerPtr (*windows_ps4_pad)(int index);
	void (*scan_for_windows_ps4_pads)();
	void (*set_tablet_pen_service_properties)(uint64_t prop);
};

#ifdef __cplusplus
}
#endif
