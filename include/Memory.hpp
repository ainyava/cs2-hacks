#pragma once

#include <cstdint>
#include "Windows.h"
#include <TlHelp32.h>

class Memory {
public:
    HANDLE handle = NULL;
    uintptr_t GetProcessId(const wchar_t* windowName);
    uintptr_t GetModuleBase(uintptr_t  processId, const wchar_t* moduleName);

    template <class Type>
    Type read(uintptr_t address) {
        Type value;
        ReadProcessMemory(handle, (LPBYTE*)address, &value, sizeof(value), NULL);
        return value;
    }

    template <class Type>
    Type write(uintptr_t address, Type value) {
        WriteProcessMemory(handle, (LPBYTE*)address, &value, sizeof(value), NULL);
        return value;
    }

};

