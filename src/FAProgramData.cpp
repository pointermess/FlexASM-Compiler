#include "stdafx.h"
#include "FAProgramData.h"

bool FlexASM::ProgramData::GetAddressOfVariable(const std::string name, uint32_t& address)
{
    address = 0;
    for (auto& variable : Variables)
    {
        if (variable->Name == name)
            return address;
        address += (uint8_t)variable->Size * variable->GetLength();
    }
    return false;
}

std::vector<uint8_t> FlexASM::ProgramData::GetOpcode()
{
    std::vector<uint8_t> result = {};
    for (auto& variable : Variables)
    {
        std::vector<uint8_t> var = variable->GetOpcode();
        result.insert(result.end(), var.begin(), var.end());
    }
    return result;
}


uint32_t FlexASM::ProgramDataVariable::GetLength()
{
	return Length;
}

FlexASM::ProgramDataVariable::ProgramDataVariable(const std::string  name, MemorySize size, uint32_t length)
{
    Length = length;
    Size = size;
    Name = name;
}

std::vector<uint8_t> FlexASM::ProgramDataVariable::GetOpcode()
{
    auto length = GetLength();
    if (Size == msByte)
        return { (uint8_t)fapiRESB, (uint8_t)(length >> 24), (uint8_t)(length >> 16), (uint8_t)(length >> 8), (uint8_t)length };
    if (Size == msWord)
        return { (uint8_t)fapiRESW, (uint8_t)(length >> 24), (uint8_t)(length >> 16), (uint8_t)(length >> 8), (uint8_t)length };
    if (Size == msDWord)
        return { (uint8_t)fapiRESD, (uint8_t)(length >> 24), (uint8_t)(length >> 16), (uint8_t)(length >> 8), (uint8_t)length };
}



FlexASM::ProgramDataInitializedVariable::ProgramDataInitializedVariable(const std::string name, MemorySize size, std::vector<uint32_t>& data)
{
    Name = name;
    Size = size;
    Data = data;
}

uint32_t FlexASM::ProgramDataInitializedVariable::GetLength()
{
	return Data.size();
}

std::vector<uint8_t> FlexASM::ProgramDataInitializedVariable::GetOpcode()
{
    std::vector<uint8_t> result = {};

    auto length = GetLength();
    if (Size == msByte)
    {
        result.push_back((uint8_t)fapiDB);
        result.push_back((length >> 24));
        result.push_back((length >> 16));
        result.push_back((length >> 8));
        result.push_back((length));

        for (uint8_t byte : Data)
        {
            result.push_back(byte);
        }
    }
    else if (Size == msWord)
    {
        result.push_back((uint8_t)fapiDW);
        result.push_back((length >> 24));
        result.push_back((length >> 16));
        result.push_back((length >> 8));
        result.push_back((length));

        for (uint16_t word : Data)
        {
            result.push_back((word >> 8));
            result.push_back((word));
        }
    }
    else if (Size == msDWord)
    {
        result.push_back((uint8_t)fapiDD);
        result.push_back((length >> 24));
        result.push_back((length >> 16));
        result.push_back((length >> 8));
        result.push_back((length));

        for (uint32_t dword : Data)
        {
            result.push_back((dword >> 24));
            result.push_back((dword >> 16));
            result.push_back((dword >> 8));
            result.push_back((dword));
        }
    }

    return result;
}
