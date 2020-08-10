//
// Created by 42kangaroo on 22.04.20.
//


#ifndef SEARCH_NORMALQUESTION_HPP
#define SEARCH_NORMALQUESTION_HPP

#include "questInterface.hpp"

namespace Lily {
    class NormalQuestion : public questInterface {
    public:
        using questInterface::questInterface;

        std::string getAnswer(std::string string) const override;
    };
}

#endif //SEARCH_NORMALQUESTION_HPP
