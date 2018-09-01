#include "stdafx.h"

#include "FAParser.h"


FAParser::FAParser()
{
}


FAParser::~FAParser()
{
}

std::shared_ptr<FAProgram> FAParser::ParseString(std::string & input)
{
    std::shared_ptr<FAProgram> result = std::make_shared<FAProgram>();
    return nullptr;
}
