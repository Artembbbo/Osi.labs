#include <iostream>
#include <windows.h>
#include <cstdint>
#include <vector>
std::vector <int> arr;
int max = INT32_MIN;
int min = INT32_MAX;
int average = 0;
DWORD WINAPI min_max(LPVOID temp) {
	if (arr.empty()) {
		return 0;
	}
	int n = arr.size();
	for (int i = 0;i < n;i++) {
		if (arr[i] > max) { max = arr[i]; }
		if (arr[i] < min) { min = arr[i]; }
		Sleep(7);
	}
	std::cout << "Max: " << max << std::endl;
	std::cout << "Min: " << min << std::endl;
	return 0;
}
typedef DWORD(WINAPI* AVG_FUNC)(LPVOID);
typedef int(*GET_AVG_FUNC)();
int main()
{
	int n = 0;
	DWORD IDThread1;
	std::cin >> n;
	arr.resize(n);
	for (int i = 0;i < n;i++) {
		std::cin >> arr[i];
	}
	HMODULE hLib = LoadLibraryA("Dll1.dll");
	AVG_FUNC dll_avg = (AVG_FUNC)GetProcAddress(hLib, "avg");
	GET_AVG_FUNC dll_GetAvg = (GET_AVG_FUNC)GetProcAddress(hLib, "GetAvg");
	HANDLE hTHREAD = CreateThread(
		NULL,
		0,
		min_max,
		&arr,
		0,
		&IDThread1
	);
	DWORD IDThread2;
	HANDLE Hthread2 = CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)dll_avg,
		&arr,
		0,
		&IDThread2
	);
	if (hTHREAD != NULL) {
		WaitForSingleObject(hTHREAD, INFINITE);
		CloseHandle(hTHREAD);
	}

	if (Hthread2 != NULL) {
		WaitForSingleObject(Hthread2, INFINITE);
		CloseHandle(Hthread2);
	}
	average = dll_GetAvg();
	FreeLibrary(hLib);
	for (int i = 0;i < n;i++) {
		if (arr[i] == max) { arr[i] = average; }
		else
			if (arr[i] == min) { arr[i] = average; }
		std::cout << arr[i] << " ";
	}
}

