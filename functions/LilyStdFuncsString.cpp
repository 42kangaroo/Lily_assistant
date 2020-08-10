//
// Created by 42kangaroo on 07.05.20.
//


#include "LilyStdFuncsString.hpp"
namespace Lily::functions {
    namespace repeat {
        std::string repeatWhatSaid(std::string saidStr){
            auto it = saidStr.find("SAY");
            if (it == std::string::npos){
                throw std::runtime_error("could not find say in string");
            }
            saidStr = saidStr.substr(it+3, saidStr.size()-(it+3));
            return saidStr;
        }
    }
}