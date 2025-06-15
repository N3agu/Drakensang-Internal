#define _CRT_SECURE_NO_WARNINGS
#include "menu.h"
#include "utils.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "min_hook/include/MinHook.h"

#include <tlhelp32.h>
#include <Psapi.h>
#include <vector>
#include <sstream>
#include <inttypes.h>

inline bool featuresMenu = true;
inline bool characterMenu = true;
DWORD pid;

uint64_t threadstack0 = NULL;

// Features
uint64_t cameraPointerAddress = NULL,
	smokePointerAddress = NULL,
	anglePointerAddress = NULL,
	attackSpeedPointerAddress = NULL,
	cameraAddress = -0x00000270,
	smokeAddress = -0x00000270,
	angleAddress = -0x00000270,
	attackSpeedAddress = -0x00000270;

std::vector<uint64_t> cameraOffsets = { 0x78, 0x218, 0x30, 0x50, 0x60, 0x60, 0x78 },
	smokeOffsets = { 0x78, 0x218, 0x30, 0x50, 0x60, 0x60, 0x88 },
	angleOffsets = { 0x78, 0x218, 0x30, 0x50, 0x60, 0x60, 0x94 },
	attackSpeedOffsets = { 0x78, 0x110, 0x788, 0x30, 0x0, 0xD8 };

// Character
uint64_t nonenemySelectedPointerAddress = NULL,
	enemySelectedPointerAddress = NULL,
	currentMapPointerAddress = NULL,
	usernamePointerAddress = NULL,
	healthPointerAddress = NULL,
	manaPointerAddress = NULL,
	usernameAddress = -0x00000270,
	currentMapAddress = -0x00000270,
	enemySelectedAddress = -0x00000270,
	nonenemySelectedAddress = -0x00000270,
	healthAddress = -0x00000270,
	manaAddress = -0x00000270;

std::vector<uint64_t> usernameOffsets = { 0xD8, 0x120, 0x78, 0xD0, 0x60, 0x260, 0x2A0 },
	healthOffsets = { 0x80, 0xB8, 0x20, 0x530, 0x48, 0x70, 0x40 },
	manaOffsets = { 0x80, 0x80, 0x278, 0x40, 0x48, 0x70, 0x4C },
	nonenemySelectedOffsets = { 0x158, 0x200, 0x10, 0x70, 0x60, 0x0, 0x2A0 },
	enemySelectedOffsets = { 0x158, 0x58, 0x60, 0x0, 0x2A0 }, 
	currentMapOffsets = { 0x1B8, 0x98, 0x40, 0x60, 0x0, 0x260, 0x260 };

HANDLE hProcHandle = NULL,
	threadHandle = NULL;

void imgui_unhook();

