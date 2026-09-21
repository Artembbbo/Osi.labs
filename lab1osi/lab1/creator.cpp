#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

struct employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Creator usage: Creator.exe <binary_file_name> <record_count>\n";
        return 1;
    }

    std::string filename = argv[1];
    int record_count = std::atoi(argv[2]);

    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        std::cerr << "Error creating binary file: " << filename << "\n";
        return 1;
    }

    for (int i = 0; i < record_count; ++i) {
        employee emp;
        std::cout << "\nEnter data for employee #" << (i + 1) << ":\n";
        std::cout << "ID (num): ";
        std::cin >> emp.num;

        std::cout << "Name (max 9 chars): ";
        std::cin >> emp.name;

        std::cout << "Hours: ";
        std::cin >> emp.hours;

        out.write(reinterpret_cast<char*>(&emp), sizeof(employee));
    }

    out.close();
    std::cout << "Binary file successfully created.\n";
    return 0;
}
