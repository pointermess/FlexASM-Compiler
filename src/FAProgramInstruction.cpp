#include "stdafx.h"
#include "FAProgramInstruction.h"

std::vector<char> FlexASM::ProgramInstructionConstIntParameter::GetOpcode()
{
    MemorySize opSize = OperationSize;

    if (opSize == msUndefined)
        opSize = msDWord;


    if (opSize == msByte)
        return { (char)opSize, (char)Value };
    if (opSize == msWord)
        return { (char)opSize, (char)(Value >> 8), (char)Value };
    if (opSize == msDWord)
        return { (char)opSize, (char)(Value >> 24), (char)(Value >> 16), (char)(Value >> 8), (char)Value };
}

std::string FlexASM::ProgramInstructionConstIntParameter::GetPattern()
{
    return "const";
}

std::vector<char> FlexASM::ProgramInstructionRegisterParameter::GetOpcode()
{
    MemorySize opSize = OperationSize;

    if (opSize == msUndefined)
        opSize = msDWord;

    return { 0 };
}

std::string FlexASM::ProgramInstructionRegisterParameter::GetPattern()
{
    return "reg";
}

const std::string FlexASM::ProgramInstruction::BuildPattern()
{
    std::string pattern = InstructionStr;

    for (auto& param : Parameters)
    {
        pattern += "_" + param->GetPattern();
    }
    
    return pattern;
}

std::string FlexASM::ProgramInstructionAddressParameter::GetPattern()
{
    return "addr";
}
