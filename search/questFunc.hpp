//
// Created by 42kangaroo on 05.01.20.
//

#ifndef SEARCH_QUESTFUNC_HPP
#define SEARCH_QUESTFUNC_HPP

#include "questInterface.hpp"

namespace Lily {
    class questFunc : public questInterface {
    public:
        using strFunc = std::function<std::string()>;

        /**
         * question with function as answer
         * @param function a function to run when question is chosen. Should return a string
         * @param word the words which must be said for Lily to choose this question. If their are multiple ones, each of them must apear once in the recognized sentence
         * @param priority the priority over other questions. 1 is the highest and 99 the lowest Priority.
         * @param how if the recognized sentence must exactly by the same as the Sentence you put into the word variable, use questType::IS
         */
        questFunc(strFunc function, std::vector<std::string> words, int priority, questType how = questType::HAS);

        /**
         * question with function as answer
         * @param function a function to run when question is chosen. Should return a string
         * @param word the words which must be said for Lily to choose this question. If their are multiple ones, each of them must apear once in the recognized sentence
         * @param priority the priority over other questions. 1 is the highest and 99 the lowest Priority.
         * @param lang the language in wich Lily will answer. must be in ESpeak format, e.g. mb-en1, it, mb-de6.
         * @param how if the recognized sentence must exactly by the same as the Sentence you put into the word variable, use questType::IS
         */
        questFunc(strFunc function, std::vector<std::string> words, int priority, std::string lang,
                  questType how = questType::HAS);

        std::string getAnswer(std::string string) const override;

    private:
        strFunc function;
    };
}

#endif //SEARCH_QUESTFUNC_HPP
