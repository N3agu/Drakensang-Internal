#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <windows.h>
#include <vector>
#include <TlHelp32.h>
#include <Psapi.h>

typedef LONG NTSTATUS;
typedef DWORD KPRIORITY;
typedef WORD UWORD;

void* GetThreadstackTopAddress(HANDLE hProcess, HANDLE hThread);
std::vector<uint64_t> threadList(uint64_t pid);
uint64_t GetThreadStartAddress(HANDLE processHandle, HANDLE hThread);

#endif // !UTILS_H