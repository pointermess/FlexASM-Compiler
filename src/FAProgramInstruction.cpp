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

    return { (char)Value };
}

std::string FlexASM::ProgramInstructionRegisterParameter::GetPattern()
{
    return "reg";
}

std::vector<char> FlexASM::ProgramInstruction::GetOpcode()
{
    std::vector<char> result = {};
    for (auto& param : Parameters)
    {
        std::vector<char> var = param->GetOpcode();
        result.insert(result.end(), var.begin(), var.end());
    }
    return result;
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

std::vector<char> FlexASM::ProgramInstructionAddressParameter::GetOpcode()
{
    MemorySize opSize = OperationSize;

    if (opSize == msUndefined)
        opSize = msDWord;

    char infoByte = (char)OperandLeft;
    infoByte = (char)(infoByte << 2) + (char)Operation;
    infoByte = (char)(infoByte << 3) + (char)OperandRight;

    std::vector<char> result = { (char)opSize, infoByte };

    // TODO: rest of it lel

    return result;
}

std::string FlexASM::ProgramInstructionAddressParameter::GetPattern()
{
    return "addr";
}
