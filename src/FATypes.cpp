#include "stdafx.h"

#include "FATypes.h"

void FAInitValidRegisters()
{
    FAValidRegisters.push_back({ "al", farAL });
    FAValidRegisters.push_back({ "ah", farAH });
    FAValidRegisters.push_back({ "ax", farAX });
    FAValidRegisters.push_back({ "eax", farEAX });
}

bool IsValidRegister(std::string & string)
{
    for (auto& validRegister : FAValidRegisters)
        if (validRegister.Name == string) return true;
    return false;
}

void FAInitValidInstructions()
{
}

bool IsValidInstruction(std::string & pattern)
{
    return false;
}
