#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <cstdlib>
#include <ctime>

void p(DWORD pid, const std::wstring& processName) {
    std::wcout << L"Found RobloxPlayerBeta.exe!" << std::endl;
    std::wcout << L"PID: " << pid << std::endl;
    std::wcout << L"Process Name: " << processName << std::endl;
}

std::wstring g() {
    int offsetLength = rand() % 4 + 3;
    std::wstring offset = L"0x";

    for (int i = 0; i < offsetLength; ++i) {
        wchar_t randomChar;

        if (rand() % 2 == 0) {
            randomChar = static_cast<wchar_t>(rand() % 26 + L'A');
        }
        else {
            randomChar = static_cast<wchar_t>(rand() % 10 + L'0');
        }

        offset += randomChar;
    }

    return offset;
}

int main() {
    system("start cmd /c");

    std::srand(static_cast<unsigned int>(std::time(0)));

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(entry);

    int offsetCount = rand() % 11 + 13;

    if (Process32First(snapshot, &entry)) {
        do {
            if (_wcsicmp(entry.szExeFile, L"RobloxPlayerBeta.exe") == 0) {
                std::wstring processName(entry.szExeFile);

                p(entry.th32ProcessID, processName);

                while (offsetCount > 0) {
                    double randomSleep = 0.4 + static_cast<double>(rand()) / RAND_MAX * 0.2;

                    Sleep(static_cast<DWORD>(randomSleep * 1000));

                    std::wstring randomOffset = g();

                    std::wcout << L"Deleted " << randomOffset << L" offset" << std::endl;

                    offsetCount--;
                    if (offsetCount == 0) {
                        std::wcout << L"Bypassed byfron" << std::endl;
                        MessageBoxW(nullptr, L"Bypassed byfron", L"Injector", MB_ICONINFORMATION | MB_OK);
                    }
                }

                break;
            }
        } while (Process32Next(snapshot, &entry));
    }

    CloseHandle(snapshot);
    getchar();

    return 0;
}