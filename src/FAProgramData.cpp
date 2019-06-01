#include "stdafx.h"
#include "FAProgramData.h"

bool FlexASM::ProgramData::GetAddressOfVariable(const std::string name, uint32_t& address)
{
    address = 33;
    for (auto& variable : Variables)
    {
        if (variable->Name == name)
            return true;
        address += (uint8_t)variable->Size * variable->GetLength();
    }
    return false;
}

std::vector<char> FlexASM::ProgramData::GetOpcode()
{
    std::vector<char> result = {};
    for (auto& variable : Variables)
    {
        std::vector<char> var = variable->GetOpcode();
        result.insert(result.end(), var.begin(), var.end());
    }
    return result;
}

int FlexASM::ProgramData::GetSize()
{
    return GetOpcode().size();
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

std::vector<char> FlexASM::ProgramDataVariable::GetOpcode()
{
    auto length = GetLength();
    if (Size == msByte)
        return { (char)fapiRESB, (char)(length >> 24), (char)(length >> 16), (char)(length >> 8), (char)length };
    if (Size == msWord)
        return { (char)fapiRESW, (char)(length >> 24), (char)(length >> 16), (char)(length >> 8), (char)length };
    if (Size == msDWord)
        return { (char)fapiRESD, (char)(length >> 24), (char)(length >> 16), (char)(length >> 8), (char)length };
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

std::vector<char> FlexASM::ProgramDataInitializedVariable::GetOpcode()
{
    std::vector<char> result = {};

    auto length = GetLength();
    if (Size == msByte)
    {
        result.push_back((char)fapiDB);
        result.push_back((length >> 24));
        result.push_back((length >> 16));
        result.push_back((length >> 8));
        result.push_back((length));

        for (char byte : Data)
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
