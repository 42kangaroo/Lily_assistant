//
// Created by 42kangaroo on 16.02.20.
//

#ifndef LILY_MAIN_LILY_SPEACH_ASSISTANT_HPP
#define LILY_MAIN_LILY_SPEACH_ASSISTANT_HPP

#include <string>
#include <iostream>
#include <listen/Speach_recognizer.hpp>
#include <espeak/speak.hpp>
#include <search/listQuest.hpp>

namespace Lily {
    class Lily_Speach_Assistant {
    public:
        void Speach_Assistant();

        Lily_Speach_Assistant();

        ~Lily_Speach_Assistant() = default;

        Lily_Speach_Assistant(const Lily_Speach_Assistant &) = delete;

        Lily_Speach_Assistant &operator=(const Lily_Speach_Assistant &) = delete;

    private:
        SpeechRocognizerWrapper recog{};
    public: //for testing
        listQuest list{};
    };
}

#endif //LILY_MAIN_LILY_SPEACH_ASSISTANT_HPP
