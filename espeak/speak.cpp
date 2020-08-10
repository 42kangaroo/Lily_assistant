/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   speak.cpp
 * Author: yael
 *
 * Created on May 30, 2019, 6:25 PM
 */

#include "speak.hpp"

using std::string;

namespace {
    /**
     * the current language
     */
    std::string lang{"mb-en1"};
    /**
     * the current speed
     */
    int speed{100};
    /**
     * the additional speed for the language. For example, french is very slow and needs additional speed.
     */
    int lang_plus_speed{0};

    /**
     * Get the current language settings
     * @return the language
     */
    string getLang() {
        return lang;
    }

    /**
     * Get the current speed settings
     * @return the speed
     */
    int getSpeed() {
        return speed + lang_plus_speed;
    }
}
namespace Lily {
    namespace speak {
        void setSpeed(int p_speed) {
            speed = p_speed;
        }

        /**
     * Get the current language settings
     * @return the language
     */
        void setLang(string language) {
            language.erase(std::remove(language.begin(), language.end(), ' '), language.end());
            if (language == "mb-de6") {
                lang_plus_speed = 40;
            } else if (language == "mb-fr1") {
                lang_plus_speed = -10;
            } else {
                lang_plus_speed = 0;
            }
            lang = std::move(language);
        }

        void synthesize(string text) {
            std::replace(text.begin(), text.end(), '\"', '\'');
            if (text.find("(lang:") != string::npos) {
                std::string lang = text.substr(text.find("(lang:") + 6, text.size() - (text.find("(lang:") + 7));
                setLang(lang);
                text = text.substr(0, text.find("(lang:"));
            }
            string first = "espeak-ng --stdout -v";
            string second = "+f4 -k5 -s" + std::to_string(getSpeed()) + " \"";
            string end = "\" | aplay -q";
            string sCommand = first + getLang() + second + text + end;
            const char *command = sCommand.c_str();
            system(command);
        }
    }
}