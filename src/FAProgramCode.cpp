#include "stdafx.h"
#include "FAProgramCode.h"

void FlexASM::ProgramCode::AddSection(ProgramSectionPtr function)
{
    Sections.push_back(function);
}
FlexASM::ProgramSectionPtr FlexASM::ProgramCode::FindSection(std::string & name)
{
    for (auto& section : Sections)
        if (section->Name == name)
            return section;
    return nullptr;
}

bool FlexASM::ProgramCode::GetAddressOfSection(const std::string name, uint32_t & address)
{
    address = 0;
    for (auto& section : Sections)
    {
        if (section->Name == name)
            return true;
        address += section->GetSize();
    }
    return false;
}

std::vector<char> FlexASM::ProgramCode::GetOpcode()
{
    std::vector<char> result = {};
    for (auto& section : Sections)
    {
        std::vector<char> var = section->GetOpcode();
        result.insert(result.end(), var.begin(), var.end());
    }
    return result;
}

int FlexASM::ProgramCode::GetSize()
{
    return GetOpcode().size();
}

std::vector<char> FlexASM::ProgramSection::GetOpcode()
{
    std::vector<char> result = {};
    for (auto& instruction : Instructions)
    {
        std::vector<char> var = instruction->GetOpcode();
        result.insert(result.end(), var.begin(), var.end());
    }
    return result;
}

int FlexASM::ProgramSection::GetSize()
{
    return GetOpcode().size();
}