void calculatePointersForFeatures() {
	try {
		// Calculate the correct addresses
		ReadProcessMemory(hProcHandle, (LPVOID)(threadstack0 + cameraAddress), &cameraPointerAddress, sizeof(cameraPointerAddress), NULL);
		ReadProcessMemory(hProcHandle, (LPVOID)(threadstack0 + smokeAddress), &smokePointerAddress, sizeof(smokePointerAddress), NULL);
		ReadProcessMemory(hProcHandle, (LPVOID)(threadstack0 + angleAddress), &anglePointerAddress, sizeof(anglePointerAddress), NULL);
		ReadProcessMemory(hProcHandle, (LPVOID)(threadstack0 + attackSpeedAddress), &attackSpeedPointerAddress, sizeof(attackSpeedPointerAddress), NULL);
		ReadProcessMemory(hProcHandle, (LPVOID)(threadstack0 + currentMapAddress), &currentMapPointerAddress, sizeof(currentMapPointerAddress), NULL);
		ReadProcessMemory(hProcHandle, (LPVOID)(threadstack0 + nonenemySelectedAddress), &nonenemySelectedPointerAddress, sizeof(nonenemySelectedPointerAddress), NULL);
		ReadProcessMemory(hProcHandle, (LPVOID)(threadstack0 + enemySelectedAddress), &enemySelectedPointerAddress, sizeof(enemySelectedPointerAddress), NULL);
		ReadProcessMemory(hProcHandle, (LPVOID)(threadstack0 + usernameAddress), &usernamePointerAddress, sizeof(usernamePointerAddress), NULL);
		ReadProcessMemory(hProcHandle, (LPVOID)(threadstack0 + healthAddress), &healthPointerAddress, sizeof(healthPointerAddress), NULL);
		ReadProcessMemory(hProcHandle, (LPVOID)(threadstack0 + manaAddress), &manaPointerAddress, sizeof(manaPointerAddress), NULL);

		int i;
		// Add the offsets, -1 because we dont want the value at the last offset
		for (i = 0; i < cameraOffsets.size() - 1; i++)
			ReadProcessMemory(hProcHandle, (LPVOID)(cameraPointerAddress + cameraOffsets.at(i)), &cameraPointerAddress, sizeof(cameraPointerAddress), NULL);

		for (i = 0; i < smokeOffsets.size() - 1; i++)
			ReadProcessMemory(hProcHandle, (LPVOID)(smokePointerAddress + smokeOffsets.at(i)), &smokePointerAddress, sizeof(smokePointerAddress), NULL);

		for (i = 0; i < angleOffsets.size() - 1; i++)
			ReadProcessMemory(hProcHandle, (LPVOID)(anglePointerAddress + angleOffsets.at(i)), &anglePointerAddress, sizeof(anglePointerAddress), NULL);

		for (i = 0; i < attackSpeedOffsets.size() - 1; i++)
			ReadProcessMemory(hProcHandle, (LPVOID)(attackSpeedPointerAddress + attackSpeedOffsets.at(i)), &attackSpeedPointerAddress, sizeof(attackSpeedPointerAddress), NULL);

		for (i = 0; i < currentMapOffsets.size() - 1; i++)
			ReadProcessMemory(hProcHandle, (LPVOID)(currentMapPointerAddress + currentMapOffsets.at(i)), &currentMapPointerAddress, sizeof(currentMapPointerAddress), NULL);

		for (i = 0; i < nonenemySelectedOffsets.size() - 1; i++)
			ReadProcessMemory(hProcHandle, (LPVOID)(nonenemySelectedPointerAddress + nonenemySelectedOffsets.at(i)), &nonenemySelectedPointerAddress, sizeof(nonenemySelectedPointerAddress), NULL);

		for (i = 0; i < enemySelectedOffsets.size() - 1; i++)
			ReadProcessMemory(hProcHandle, (LPVOID)(enemySelectedPointerAddress + enemySelectedOffsets.at(i)), &enemySelectedPointerAddress, sizeof(enemySelectedPointerAddress), NULL);

		for (i = 0; i < usernameOffsets.size() - 1; i++)
			ReadProcessMemory(hProcHandle, (LPVOID)(usernamePointerAddress + usernameOffsets.at(i)), &usernamePointerAddress, sizeof(usernamePointerAddress), NULL);

		for (i = 0; i < healthOffsets.size() - 1; i++)
			ReadProcessMemory(hProcHandle, (LPVOID)(healthPointerAddress + healthOffsets.at(i)), &healthPointerAddress, sizeof(healthPointerAddress), NULL);

		for (i = 0; i < manaOffsets.size() - 1; i++)
			ReadProcessMemory(hProcHandle, (LPVOID)(manaPointerAddress + manaOffsets.at(i)), &manaPointerAddress, sizeof(manaPointerAddress), NULL);

		// Add last offset
		cameraPointerAddress += cameraOffsets.at(cameraOffsets.size() - 1);
		smokePointerAddress += smokeOffsets.at(smokeOffsets.size() - 1);
		anglePointerAddress += angleOffsets.at(angleOffsets.size() - 1);
		attackSpeedPointerAddress += attackSpeedOffsets.at(attackSpeedOffsets.size() - 1);
		currentMapPointerAddress += currentMapOffsets.at(currentMapOffsets.size() - 1);
		nonenemySelectedPointerAddress += nonenemySelectedOffsets.at(nonenemySelectedOffsets.size() - 1);
		enemySelectedPointerAddress += enemySelectedOffsets.at(enemySelectedOffsets.size() - 1);
		usernamePointerAddress += usernameOffsets.at(usernameOffsets.size() - 1);
		healthPointerAddress += healthOffsets.at(healthOffsets.size() - 1);
		manaPointerAddress += manaOffsets.at(manaOffsets.size() - 1);
	}
	catch (...) {}
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (GetAsyncKeyState(VK_INSERT) & 1) {
		featuresMenu = !featuresMenu;
	}

	if (GetAsyncKeyState(VK_HOME) & 1) {
		characterMenu = !characterMenu;
	}
	
	calculatePointersForFeatures(); // Recalculate the threadstack & addresses in case the map was changed
	
	if (GetAsyncKeyState(VK_DELETE) & 1) {
		imgui_unhook();
	}

	if ((featuresMenu || characterMenu) && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
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

	std::vector<uint64_t> threadId = threadList(pid);
	threadHandle = OpenThread(THREAD_GET_CONTEXT | THREAD_QUERY_INFORMATION, FALSE, *threadId.begin());
	threadstack0 = GetThreadStartAddress(hProcHandle, threadHandle);
	CloseHandle(threadHandle);

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
	if (featuresMenu) {
		try {
			ImGui::Begin("Features | DSO Internal by N3agu", &featuresMenu, ImGuiWindowFlags_NoSavedSettings);
			ImGui::Text("Keep the menu closed while entering a new map!");

			static float cameraValue = 25.0f; // original value
			ImGui::SliderFloat("Camera", &cameraValue, 5.0f, 120.0f);
			WriteProcessMemory(hProcHandle, reinterpret_cast<LPVOID>(cameraPointerAddress), &cameraValue, sizeof(float), 0);

			static float smokeValue = 25.0f; // original value
			ImGui::SliderFloat("Smoke", &smokeValue, 0.0f, 100.0f);
			WriteProcessMemory(hProcHandle, reinterpret_cast<LPVOID>(smokePointerAddress), &smokeValue, sizeof(float), 0);

			static float angleValue = 0.5934119821f; // original value
			ImGui::SliderFloat("Angle View", &angleValue, 0.1f, 5.0f);
			WriteProcessMemory(hProcHandle, reinterpret_cast<LPVOID>(anglePointerAddress), &angleValue, sizeof(float), 0);

			static float attackSpeedValue = 1.170f; // my characters value
			ImGui::SliderFloat("Visual Attack Speed", &attackSpeedValue, 0.1f, 30.0f);
			WriteProcessMemory(hProcHandle, reinterpret_cast<LPVOID>(attackSpeedPointerAddress), &attackSpeedValue, sizeof(float), 0);
			ImGui::End();
		}
		catch (...) {
			// Catch-all for unexpected errors - debugging
		}
	}

	if (characterMenu) {
		try {
			ImGui::Begin("Character | DSO Internal by N3agu", &characterMenu, ImGuiWindowFlags_NoSavedSettings);

			static char currentMapValue[256] = "";
			SIZE_T bytesReadForMap = 0;

			bool foundMap = ReadProcessMemory(hProcHandle, reinterpret_cast<LPCVOID>(currentMapPointerAddress), currentMapValue, sizeof(currentMapValue), &bytesReadForMap);

			if (foundMap) {
				ImGui::Text("Current Map: %s", currentMapValue);
			}
			else {
				ImGui::Text("Current Map: Not found");
			}

			static char usernameValue[256] = "";
			SIZE_T bytesReadForUsername = 0;

			bool foundUsername = ReadProcessMemory(hProcHandle, reinterpret_cast<LPCVOID>(usernamePointerAddress), usernameValue, sizeof(usernameValue), &bytesReadForUsername);

			if (foundUsername) ImGui::Text("Username: %s", usernameValue);
			else ImGui::Text("Username: Not found");

			int healthValue;
			SIZE_T bytesReadForHealth = 0;

			bool foundHealth = ReadProcessMemory(hProcHandle, reinterpret_cast<LPCVOID>(healthPointerAddress), &healthValue, sizeof(healthValue), &bytesReadForHealth);

			if (foundHealth) {
				ImGui::Text("Health: %i", healthValue);
			}
			else {
				ImGui::Text("Health: Not found");
			}

			int manaValue;
			SIZE_T bytesReadForMana = 0;

			bool foundMana = ReadProcessMemory(hProcHandle, reinterpret_cast<LPCVOID>(manaPointerAddress), &manaValue, sizeof(manaValue), &bytesReadForMana);

			if (foundMana) {
				ImGui::Text("Mana: %i", manaValue);
			}
			else {
				ImGui::Text("Mana: Not found");
			}

			static char nonenemySelectionValue[256] = "";
			SIZE_T bytesReadForNonenemySelection = 0;

			bool foundNonenemy = ReadProcessMemory(hProcHandle, reinterpret_cast<LPCVOID>(nonenemySelectedPointerAddress), nonenemySelectionValue, sizeof(nonenemySelectionValue), &bytesReadForNonenemySelection);

			if (foundNonenemy) {
				if (!strstr(nonenemySelectionValue, "Locale"))
					ImGui::Text("Last Selected Non-Enemy: %s", nonenemySelectionValue);
				else
					ImGui::Text("Last Selected Non-Enemy: None");
			}
			else {
				ImGui::Text("Last Selected Non-Enemy: None");
			}

			static char enemySelectionValue[256] = "";
			SIZE_T bytesReadForEnemySelection = 0;

			bool foundEnemy = ReadProcessMemory(hProcHandle, reinterpret_cast<LPCVOID>(enemySelectedPointerAddress), enemySelectionValue, sizeof(enemySelectionValue), &bytesReadForEnemySelection);

			if (foundEnemy) {
				if (!strstr(enemySelectionValue, "Locale"))
					ImGui::Text("Last Selected Enemy: %s", enemySelectionValue);
				else
					ImGui::Text("Last Selected Enemy: None");
			}
			else ImGui::Text("Last Selected Enemy: None");
			ImGui::End();
		}
		catch (...) {
			// Catch-all for unexpected errors - debugging
		}
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
