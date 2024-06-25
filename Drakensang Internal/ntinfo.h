#ifndef NTINFO_H
#define NTINFO_H

#include <iostream>
#include <windows.h>

typedef LONG NTSTATUS;
typedef DWORD KPRIORITY;
typedef WORD UWORD;

void* GetThreadstackTopAddress(HANDLE hProcess, HANDLE hThread);

#endif // !NTINFO_H