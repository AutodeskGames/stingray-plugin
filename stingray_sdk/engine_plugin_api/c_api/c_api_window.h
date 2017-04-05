#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*WindowCApi_KeyDownFunction)(void *obj, int virtual_key, int repeat_count, int scan_code, int extended, int previous_state);
typedef void(*WindowCApi_CharDownFunction)(void *obj, int char_code);
typedef void(*WindowCApi_KeyUpFunction)(void *obj, int virtual_key, int scan_code, int extended);
typedef void(*WindowCApi_MouseButtonFunction)(void *obj, int button);
typedef void(*WindowCApi_MouseMoveFunction)(void *obj, ConstVector3Ptr delta);
typedef void(*WindowCApi_CursorPosFunction)(void *obj, unsigned x, unsigned y);
typedef void(*WindowCApi_ActivateFunction)(void *obj, int active);
typedef void(*WindowCApi_ResizeFunction)(void *obj, WindowPtr window, int x, int y, int width, int heigh);
typedef void(*WindowCApi_ToggleFullscreenFunction)(void *obj, WindowPtr window);
typedef void(*WindowCApi_SetFocusFunction)(void *obj);

struct WindowCApi
{
	int		(*has_mouse_focus) (ConstWindowPtr optional);
	int		(*has_focus) (ConstWindowPtr optional);
	void	(*set_mouse_focus) (WindowPtr optional, int enabled);
	void	(*set_focus) (WindowPtr optional);

	int		(*show_cursor) (WindowPtr optional);
	int		(*clip_cursor) (WindowPtr optional);
	void	(*set_cursor) (WindowPtr optional, const char* optional_mouse_cursor);
	void	(*set_show_cursor) (WindowPtr optional, int enabled, int restore_cursor_pos);
	void	(*set_clip_cursor)(WindowPtr optional, int enabled);

	int		(*is_resizable)(ConstWindowPtr optional);
	void	(*set_resizable) (WindowPtr optional, int enabled);
	void	(*set_resolution) (WindowPtr optional, unsigned width, unsigned height);
	float   (*get_dpi_scale) ();

	void	(*set_title) (WindowPtr optional, const char* title);
	int		(*has_window) (ConstWindowPtr);
	WindowPtr (*get_main_window)();

	void	(*minimize) (WindowPtr optional);
	void	(*maximize) (WindowPtr optional);
	void	(*restore) (WindowPtr optional);
	int		(*is_closing) (WindowPtr optional);
	void	(*close) (WindowPtr optional);
	void	(*trigger_resize) (WindowPtr optional);
	void	(*set_ime_enabled) (WindowPtr optional, int enabled);
	void	(*set_foreground) (WindowPtr optional);
	void	(*set_keystroke_enabled) (enum WindowKeystrokes, int enabled);
	void	(*fill_default_open_parameter) (struct WindowOpenParameter* out_result);
	unsigned (*id) (WindowPtr optional);
	WindowPtr (*open) (struct WindowOpenParameter* const);
	struct WindowRectWrapper (*rect) (WindowPtr optional);
	void	(*set_rect)(WindowPtr optional, struct WindowRectWrapper rect);

	void (*add_key_down_callback)(WindowPtr window, void *obj, WindowCApi_KeyDownFunction f);
	void (*remove_key_down_callback)(WindowPtr window, void *obj, WindowCApi_KeyDownFunction f);
	void (*add_char_down_callback)(WindowPtr window, void *obj, WindowCApi_CharDownFunction f);
	void (*remove_char_down_callback)(WindowPtr window, void *obj, WindowCApi_CharDownFunction f);
	void (*add_key_up_callback)(WindowPtr window, void *obj, WindowCApi_KeyUpFunction f);
	void (*remove_key_up_callback)(WindowPtr window, void *obj, WindowCApi_KeyUpFunction f);
	void (*add_mouse_down_callback)(WindowPtr window, void *obj, WindowCApi_MouseButtonFunction f);
	void (*remove_mouse_down_callback)(WindowPtr window, void *obj, WindowCApi_MouseButtonFunction f);
	void (*add_mouse_up_callback)(WindowPtr window, void *obj, WindowCApi_MouseButtonFunction f);
	void (*remove_mouse_up_callback)(WindowPtr window, void *obj, WindowCApi_MouseButtonFunction f);
	void (*add_mouse_move_callback)(WindowPtr window, void *obj, WindowCApi_MouseMoveFunction f);
	void (*remove_mouse_move_callback)(WindowPtr window, void *obj, WindowCApi_MouseMoveFunction f);
	void (*add_wheel_move_callback)(WindowPtr window, void *obj, WindowCApi_MouseMoveFunction f);
	void (*remove_wheel_move_callback)(WindowPtr window, void *obj, WindowCApi_MouseMoveFunction f);
	void (*add_cursor_pos_callback)(WindowPtr window, void *obj, WindowCApi_CursorPosFunction f);
	void (*remove_cursor_pos_callback)(WindowPtr window, void *obj, WindowCApi_CursorPosFunction f);
	void (*add_activate_callback)(WindowPtr window, void *obj, WindowCApi_ActivateFunction f);
	void (*remove_activate_callback)(WindowPtr window, void *obj, WindowCApi_ActivateFunction f);
	void (*add_resize_callback)(WindowPtr window, void *obj, WindowCApi_ResizeFunction f);
	void (*remove_resize_callback)(WindowPtr window, void *obj, WindowCApi_ResizeFunction f);
	void (*add_toggle_fullscreen_callback)(WindowPtr window, void *obj, WindowCApi_ToggleFullscreenFunction f);
	void (*remove_toggle_fullscreen_callback)(WindowPtr window, void *obj, WindowCApi_ToggleFullscreenFunction f);
	void (*add_set_focus_callback)(WindowPtr window, void *obj, WindowCApi_SetFocusFunction f);
	void (*remove_set_focus_callback)(WindowPtr window, void *obj, WindowCApi_SetFocusFunction f);
};

#ifdef __cplusplus
}
#endif
