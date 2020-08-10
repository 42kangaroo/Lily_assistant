//
// Created by 42kangaroo on 07.05.20.
//

#ifndef FUNCTIONS_LILYSTDFUNCSSTRING_HPP
#define FUNCTIONS_LILYSTDFUNCSSTRING_HPP


#include <string>
#include <stdexcept>

namespace Lily::functions {
    namespace repeat {
        /**
         * function to repeat what was said
         * @param saidStr the string that was said.
         * @return the same string apart from the "say"
         */
        std::string repeatWhatSaid(std::string saidStr);
    }
}


#endif //FUNCTIONS_LILYSTDFUNCSSTRING_HPP
