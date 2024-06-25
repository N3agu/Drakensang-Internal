#define _CRT_SECURE_NO_WARNINGS
#include "menu.h"
#include "ntinfo.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "min_hook/include/MinHook.h"

#include <tlhelp32.h>
#include <Psapi.h>
#include <vector>
#include <sstream>
#include <inttypes.h>

inline bool menu = true;
DWORD pid;

uint64_t cameraPointerAddress = NULL,
	smokePointerAddress = NULL,
	anglePointerAddress = NULL;

HANDLE hProcHandle = NULL,
	threadHandle = NULL;

void imgui_unhook();

uint64_t GetThreadStartAddress(HANDLE processHandle, HANDLE hThread) {
	/* rewritten from https://github.com/cheat-engine/cheat-engine/blob/master/Cheat%20Engine/CEFuncProc.pas#L3080 */
	uint64_t used = 0, ret = 0, 
		stacktop = 0, result = 0;

	MODULEINFO mi;

	GetModuleInformation(processHandle, GetModuleHandle("kernel32.dll"), &mi, sizeof(mi));
	stacktop = (uint64_t)GetThreadstackTopAddress(processHandle, hThread);

	CloseHandle(hThread);

	if (stacktop) {
		uint64_t* buf32 = new uint64_t[8192];

		if (ReadProcessMemory(processHandle, (LPCVOID)(stacktop - 8192), buf32, 8192, NULL))
			for (int i = 8192 / 8 - 1; i >= 0; --i)
				if (buf32[i] >= (uint64_t)mi.lpBaseOfDll && buf32[i] <= (uint64_t)mi.lpBaseOfDll + mi.SizeOfImage) {
					result = stacktop - 8192 + i * 8;
					break;
				}

		delete buf32;
	}

	return result;
}

std::vector<uint64_t> threadList(uint64_t pid) {
	std::vector<uint64_t> vect = std::vector<uint64_t>();
	HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (h == INVALID_HANDLE_VALUE)
		return vect;

	THREADENTRY32 te;
	te.dwSize = sizeof(te);
	if (Thread32First(h, &te))
		do {
			if (te.dwSize >= FIELD_OFFSET(THREADENTRY32, th32OwnerProcessID) + sizeof(te.th32OwnerProcessID))
				if (te.th32OwnerProcessID == pid) vect.push_back(te.th32ThreadID);
			te.dwSize = sizeof(te);
		} while (Thread32Next(h, &te));

		return vect;
}

