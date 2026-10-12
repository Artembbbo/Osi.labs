// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include "framework.h"
#include <iostream>
#include <vector>
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

int average = 0;
DWORD WINAPI avg(LPVOID temp) {
    std::vector<int>* arr = (std::vector<int>*)temp;
    if (arr->empty()) return 0;

    long long sum = 0;
    int n = arr->size();
    for (int i = 0; i < n; i++) {
        sum += (*arr)[i];
        Sleep(12);
    }

    average = sum / n;
    std::cout << "avg: " << average << std::endl;
    return 0;
}

int GetAvg() {
    return average;
}