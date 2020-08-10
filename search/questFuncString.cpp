//
// Created by 42kangaroo on 22.04.20.
//

#include "questFuncString.hpp"

namespace Lily {
    questFuncString::questFuncString(strFuncParam function, std::vector<std::string> words, int priority, questType how)
            : questInterface(
            {"questFunc"}, words,
            priority, how), functionParam(std::move(function)) {}

    std::string questFuncString::getAnswer(std::string string) const {
        try {
            return functionParam(string);
        } catch (std::runtime_error &e) {
            using std::literals::string_literals::operator ""s;
            return "the function returned with the exception "s + e.what();
        }
    }

    questFuncString::questFuncString(questFuncString::strFuncParam function, std::vector<std::string> words,
                                     int priority, std::string lang, questType how) : questInterface(
            {"questFunc"}, words,
            priority, lang, how), functionParam(std::move(function)) {}

}