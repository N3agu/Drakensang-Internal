#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include "min_hook/include/MinHook.h"

DWORD WINAPI menuSetup(__in  LPVOID lpParameter);
void imgui_unhook();

BOOL WINAPI DllMain(const HINSTANCE instance, const DWORD reason, const LPVOID reserved) {
	switch (reason) {
		case DLL_PROCESS_ATTACH: {
			CloseHandle(CreateThread(nullptr, NULL, menuSetup, instance, NULL, nullptr));
		} break;
		case DLL_PROCESS_DETACH: {
			imgui_unhook();
			break;
		}
		default: break;
	}

	return TRUE;
}