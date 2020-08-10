//
// Created by 42kangaroo on 16.09.19.
//

#include <iostream>
#include "Speach_recognizer.hpp"
/**
 * the testing main
 */
int main(int argc, char *argv[]) {
    using namespace Lily;
    try {
        Dictionary_txt::addMinimumPhrases();
        Dictionary_txt::reloadIfNew();
        SpeechRocognizerWrapper recog{};
        std::string hyp{};
        while (hyp != "STOP") {
            hyp = recog.recognize_with_keyphrase();
            std::cout << hyp << "\n";
        }
    } catch (std::exception &e) {
        std::cout << e.what() << "\n";
    }
    return 0;
}

