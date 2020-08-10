//
// Created by 42kangaroo on 29.12.19.
//

#ifndef SEARCH_LISTQUEST_HPP
#define SEARCH_LISTQUEST_HPP

#include <iostream>
#include <set>
#include <iterator>
#include <string>
#include "questInterface.hpp"
#include "questFunc.hpp"
#include "NormalQuestion.hpp"
#include "questFuncString.hpp"
#include "functions/LilyStdFuncs.hpp"
#include "functions/LilyStdFuncsString.hpp"
#include "listen/Dictionary_txt.hpp"
#include <QtSql>
#include <memory>
#include "addGUI/Database_handler.hpp"

namespace Lily {
    class listQuest {
    public:
        /**
         * intitialises a interface for questions. Reads the database and adds some standard answers.
         */
        listQuest();

        using strFunc = std::function<std::string()>;
        using strFuncParam = std::function<std::string(std::string)>;

        /**
         *
         * @param question the recognized phrase.
         * @return the answer for this phrase
         */
        std::string getAnswer(const std::string &question);

        /**
         * Adds a question element
         * @param answer what Lily should answer if the question is asked. If you make multiple answers, one is chosen randomly
         * @param word the words which must be said for Lily to choose this question. If their are multiple ones, each of them must apear once in the recognized sentence
         * @param priority the priority over other questions. 1 is the highest and 99 the lowest Priority.
         * @param how if the recognized sentence must exactly by the same as the Sentence you put into the word variable, use questType::IS
         */
        void addEllements(std::vector<std::string> answer, std::vector<std::string> words, int priority,
                          questType how = questType::HAS);

        /**
         * Adds a question element
         * @param function a function to run when question is chosen. Should return a string
         * @param word the words which must be said for Lily to choose this question. If their are multiple ones, each of them must apear once in the recognized sentence
         * @param priority the priority over other questions. 1 is the highest and 99 the lowest Priority.
         * @param how if the recognized sentence must exactly by the same as the Sentence you put into the word variable, use questType::IS
         */
        void
        addEllements(strFunc function, std::vector<std::string> words, int priority, questType how = questType::HAS);

        /**
         * Adds a question element
         * @param function a function to run when question is chosen. Should take and return a string
         * @param word the words which must be said for Lily to choose this question. If their are multiple ones, each of them must apear once in the recognized sentence
         * @param priority the priority over other questions. 1 is the highest and 99 the lowest Priority.
         * @param how if the recognized sentence must exactly by the same as the Sentence you put into the word variable, use questType::IS
         */
        void addEllements(strFuncParam function, std::vector<std::string> words, int priority,
                          questType how = questType::HAS);

        /**
         * Adds a question element
         * @param answer what Lily should answer if the question is asked. If you make multiple answers, one is chosen randomly
         * @param word the words which must be said for Lily to choose this question. If their are multiple ones, each of them must apear once in the recognized sentence
         * @param priority the priority over other questions. 1 is the highest and 99 the lowest Priority.
         * @param lang the language in wich Lily will answer. must be in ESpeak format, e.g. mb-en1, it, mb-de6.
         * @param how if the recognized sentence must exactly by the same as the Sentence you put into the word variable, use questType::IS
         */
        void
        addEllements(std::vector<std::string> answer, std::vector<std::string> words, int priority,
                     const std::string &lang,
                     questType how = questType::HAS);

        /**
         * Adds a question element
         * @param function a function to run when question is chosen. Should return a string
         * @param word the words which must be said for Lily to choose this question. If their are multiple ones, each of them must apear once in the recognized sentence
         * @param priority the priority over other questions. 1 is the highest and 99 the lowest Priority.
         * @param lang the language in wich Lily will answer. must be in ESpeak format, e.g. mb-en1, it, mb-de6.
         * @param how if the recognized sentence must exactly by the same as the Sentence you put into the word variable, use questType::IS
         */
        void
        addEllements(strFunc function, std::vector<std::string> words, int priority, const std::string &lang,
                     questType how = questType::HAS);

        /**
         * Adds a question element
         * @param function a function to run when question is chosen. Should take and return a string
         * @param word the words which must be said for Lily to choose this question. If their are multiple ones, each of them must apear once in the recognized sentence
         * @param priority the priority over other questions. 1 is the highest and 99 the lowest Priority.
         * @param lang the language in wich Lily will answer. must be in ESpeak format, e.g. mb-en1, it, mb-de6.
         * @param how if the recognized sentence must exactly by the same as the Sentence you put into the word variable, use questType::IS
         */
        void addEllements(strFuncParam function, std::vector<std::string> words, int priority, const std::string &lang,
                          questType how = questType::HAS);

    private:
        /**
         * checks if the new question makes an other unreachable
         * @param quest the new question
         * @return true if it makes another question unreachable
         */
        bool doesMakeOtherImpossible(std::shared_ptr<questInterface> quest);

        Database_handler db;

        /**
         * loads the database into listQuest
         */
        void loadDatabase();

        /**
         * compares the priority of two questions
         * @param quest1 the first question
         * @param quest2 the second question
         * @return the question with the higher priority or samePriority if both have the same priority
         */
        std::shared_ptr<questInterface>
        comparePriotity(const std::shared_ptr<questInterface> &quest1, const std::shared_ptr<questInterface> &quest2);

        static std::vector<std::shared_ptr<questInterface>> sameAnswers;

        /**
         *
         * @return all the answers with the same priority.
         */
        static std::string getSameAnswers();

        std::shared_ptr<questInterface> samePriority;
        using listType = std::multiset<std::shared_ptr<questInterface>, std::function<bool(
                std::shared_ptr<questInterface>, std::shared_ptr<questInterface>)>>;
        listType questList{[](
                std::shared_ptr<questInterface> a, std::shared_ptr<questInterface> b) { return *a < *b; }};
        listType::iterator it;

        /**
         * turns a string into a vector, separated at the commas
         * @param inputSting
         * @return the vector with the question words.
         */
        std::vector<std::string> String2Vector(const std::string &inputSting);

    };

}
#endif //SEARCH_LISTQUEST_HPP
