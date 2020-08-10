/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   speak.h
 * Author: yael
 *
 * Created on May 30, 2019, 6:25 PM
 */

#ifndef SPEAK_H
#define SPEAK_H

#include <string>
#include <cstdlib>
#include <utility>
#include <algorithm>
namespace Lily {
/**
 * The speech synthesis namespace
 */
    namespace speak {

        /**
        * Synthesize a given Text.
        * <br> You can specify the language by appending (lang:<i><b>your-language</b></i>) to the end of the text.
        * <br> The default language is mb-en1.
        * @param text the text to be synthesized
        */
        void synthesize(std::string text);

        /**
         * Set the speed.
         * @param speed the new speed.
         */
        void setSpeed(int p_speed);

        /**
        * Set the language. Format like ESpeak languages. Examples are mb-en1, it, mb-de6.
        * @param lang the language in ESpeak format.
        */
        void setLang(std::string language);
    }
}
#endif /* SPEAK_H */

