//
// Created by 42kangaroo on 21.12.19.
//

#include "questInterface.hpp"

#include <utility>

namespace Lily {
    questInterface::questInterface(std::vector<std::string> answer, std::vector<std::string> word, int priority,
                                   questType how)
            : questInterface(answer, word, priority, "mb-en1", how) {
    }


    int questInterface::getPriority() const {
        return priority;
    }

    int questInterface::setPriority(int priority) {
        if (priority > 99) {
            std::cout << "priority can't be set to more then 99: set to 99 " << "in questInterface with keyword "
                      << "\""
                      << getAsString()
                      << "\"" << std::endl;
            priority = 99;
        } else if (priority < 1) {
            std::cout << "priority can't be set to less then 1: set to 1 " << "in questInterface with keyword " << "\""
                      << getAsString()
                      << "\"" << std::endl;
            priority = 1;
        }
        this->priority = priority;
        return this->priority;
    }

    std::string questInterface::getAsString() const {
        std::string word;
        for (auto &str2 : getWords()) {
            if (str2 == getWords().back()) {
                word += str2;
            } else {
                word += str2 + ", ";
            }
        }
        return word;
    }

    bool questInterface::operator==(const questInterface &q) const {
        return q.getPriority() == this->getPriority();
    }

    bool questInterface::operator!=(const questInterface &q) const {
        return q.getPriority() != this->getPriority();
    }

    bool questInterface::operator<(const questInterface &q) const {
        return q.getPriority() > this->getPriority();
    }

    bool questInterface::operator>(const questInterface &q) const {
        return q.getPriority() < this->getPriority();
    }

    bool questInterface::operator>=(const questInterface &q) const {
        return q.getPriority() <= this->getPriority();
    }

    bool questInterface::operator<=(const questInterface &q) const {
        return q.getPriority() >= this->getPriority();
    }

    questInterface &questInterface::operator++() {
        if (this->priority < 100) {
            this->priority++;
        }
        return *this;
    }

    questInterface &questInterface::operator++(int) {
        questInterface &tmp(*this);
        operator++();
        return tmp;
    }

    questInterface &questInterface::operator--() {
        if (this->getPriority() > 1) {
            this->priority--;
        }
        return *this;
    }

    questInterface &questInterface::operator--(int) {
        questInterface &tmp(*this);
        operator--();
        return tmp;
    }

    questInterface &questInterface::operator+=(int increment) {
        this->priority += increment;
        if (this->getPriority() > 99) {
            this->setPriority(99);
        }
        return *this;
    }

    questInterface &questInterface::operator-=(int decrement) {
        this->priority -= decrement;
        if (this->getPriority() < 1) {
            this->setPriority(1);
        }
        return *this;
    }

    std::string questInterface::getLang() const {
        return lang;
    }

    std::vector<std::string> questInterface::getWords() const {
        return words;
    }

    questType questInterface::getQuestType() const {
        return how;
    }

    questInterface::questInterface(std::vector<std::string> answer, std::vector<std::string> word, int priority,
                                   std::string lang, questType how) : lang(std::move(lang)), answer(std::move(answer)),
                                                                      words(std::move(word)), how(how) {
        if (this->words.empty()) {
            throw std::invalid_argument("question words required required");
        }
        if (this->answer.empty()) {
            throw std::invalid_argument("answer is required");
        }
        setPriority(priority);
    }


}