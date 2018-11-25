#include "stdafx.h"

#include "FATypes.h"
using namespace FlexASM;

// Declare global variables
std::vector<FlexASM::ValidRegisterStruct> FlexASM::ValidRegisters;
std::vector<FlexASM::ValidInstructionStruct> FlexASM::ValidInstructions;
std::vector<FlexASM::ValidInstructionStruct> FlexASM::ValidPseudoInstructions;

/*
* InitValidRegisters
*
* Initializes all valid registers
*/
void FlexASM::InitValidRegisters()
{
    ValidRegisters.push_back({ "al", farAL });
    ValidRegisters.push_back({ "ah", farAH });
    ValidRegisters.push_back({ "ax", farAX });
    ValidRegisters.push_back({ "eax", farEAX });

    ValidRegisters.push_back({ "bl", farBL });
    ValidRegisters.push_back({ "bh", farBH });
    ValidRegisters.push_back({ "bx", farBX });
    ValidRegisters.push_back({ "ebx", farEBX });

    ValidRegisters.push_back({ "cl", farCL });
    ValidRegisters.push_back({ "ch", farCH });
    ValidRegisters.push_back({ "cx", farCX });
    ValidRegisters.push_back({ "ecx", farECX });

    ValidRegisters.push_back({ "dl", farDL });
    ValidRegisters.push_back({ "dh", farDH });
    ValidRegisters.push_back({ "dx", farDX });
    ValidRegisters.push_back({ "edx", farEDX });

    ValidRegisters.push_back({ "esp", farESP });
    ValidRegisters.push_back({ "ebp", farEBP });
}

/*
* IsValidRegister
*
* Checks if the passed string is a valid register
*/
bool FlexASM::IsValidRegister(const std::string string)
{
    for (auto& validRegister : ValidRegisters)
        if (validRegister.Name == string)
            return true;
    return false;
}

/*
* IsValidPseudoInstruction
*
* Checks if the pseudo instruction is valid
*/
bool FlexASM::IsValidPseudoInstruction(const std::string pattern)
{
    for (auto& validInstruction : ValidPseudoInstructions)
        if (validInstruction.Pattern == pattern)
            return true;
    return false;
}

/*
* PseudoInstructionOperationSize
*
* Returns the operation size of an pseudo instruction
*/
MemorySize FlexASM::PseudoInstructionOperationSize(Instruction pseudoInstruction)
{
	if ((char)pseudoInstruction >= 0x30 && (char)pseudoInstruction <= 0x34)
		return msByte;
	else if ((char)pseudoInstruction >= 0x35 && (char)pseudoInstruction <= 0x39)
		return msWord;
	else if ((char)pseudoInstruction >= 0x3A && (char)pseudoInstruction <= 0x3F)
		return msDWord;
	else
		return msUndefined;
}

/*
* FAInitValidInstructions
*
* Initializes
*/
void FlexASM::InitValidInstructions()
{
	//
    ValidInstructions.push_back({ "mov_const_const", faiMOV_REG_CONST });


	// Initialize all valid pseudo instuctions
    ValidPseudoInstructions.push_back({ "db", fapiDB });
    ValidPseudoInstructions.push_back({ "dw", fapiDW });
    ValidPseudoInstructions.push_back({ "dd", fapiDD });
    ValidPseudoInstructions.push_back({ "resb", fapiRESB });
    ValidPseudoInstructions.push_back({ "resw", fapiRESW });
    ValidPseudoInstructions.push_back({ "resd", fapiRESD });
}

/*
* IsValidInstruction
*
* Checks if the passed instruction pattern is valid.
*/
bool FlexASM::IsValidInstruction(const std::string pattern)
{
    for (auto& validInstruction : ValidInstructions)
        if (validInstruction.Pattern == pattern)
            return true;
    return false;
}

/*
* IsValidInstructionMnemonic
*
* Checks if the passed mnemonic is valid.
*/
bool FlexASM::IsValidInstructionMnemonic(const std::string mnemonic)
{
    for (auto& validInstruction : ValidInstructions)
        if (validInstruction.Pattern.substr(0, mnemonic.length() + 1) == mnemonic + "_")
            return true;
    return false;
}

bool FlexASM::IsPseudoInstructionReservation(Instruction pseudoInstruction)
{
	return (pseudoInstruction == fapiRESB) || (pseudoInstruction == fapiRESW) || (pseudoInstruction == fapiRESD);
}

Instruction FlexASM::PseudoInstruction(const std::string pseudoInstructionStr)
{
	for (auto& validInstruction : ValidPseudoInstructions)
		if (validInstruction.Pattern == pseudoInstructionStr)
			return validInstruction.Instruction;
	return faiUnknown;
}
