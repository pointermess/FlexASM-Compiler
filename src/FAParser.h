#pragma once

#include <memory>
#include <string>

#include "FAProgram.h"

class FAParser
{
public:
    FAParser();
    ~FAParser();

    std::shared_ptr<FAProgram> ParseString(std::string & input);
};

