#pragma once

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows
#include <windows.h>
extern "C" __declspec(dllexport) DWORD WINAPI avg(LPVOID temp);
extern "C" __declspec(dllexport) int GetAvg();