#include "listQuest.hpp"


int main() {
    Lily::listQuest list{};
    std::cout << list.getAnswer("what dath"
                                "") << std::endl;
    return 0;
}

