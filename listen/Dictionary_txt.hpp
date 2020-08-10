//
// Created by 42kangaroo on 23.04.20.
//

#ifndef LISTEN_DICTIONARY_TXT_HPP
#define LISTEN_DICTIONARY_TXT_HPP

#include <string>
#include <fstream>
#include <curl/curl.h>
#include <memory>
#include <iostream>
#include <algorithm>
#include <sstream>


namespace Lily {
    namespace Dictionary_txt {
        /**
         * generate the .dic and .lm file
         */
        void reload_dic();
        /**
         * adds a string to the dictionary
         * @param str the string to add
         */
        void addToDic(std::string str);
        /**
         * reloads the dictionary if new files words where added
         */
        void reloadIfNew();
        /**
         * adds minimum phrases to the dictionary like "stop", "hey Lily" and "raspberry pi"
         */
        void addMinimumPhrases();
    }
}

#endif //LISTEN_DICTIONARY_TXT_HPP
