#include "stdafx.h"
#include "FAProgramInstruction.h"
#include "FAProgram.h"

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

std::vector<char> FlexASM:: ProgramInstructionRegisterParameter::GetOpcode()
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

int FlexASM::ProgramInstruction::GetSize()
{
    return GetOpcode().size();
}

std::vector<char> FlexASM::ProgramInstruction::GetOpcode()
{
    std::vector<char> result = { (char)InstructionEnum };
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

    if (OperandLeft == vtConstantValue)
    {
        result.push_back((char)(OperandLeftConstant >> 24));
        result.push_back((char)(OperandLeftConstant >> 16));
        result.push_back((char)(OperandLeftConstant >> 8));
        result.push_back((char)(OperandLeftConstant));
    } 
    else if (OperandLeft == vtRegister)
    {
        result.push_back((char)(OperandLeftRegister));
    }

    if (OperandRight != vtUndefined)
    {
        if (OperandRight == vtConstantValue)
        {
            result.push_back((char)(OperandRightConstant >> 24));
            result.push_back((char)(OperandRightConstant >> 16));
            result.push_back((char)(OperandRightConstant >> 8));
            result.push_back((char)(OperandRightConstant));
        }
        else if (OperandRight == vtRegister)
        {
            result.push_back((char)(OperandRightRegister));
        }
    }

    return result;
}

std::string FlexASM::ProgramInstructionAddressParameter::GetPattern()
{
    return "addr";
}

int FlexASM::ProgramInstructionParameterInterface::GetSize()
{
    return GetOpcode().size();
}


std::vector<char> FlexASM::ProgramInstructionAliasParameter::GetOpcode()
{
    unsigned int addr;
    if (LookupTable->Find(Alias, addr))
    {
        return { (char)4, (char)(addr >> 24), (char)(addr >> 16), (char)(addr >> 8), (char)addr };
    }
    else
    {
        return { 0,0,0,0,0 };
    }
}

std::string FlexASM::ProgramInstructionAliasParameter::GetPattern()
{
    return "const";
}
