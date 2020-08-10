//
// Created by 42kangaroo on 16.02.20.
//



#include "Lily_Speach_Assistant.hpp"

namespace Lily {
    void Lily_Speach_Assistant::Speach_Assistant() {
        Dictionary_txt::reloadIfNew();
        std::string hyp{};
        while (hyp != "STOP") {
            hyp = recog.recognize_with_keyphrase();
            std::cout << hyp << std::endl;
            std::string answer = list.getAnswer(hyp);
            speak::synthesize(answer);
        }
    }

    Lily_Speach_Assistant::Lily_Speach_Assistant() {
        Dictionary_txt::addMinimumPhrases();
    }
}