#include "stdafx.h"
#include "Types.h"

void FAInitValidRegisters()
{
    FAValidRegisters.push_back({ "al", farAL });
    FAValidRegisters.push_back({ "ah", farAL });
    FAValidRegisters.push_back({ "al", farAL });
    FAValidRegisters.push_back({ "al", farAL });
}

bool IsValidRegister(std::string string)
{
    return false;
}
