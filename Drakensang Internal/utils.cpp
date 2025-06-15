#include "utils.h"

typedef struct _CLIENT_ID {
	PVOID UniqueProcess;
	PVOID UniqueThread;
} CLIENT_ID, * PCLIENT_ID;

typedef struct _THREAD_BASIC_INFORMATION {
	NTSTATUS                ExitStatus;
	PVOID                   TebBaseAddress;
	CLIENT_ID               ClientId;
	KAFFINITY               AffinityMask;
	KPRIORITY               Priority;
	KPRIORITY               BasePriority;
} THREAD_BASIC_INFORMATION, * PTHREAD_BASIC_INFORMATION;

enum THREADINFOCLASS {
	ThreadBasicInformation,
};

void* GetThreadstackTopAddress(HANDLE hProcess, HANDLE hThread) {

	LPSTR moduleName = (LPSTR)"ntdll.dll";

	bool loadedManually = false;
	HMODULE module = GetModuleHandle(moduleName);

	if (!module) {
		module = LoadLibrary(moduleName);
		loadedManually = true;
	}

	NTSTATUS(__stdcall * NtQueryInformationThread)(HANDLE ThreadHandle, THREADINFOCLASS ThreadInformationClass, PVOID ThreadInformation, ULONG ThreadInformationLength, PULONG ReturnLength);
	NtQueryInformationThread = reinterpret_cast<decltype(NtQueryInformationThread)>(GetProcAddress(module, "NtQueryInformationThread"));

	if (NtQueryInformationThread) {
		NT_TIB tib = { 0 };
		THREAD_BASIC_INFORMATION tbi = { 0 };

		NTSTATUS status = NtQueryInformationThread(hThread, ThreadBasicInformation, &tbi, sizeof(tbi), nullptr);
		if (status >= 0) {
			ReadProcessMemory(hProcess, tbi.TebBaseAddress, &tib, sizeof(tbi), nullptr);

			if (loadedManually) FreeLibrary(module);
			return tib.StackBase;
		}
	}


	if (loadedManually) FreeLibrary(module);

	return nullptr;
}

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