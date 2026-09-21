#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <iomanip>

struct employee {
    int num;
    char name[10];
    double hours;
};

bool run_process(const std::wstring& cmd_line) {
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    std::wstring writable_cmd = cmd_line;

    if (!CreateProcessW(
        NULL,
        &writable_cmd[0],
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    )) {
        std::cerr << "CreateProcess failed (" << GetLastError() << ").\n";
        return false;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return true;
}

int main() {
    std::string bin_filename;
    int record_count;

    std::cout << "Enter binary file name: ";
    std::cin >> bin_filename;
    std::cout << "Enter number of records: ";
    std::cin >> record_count;
    if (record_count <= 0) {
        std::cerr << "Error: Number of records must be greater than 0.\n";
        std::cout << "Program finished with error.\n";
        return 1;
    }

    std::wstring creator_cmd = L"Creator.exe " +
        std::wstring(bin_filename.begin(), bin_filename.end()) +
        L" " + std::to_wstring(record_count);
    if (!run_process(creator_cmd)) return 1;

    std::cout << "\n Binary File Content \n";
    std::ifstream in(bin_filename, std::ios::binary);
    if (!in) {
        std::cerr << "Failed to open binary file.\n";
    }
    else {
        employee emp;
        while (in.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
            std::cout << "ID: " << emp.num << " | Name: " << emp.name << " | Hours: " << emp.hours << "\n";
        }
        in.close();
    }

    std::string report_filename;
    double hourly_rate;
    std::cout << "\nEnter report file name: ";
    std::cin >> report_filename;
    std::cout << "Enter hourly rate: ";
    std::cin >> hourly_rate;

    std::wstring reporter_cmd = L"Reporter.exe " +
        std::wstring(bin_filename.begin(), bin_filename.end()) + L" " +
        std::wstring(report_filename.begin(), report_filename.end()) + L" " +
        std::to_wstring(hourly_rate);

    if (!run_process(reporter_cmd)) return 1;

    std::cout << "\n Report File Content \n";
    std::ifstream report_file(report_filename);
    if (!report_file) {
        std::cerr << "Failed to open report file.\n";
    }
    else {
        std::string line;
        while (std::getline(report_file, line)) {
            std::cout << line << "\n";
        }
        report_file.close();
    }

    std::cout << "\nProgram finished successfully.\n";
    return 0;
}
