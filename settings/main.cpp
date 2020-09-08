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
    Lily::csvFileHandler csvFileHandler{"/home/pi/C-Programmes/private_settings/settings.csv",
                                        {"settings", "value", "new"}};
    //csvFileHandler csvFileHandler{"/home/pi/C-Programmes/private_settings/settings.csv"};
    for (int i = 0; i < 30; i++) {
        csvFileHandler.writeRow({std::to_string(i), std::to_string(i), std::to_string(i)});
    }
    print(csvFileHandler.find("settings", "1"));
    std::cout << std::endl;
    csvFileHandler.sort("value");
    csvFileHandler.delete_row(0);
    csvFileHandler.delete_rows("settings", "1");
    csvFileHandler.change_row(csvFileHandler.find_index("new", "7"), "value", "hey");
    csvFileHandler.change_row(csvFileHandler.find("new", "8"), "value", "changed");
    for (const auto &row : csvFileHandler.getWholeFile()) {
        print(row);
        std::cout << "\n";
    }
    csvFileHandler.sort("settings");
    csvFileHandler.delete_row("new", "20");
    std::cout << "found values:" << std::endl;
    for (const auto &row : csvFileHandler.find_all("value", "2")) {
        print(row);
        std::cout << "\n";
    }
    return 0;
}
