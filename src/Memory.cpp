#include "../include/Memory.hpp"

uintptr_t Memory::GetProcessId(const wchar_t* processName) {
    HANDLE hProcessId = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    uintptr_t process;
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);

    do
    {
        if (!_wcsicmp(pEntry.szExeFile, processName))
        {
            process = pEntry.th32ProcessID;
            CloseHandle(hProcessId);
            handle = OpenProcess(PROCESS_ALL_ACCESS, false, process);
            return process;
        }

    } while (Process32Next(hProcessId, &pEntry));
    return 0;
}

uintptr_t Memory::GetModuleBase(uintptr_t processId, const wchar_t* moduleName) {
    HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
    MODULEENTRY32 mEntry;
    mEntry.dwSize = sizeof(mEntry);

    do
    {
        if (!_wcsicmp(mEntry.szModule, moduleName))
        {
            CloseHandle(hModule);
            return (uintptr_t)mEntry.hModule;
        }
    } while (Module32Next(hModule, &mEntry));
    return 0;
}