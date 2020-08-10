//
// Created by 42kangaroo on 22.04.20.
//

#include "NormalQuestion.hpp"

namespace Lily {
    std::string NormalQuestion::getAnswer(std::string question) const {
        std::random_device randomDevice{};
        std::uniform_int_distribution<size_t> distribution{0, answer.size() - 1};
        return answer.at(distribution(randomDevice));
    }
}