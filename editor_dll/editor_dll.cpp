#include <editor_dll_export.h>
#include <Windows.h>

EDITOR_DLL_EXPORT int editor_dll_message_box(const char* title, const char* message)
{
	return MessageBox(nullptr, message, title, MB_OK | MB_APPLMODAL);
}