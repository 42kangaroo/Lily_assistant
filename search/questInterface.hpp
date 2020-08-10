//
// Created by 42kangaroo on 21.12.19.
//

#ifndef SEARCH_QUESTINTERFACE_HPP
#define SEARCH_QUESTINTERFACE_HPP

#include <random>
#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include "questType.hpp"

namespace Lily {

    /**
     * the Interface for creating new questions for Lily
     */
    class questInterface {
    public:
        /**
         * the Interface for creating new questions for Lily
         * @param answer what Lily should answer if the question is asked. If you make multiple answers, one is chosen randomly
         * @param word the words which must be said for Lily to choose this question. If their are multiple ones, each of them must apear once in the recognized sentence
         * @param priority the priority over other questions. 1 is the highest and 99 the lowest Priority.
         * @param how if the recognized sentence must exactly by the same as the Sentence you put into the word variable, use questType::IS
         */
        questInterface(std::vector<std::string> answer, std::vector<std::string> word, int priority,
                       questType how = questType::HAS);

        /**
         * the Interface for creating new questions for Lily
         * @param answer what Lily should answer if the question is asked. If you make multiple answers, one is chosen randomly
         * @param word the words which must be said for Lily to choose this question. If their are multiple ones, each of them must apear once in the recognized sentence
         * @param priority the priority over other questions. 1 is the highest and 99 the lowest Priority.
         * @param lang the language in wich Lily will answer. must be in ESpeak format, e.g. mb-en1, it, mb-de6.
         * @param how if the recognized sentence must exactly by the same as the Sentence you put into the word variable, use questType::IS
         */
        questInterface(std::vector<std::string> answer, std::vector<std::string> word, int priority, std::string lang,
                       questType how = questType::HAS);

        /**
         * @return the language setting.
         */
        std::string getLang() const;

        /**
         *
         * @return the priority
         */
        int getPriority() const;

        /**
         * @return the multiple words as a string, separeted by a a coma
         */
        virtual std::string getAsString() const;

        /**
         *
         * @return the question words as a vector
         */
        std::vector<std::string> getWords() const;

        /**
         *
         * @param string you must pass the question hear for the functions who need it
         * @return the answer for the question
         */
        virtual std::string getAnswer(std::string string) const = 0;

        /**
         *
         * @return the Type of the question, HAS or IS
         */
        questType getQuestType() const;

        /**
         *
         * @param priority the new Priority. must be between 1 and 99. 1 is the highest priority.
         * @return the new priority
         */
        int setPriority(int priority);

        /**
         * compare the priority
         */
        bool operator==(const questInterface &) const;

/**
         * compare the priority
         */
        bool operator!=(const questInterface &) const;

/**
         * compare the priority
         */
        bool operator<(const questInterface &) const;

/**
         * compare the priority
         */
        bool operator>(const questInterface &) const;

/**
         * compare the priority
         */
        bool operator<=(const questInterface &) const;

/**
         * compare the priority
         */
        bool operator>=(const questInterface &) const;

        /**
         * change the priotity
         */
        questInterface &operator++();

/**
         * change the priotity
         */
        questInterface &operator++(int);

/**
         * change the priotity
         */
        questInterface &operator--();

/**
         * change the priotity
         */
        questInterface &operator--(int);

/**
         * change the priotity
         */
        questInterface &operator+=(int);

/**
         * change the priotity
         */
        questInterface &operator-=(int);


    protected:
        const questType how;
        const std::vector<std::string> words;
        int priority{};
        const std::vector<std::string> answer;
        const std::string lang;
    };
}

#endif //SEARCH_QUESTINTERFACE_HPP
