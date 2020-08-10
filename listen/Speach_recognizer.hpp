//
// Created by 42kangaroo on 17.09.19.
//

#ifndef LISTEN_MIC_HPP
#define LISTEN_MIC_HPP

#include <pocketsphinx/pocketsphinx.h>
#include <sphinxbase/ad.h>
#include <string>
#include <alsa/asoundlib.h>
#include <alsa/pcm.h>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <curl/curl.h>
#include <algorithm>
#include <unistd.h>
#include <memory>
#include "Dictionary_txt.hpp"
/**
 * Die speech to text namespace
 */
namespace Lily {
    namespace Speach_recognizer {

        void init();

        void free();

        std::string recognize_with_keyphrase();


    }
    /**
     * RAII wrapper for Speach_recognizer
     */
    class SpeechRocognizerWrapper {
    public:
        SpeechRocognizerWrapper() {
            Speach_recognizer::init();

        }

        ~SpeechRocognizerWrapper() { Speach_recognizer::free(); }

        /**
 * recognize a phrase, but only after hearing the Keyphrase
 * @return the recognized phrase without the keyphrase
 */
        std::string recognize_with_keyphrase() { return Speach_recognizer::recognize_with_keyphrase(); }
    };
}
#endif //LISTEN_MIC_HPP