void calculatePointersForFeatures() {
	std::vector<uint64_t> threadId = threadList(pid);
	HANDLE threadHandle = OpenThread(THREAD_GET_CONTEXT | THREAD_QUERY_INFORMATION, FALSE, *threadId.begin());

	int i;
	uint64_t threadstack0 = GetThreadStartAddress(hProcHandle, threadHandle),
		cameraAddress = -0x00000270,
		smokeAddress = -0x00000270,
		angleAddress = -0x00000270;
	
	std::vector<uint64_t> cameraOffsets = { 0x78, 0x110, 0x738, 0x78, 0x60, 0x78 };
	std::vector<uint64_t> smokeOffsets = { 0x78, 0x110, 0x738, 0x78, 0x60, 0x88 };
	std::vector<uint64_t> angleOffsets = { 0x78, 0x110, 0x738, 0x78, 0x60, 0x94 };

	// Calculate the correct addresses
	ReadProcessMemory(hProcHandle, (LPVOID)(threadstack0 + cameraAddress), &cameraPointerAddress, sizeof(cameraPointerAddress), NULL);
	ReadProcessMemory(hProcHandle, (LPVOID)(threadstack0 + smokeAddress), &smokePointerAddress, sizeof(smokePointerAddress), NULL);
	ReadProcessMemory(hProcHandle, (LPVOID)(threadstack0 + angleAddress), &anglePointerAddress, sizeof(anglePointerAddress), NULL);

	// Add the offsets, -1 because we dont want the value at the last offset
	for (i = 0; i < cameraOffsets.size() - 1; i++)
		ReadProcessMemory(hProcHandle, (LPVOID)(cameraPointerAddress + cameraOffsets.at(i)), &cameraPointerAddress, sizeof(cameraPointerAddress), NULL);

	for (i = 0; i < smokeOffsets.size() - 1; i++)
		ReadProcessMemory(hProcHandle, (LPVOID)(smokePointerAddress + smokeOffsets.at(i)), &smokePointerAddress, sizeof(smokePointerAddress), NULL);

	for (i = 0; i < angleOffsets.size() - 1; i++)
		ReadProcessMemory(hProcHandle, (LPVOID)(anglePointerAddress + angleOffsets.at(i)), &anglePointerAddress, sizeof(anglePointerAddress), NULL);

	// Add last offset
	cameraPointerAddress += cameraOffsets.at(cameraOffsets.size() - 1);
	smokePointerAddress += smokeOffsets.at(smokeOffsets.size() - 1);
	anglePointerAddress += angleOffsets.at(angleOffsets.size() - 1);

	CloseHandle(threadHandle);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (GetAsyncKeyState(VK_INSERT) & 1) {
		menu = !menu;
		if (menu) calculatePointersForFeatures(); // Recalculate the threadstack & addresses in case the map was changed
	}

	if (GetAsyncKeyState(VK_DELETE) & 1)
		imgui_unhook();

	if (menu && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return 1L;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

DWORD WINAPI menuSetup(LPVOID lpParameter) {
	while (!GetModuleHandle("Drakensang Internal.dll")) Sleep(100);

	pid = GetCurrentProcessId();
	hProcHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (hProcHandle == INVALID_HANDLE_VALUE || !hProcHandle) {
		MessageBoxA(NULL, "Invalid handle", "Failed to open process", 0);
		return 0;
	}

	HWND hwndProc = GetForegroundWindow();
	if (!hwndProc) {
		MessageBoxA(NULL, "Invalid HWND", "Failed to find window", 0);
		return 0;
	}

	calculatePointersForFeatures();

	LPDIRECT3D9 d3d = NULL;
	LPDIRECT3DDEVICE9 d3ddev = NULL;

	HWND tmpWnd = CreateWindowA("BUTTON", "Temp Window", WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, NULL, NULL, hModule, NULL);
	if (!tmpWnd) {
		MessageBoxA(NULL, "Invalid temp window", "Failed to create window", 0);
		return 0;
	}

	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d) {
		DestroyWindow(tmpWnd);
		return 0;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = tmpWnd;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	HRESULT result = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, tmpWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);
	if (result != D3D_OK) {
		d3d->Release();
		DestroyWindow(tmpWnd);
		return 0;
	}

	// Architecture
	DWORD64* dVtable = reinterpret_cast<DWORD64*>(d3ddev);
	dVtable = reinterpret_cast<DWORD64*>(dVtable[0]);

	EndScene_orig = reinterpret_cast<EndScene>(dVtable[42]);
	DrawIndexedPrimitive_orig = reinterpret_cast<DrawIndexedPrimitive>(dVtable[82]);
	Reset_orig = reinterpret_cast<Reset>(dVtable[16]);

	// Hooks
	if (MH_Initialize() != MH_OK) { return 1; }
	if (MH_CreateHook(reinterpret_cast<DWORD_PTR*>(dVtable[42]), &EndScene_hook, reinterpret_cast<void**>(&EndScene_orig)) != MH_OK) { return 1; }
	if (MH_EnableHook(reinterpret_cast<DWORD_PTR*>(dVtable[42])) != MH_OK) return 1;
	if (MH_CreateHook(reinterpret_cast<DWORD_PTR*>(dVtable[82]), &DrawIndexedPrimitive_hook, reinterpret_cast<void**>(&DrawIndexedPrimitive_orig)) != MH_OK) { return 1; }
	if (MH_EnableHook(reinterpret_cast<DWORD_PTR*>(dVtable[82])) != MH_OK) return 1;
	if (MH_CreateHook(reinterpret_cast<DWORD_PTR*>(dVtable[16]), &Reset_hook, reinterpret_cast<void**>(&Reset_orig)) != MH_OK) { return 1; }
	if (MH_EnableHook(reinterpret_cast<DWORD_PTR*>(dVtable[16])) != MH_OK) return 1;

	oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(FindWindowA(NULL, "Drakensang Online"), GWLP_WNDPROC, (LONG_PTR)WndProc));

	d3ddev->Release();
	d3d->Release();
	DestroyWindow(tmpWnd);

	return 1;
}

HRESULT APIENTRY DrawIndexedPrimitive_hook(LPDIRECT3DDEVICE9 pD3D9, D3DPRIMITIVETYPE Type,
	INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount) {
	return DrawIndexedPrimitive_orig(pD3D9, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

void showMenu() {
	IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context");
	ImGuiWindowFlags window_flags = 0;
	if (menu) {
		ImGui::Begin("Drakensang Internal | N3agu", &menu, ImGuiWindowFlags_NoSavedSettings);
		static float cameraValue = 25.0f; // original value
		ImGui::SliderFloat("Camera", &cameraValue, 5.0f, 120.0f);
		WriteProcessMemory(hProcHandle, reinterpret_cast<LPVOID>(cameraPointerAddress), &cameraValue, sizeof(float), 0);

		static float smokeValue = 25.0f; // original value
		ImGui::SliderFloat("Smoke", &smokeValue, 0.0f, 100.0f);
		WriteProcessMemory(hProcHandle, reinterpret_cast<LPVOID>(smokePointerAddress), &smokeValue, sizeof(float), 0);

		static float angleValue = 0.5934119821f; // original value
		ImGui::SliderFloat("Angle View", &angleValue, 0.1f, 5.0f);
		WriteProcessMemory(hProcHandle, reinterpret_cast<LPVOID>(anglePointerAddress), &angleValue, sizeof(float), 0);
		ImGui::End();
	}
}

HRESULT APIENTRY EndScene_hook(LPDIRECT3DDEVICE9 pD3D9) {
	static bool init = true;
	if (init) {
		init = false;
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		ImGui_ImplWin32_Init(FindWindowA(NULL, "Drakensang Online"));
		ImGui_ImplDX9_Init(pD3D9);
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	showMenu();
	ImGui::GetIO().WantCaptureMouse = true;

	ImGui::EndFrame();
	ImGui::Render();

	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return EndScene_orig(pD3D9);
}

HRESULT APIENTRY Reset_hook(LPDIRECT3DDEVICE9 pD3D9, D3DPRESENT_PARAMETERS* pPresentationParameters) {
	HRESULT ResetReturn = Reset_orig(pD3D9, pPresentationParameters);
	return ResetReturn;
}

void imgui_unhook() {
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
