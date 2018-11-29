#include "stdafx.h"
#include <algorithm>
#include <fstream>
#include <streambuf>

#include "Utilities.h"

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

void str_to_lower(std::string & s)
{
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
}

std::string read_file(std::string fileName)
{
    std::ifstream t(fileName);
    std::string result((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());
    return result;
}

int parse_number(std::string number)
{
    if (number.length() > 2)
    {
        std::string prefix;
        std::string value;
        prefix.assign(number, 0, 2);
        value.assign(number, 2, number.length() - 2);

        if (prefix == "0x")
            return std::stoi(value, nullptr, 16);
        if (prefix == "0o")
            return std::stoi(value, nullptr, 8);
        if (prefix == "0b")
            return std::stoi(value, nullptr, 2);
    }
    return std::stoi(number);
}
