//
// Created by 42kangaroo on 05.01.20.
//

#include "questFunc.hpp"

namespace Lily {
    questFunc::questFunc(strFunc function, std::vector<std::string> words, int priority, questType how)
            : questInterface(
            {"questFunc"},
            words,
            priority,
            how), function(std::move(function)) {}

    std::string questFunc::getAnswer(std::string question) const {
        try {
            return function();
        }
        catch (std::runtime_error &e) {
            using std::literals::string_literals::operator ""s;
            return "the function failed with exception "s + e.what();
        }

    }

    questFunc::questFunc(questFunc::strFunc function, std::vector<std::string> words, int priority, std::string lang,
                         questType how) : questInterface({"questFunc"},
                                                         words,
                                                         priority,
                                                         lang,
                                                         how), function(std::move(function)) {}
}