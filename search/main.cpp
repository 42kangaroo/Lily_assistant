#include "listQuest.hpp"


int main() {
    Lily::listQuest list{};
    std::cout << list.getAnswer("what is the time") << std::endl;
    return 0;
}

