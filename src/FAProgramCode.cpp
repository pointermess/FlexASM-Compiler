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
