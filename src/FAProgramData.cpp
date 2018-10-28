#include "stdafx.h"
#include "FAProgramData.h"

bool FlexASM::ProgramData::GetAddressOfVariable(const std::string name, uint32_t& address)
{
    address = 0;
    for (auto& variable : Variables)
    {
        if (variable->Name == name)
            return address;
        address += (uint8_t)variable->Size * variable->Length;
    }
    return false;
}


FlexASM::ProgramDataVariable::ProgramDataVariable(const std::string  name, MemorySize size, uint32_t length)
{
    Length = length;
    Size = size;
    Name = name;
}

std::vector<uint8_t> FlexASM::ProgramDataVariable::GetOpcode()
{
    switch (Size)
    {
   
    }
}



FlexASM::ProgramDataInitializedVariable::ProgramDataInitializedVariable(const std::string name, MemorySize size, std::vector<uint32_t>& data)
    : ProgramDataVariable(name, size)
{
    Data = data;
    Length = data.size();
}