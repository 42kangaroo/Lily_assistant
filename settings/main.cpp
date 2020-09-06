#include "csvFileHandler.hpp"
//#include <sys/stat.h>
#include <iostream>

template<typename outType>
void print(outType containerType) {
    for (const auto &attribute : containerType) {
        std::cout << attribute << " ";
    }
}

int main() {
    //mkdir("/home/pi/C-Programmes/private_settings", 0777);
    csvFileHandler csvFileHandler{"/home/pi/C-Programmes/private_settings/settings.csv", {"settings", "value", "new"}};
    //csvFileHandler csvFileHandler{"/home/pi/C-Programmes/private_settings/settings.csv"};
    for (int i = 0; i < 30; i++) {
        csvFileHandler.writeRow({std::to_string(i), std::to_string(i), std::to_string(i)});
    }
    print(csvFileHandler.find("settings", "1"));
    std::cout << std::endl;
    csvFileHandler.sort("value");
    for (const auto &row : csvFileHandler.getWholeFile()) {
        print(row);
        std::cout << "\n";
    }
    csvFileHandler.sort("settings");
    std::cout << "found values:" << std::endl;
    for (const auto &row : csvFileHandler.find_all("value", "2")) {
        print(row);
        std::cout << "\n";
    }
    return 0;
}
