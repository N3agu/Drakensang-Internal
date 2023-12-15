#include <iostream>
#include <Windows.h>
#include <vector>
#include <thread>
#include <chrono>
#include <tlhelp32.h>
#include <psapi.h>
#include <filesystem>

namespace fs = std::filesystem;

std::vector<std::wstring> getDllFilesInCurrentDirectory() {
    std::vector<std::wstring> dllFiles;

    try {
        fs::path currentPath = fs::current_path();
        for (const auto &entry: fs::directory_iterator(currentPath)) {
            if (entry.is_regular_file() && entry.path().extension() == L".dll") {
                dllFiles.push_back(entry.path().filename());
            }
        }
    } catch (const fs::filesystem_error &e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return dllFiles;
}

std::vector<uint32_t> find_processes(const std::wstring &name) {

    std::vector<uint32_t> DrakensangProcesses;

    HANDLE process_snap;
    PROCESSENTRY32 pe32;
    process_snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (process_snap == INVALID_HANDLE_VALUE)
        return DrakensangProcesses;

    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(process_snap, &pe32)) {
        if (reinterpret_cast<const wchar_t *>(pe32.szExeFile) == name)
            DrakensangProcesses.push_back(pe32.th32ProcessID);

        while (Process32Next(process_snap, &pe32)) {
            if (reinterpret_cast<const wchar_t *>(pe32.szExeFile) == name)
                DrakensangProcesses.push_back(pe32.th32ProcessID);
        }
    }

    CloseHandle(process_snap);

    return DrakensangProcesses;
}

using namespace std::chrono_literals;

bool is_injected(const uint32_t &pid, const std::wstring &cheat) {
    HMODULE hMods[1024];
    HANDLE hProcess;
    DWORD cbNeeded;
    unsigned int i;
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
                           PROCESS_VM_READ,
                           FALSE, pid);

    if (nullptr == hProcess)
        return false;

    if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
        for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
            TCHAR szModName[MAX_PATH];
            if (GetModuleBaseName(hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR))) {
                if (wcscmp(reinterpret_cast<const wchar_t *>(szModName), cheat.c_str()) == 0) {
                    CloseHandle(hProcess);
                    return true;
                }
            }
        }
    }

    CloseHandle(hProcess);

    return false;
}

void enable_debug_privilege() {
    HANDLE token;
    LUID value;
    TOKEN_PRIVILEGES tp;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token)) {
        if (LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &value)) {
            tp.PrivilegeCount = 1;
            tp.Privileges[0].Luid = value;
            tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            if (AdjustTokenPrivileges(token, FALSE, &tp, sizeof(tp), nullptr, nullptr))
                CloseHandle(token);
        }
    }
}

bool inject(const uint32_t &pid, const std::wstring &cheat) {
    TCHAR current_dir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, current_dir);

    auto dll_path = std::wstring(reinterpret_cast<const wchar_t *>(current_dir)) + cheat;

    auto handle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);

    if (!handle || handle == INVALID_HANDLE_VALUE) {
        printf("[-] Failed to open Drakensang process!\n");
        return false;
    }

    FILETIME ft;
    SYSTEMTIME st;
    GetSystemTime(&st);
    SystemTimeToFileTime(&st, &ft);

    FILETIME create, exit, kernel, user;
    GetProcessTimes(handle, &create, &exit, &kernel, &user);

    auto delta = 10 - static_cast<int32_t>(
            (*reinterpret_cast<uint64_t *>(&ft) - *reinterpret_cast<uint64_t *>(&create.dwLowDateTime)) / 10000000U);
    if (delta > 0)
        std::this_thread::sleep_for(std::chrono::seconds(delta));

    auto dll_path_remote = VirtualAllocEx(handle, nullptr, (dll_path.size() + 1) * sizeof(wchar_t),
                                          MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if (!dll_path_remote) {
        printf("[-] Failed to alloc space!\n");
        CloseHandle(handle);
        return false;
    }

    if (!WriteProcessMemory(handle, dll_path_remote, dll_path.data(), (dll_path.size() + 1) * sizeof(wchar_t),
                            nullptr)) {
        printf("[-] Failed to write memory!\n");
        VirtualFreeEx(handle, dll_path_remote, 0, MEM_RELEASE);
        CloseHandle(handle);
        return false;
    }

    auto thread = CreateRemoteThread(handle, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(GetProcAddress(
            LoadLibrary(reinterpret_cast<LPCSTR>(L"kernel32.dll")), "LoadLibraryW")), dll_path_remote, 0, nullptr);
    if (!thread || thread == INVALID_HANDLE_VALUE) {
        printf("[-] Failed to create thread!\n");
        VirtualFreeEx(handle, dll_path_remote, 0, MEM_RELEASE);
        CloseHandle(handle);
        return false;
    }

    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
    VirtualFreeEx(handle, dll_path_remote, 0, MEM_RELEASE);
    CloseHandle(handle);
    printf("[+] Injected successfully!\n");
    return true;
}

int main() {
    enable_debug_privilege();

    std::vector<std::wstring> dllFiles = getDllFilesInCurrentDirectory();
    std::wstring Cheat{};

    if (!dllFiles.empty()) {
        if (dllFiles.size() == 1) {
            Cheat = dllFiles[0];
        } else {
            std::cout << "Choose the Injector DLL :" << '\n';
            int counter{}, choice{};
            for (const auto &dllFileName: dllFiles) {
                std::wcout << ++counter << ") " << dllFileName << std::endl;
            }
            std::cout << '>';
            std::cin >> choice;
            Cheat = dllFiles[choice - 1];
        }
    } else {
        std::wcout << L"No DLL files found in the current directory.\n";
    }


    printf("[+] Looking for Drakensang processes...\n");
    while (true) {
        auto dso_processes = find_processes(L"Drakensang.exe");
        for (auto &pid: dso_processes) {
            if (!is_injected(pid, Cheat))
                inject(pid, Cheat);
        }
        std::this_thread::sleep_for(5s);
    }
    return 0;
}