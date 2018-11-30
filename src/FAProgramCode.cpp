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

std::vector<uint8_t> FlexASM::ProgramCode::GetOpcode()
{ 
    return {};
}
