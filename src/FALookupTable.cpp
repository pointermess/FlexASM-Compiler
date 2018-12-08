#include "stdafx.h"
#include "FALookupTable.h"


FlexASM::LookupTable::LookupTable()
{
}

FlexASM::LookupTable::~LookupTable()
{
}

void FlexASM::LookupTable::Add(const std::string name, const unsigned int value)
{
    _LookupTable.insert(std::pair<std::string, unsigned int>(name, value));
}

const bool FlexASM::LookupTable::Find(const std::string name, unsigned int& value)
{
    if (_LookupTable.find(name) != _LookupTable.end())
    {
        value = _LookupTable[name];
        return true;
    }
    return false;
}
