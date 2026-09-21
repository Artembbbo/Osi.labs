#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <algorithm>

struct employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Reporter usage: Reporter.exe <binary_file> <report_file> <hourly_rate>\n";
        return 1;
    }

    std::string binary_filename = argv[1];
    std::string report_filename = argv[2];
    double hourly_rate = std::atof(argv[3]);

    std::ifstream in(binary_filename, std::ios::binary);
    if (!in) {
        std::cerr << "Error opening binary file: " << binary_filename << "\n";
        return 1;
    }

    std::vector<employee> employees;
    employee emp;

    while (in.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        employees.push_back(emp);
    }
    in.close();


    std::sort(employees.begin(), employees.end(), [](const employee& a, const employee& b) {
        return a.num < b.num;
        });

    std::ofstream out(report_filename);
    if (!out) {
        std::cerr << "Error creating report file: " << report_filename << "\n";
        return 1;
    }

    out << "Report for file \"" << binary_filename << "\"\n";
    out << "Employee ID, Employee Name, Hours, Salary\n";

    for (const auto& item : employees) {
        double salary = item.hours * hourly_rate;
        out << item.num << ", " << item.name << ", " << item.hours << ", "
            << std::fixed << std::setprecision(2) << salary << "\n";
    }

    out.close();
    std::cout << "Report file successfully created.\n";
    return 0;
}
