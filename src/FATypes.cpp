#include "stdafx.h"

#include "FATypes.h"
#include "Utilities.h"
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
    ValidInstructions.push_back({ "mov_reg_const", faiMOV_REG_CONST });
    ValidInstructions.push_back({ "mov_reg_reg", faiMOV_REG_REG });
    ValidInstructions.push_back({ "mov_reg_addr", faiMOV_REG_ADDR });
    ValidInstructions.push_back({ "mov_addr_const", });
    ValidInstructions.push_back({ "mov_addr_const", faiMOV_ADDR_CONST });
    ValidInstructions.push_back({ "mov_addr_reg", faiMOV_ADDR_REG });
    ValidInstructions.push_back({ "mov_addr_addr", faiMOV_ADDR_ADDR });

    ValidInstructions.push_back({ "push_const", faiPUSH_CONST });
    ValidInstructions.push_back({ "push_reg", faiPUSH_REG });
    ValidInstructions.push_back({ "push_addr", faiPUSH_ADDR });
    ValidInstructions.push_back({ "pop_reg", faiPOP_REG });

    ValidInstructions.push_back({ "jmp_const", faiJMP_LABEL });
    ValidInstructions.push_back({ "jmp_addr", faiJMP_ADDR });
    ValidInstructions.push_back({ "jo_const", faiJO_LABEL });
    ValidInstructions.push_back({ "jo_addr", faiJO_ADDR });
    ValidInstructions.push_back({ "jno_const", faiJNO_LABEL });
    ValidInstructions.push_back({ "jno_addr", faiJNO_ADDR });
    ValidInstructions.push_back({ "js_const", faiJS_LABEL });
    ValidInstructions.push_back({ "js_addr", faiJS_ADDR });
    ValidInstructions.push_back({ "jns_const", faiJNS_LABEL });
    ValidInstructions.push_back({ "jns_addr", faiJNS_ADDR });
    ValidInstructions.push_back({ "je_const", faiJE_LABEL });
    ValidInstructions.push_back({ "je_addr", faiJE_ADDR });
    ValidInstructions.push_back({ "jne_const", faiJNE_LABEL });
    ValidInstructions.push_back({ "jne_addr", faiJNE_ADDR });
    ValidInstructions.push_back({ "jb_const", faiJB_LABEL });
    ValidInstructions.push_back({ "jb_addr", faiJB_ADDR });
    ValidInstructions.push_back({ "jbe_const", faiJBE_LABEL });
    ValidInstructions.push_back({ "jbe_addr", faiJBE_ADDR });
    ValidInstructions.push_back({ "ja_const", faiJA_LABEL });
    ValidInstructions.push_back({ "ja_addr", faiJA_ADDR });
    ValidInstructions.push_back({ "jae_const", faiJAE_LABEL });
    ValidInstructions.push_back({ "jae_addr", faiJAE_ADDR });
    ValidInstructions.push_back({ "jl_const", faiJL_LABEL });
    ValidInstructions.push_back({ "jl_addr", faiJL_ADDR });
    ValidInstructions.push_back({ "jle_const", faiJLE_LABEL });
    ValidInstructions.push_back({ "jle_addr", faiJLE_ADDR });
    ValidInstructions.push_back({ "jg_const", faiJG_LABEL });
    ValidInstructions.push_back({ "jg_addr", faiJG_ADDR });
    ValidInstructions.push_back({ "jge_const", faiJGE_LABEL });
    ValidInstructions.push_back({ "jge_addr", faiJGE_ADDR });
    ValidInstructions.push_back({ "jp_const", faiJP_LABEL });
    ValidInstructions.push_back({ "jp_addr", faiJP_ADDR });
    ValidInstructions.push_back({ "jnp_const", faiJNP_LABEL });
    ValidInstructions.push_back({ "jnp_addr", faiJNP_ADDR });

    ValidInstructions.push_back({ "call_const", faiCALL_LABEL });
    ValidInstructions.push_back({ "call_addr", faiCALL_ADDR });
    ValidInstructions.push_back({ "ret", faiRET });

    ValidInstructions.push_back({ "int_const", faiINT_CONST });

    ValidInstructions.push_back({ "add_reg_const", faiADD_REG_CONST });
    ValidInstructions.push_back({ "add_reg_reg", faiADD_REG_REG });
    ValidInstructions.push_back({ "sub_reg_const", faiSUB_REG_CONST });
    ValidInstructions.push_back({ "sub_reg_reg", faiSUB_REG_REG });
    ValidInstructions.push_back({ "mul_reg_const", faiMUL_REG_CONST });
    ValidInstructions.push_back({ "mul_reg_reg", faiMUL_REG_REG });
    ValidInstructions.push_back({ "div_reg_const", faiDIV_REG_CONST });
    ValidInstructions.push_back({ "div_reg_reg", faiDIV_REG_REG });
    ValidInstructions.push_back({ "iadd_reg_const", faiIADD_REG_CONST });
    ValidInstructions.push_back({ "iadd_reg_reg", faiIADD_REG_REG });
    ValidInstructions.push_back({ "isub_reg_const", faiISUB_REG_CONST });
    ValidInstructions.push_back({ "isub_reg_reg", faiISUB_REG_REG });
    ValidInstructions.push_back({ "imul_reg_const", faiIMUL_REG_CONST });
    ValidInstructions.push_back({ "imul_reg_reg", faiIMUL_REG_REG });
    ValidInstructions.push_back({ "idiv_reg_const", faiIDIV_REG_CONST });
    ValidInstructions.push_back({ "idiv_reg_reg", faiIDIV_REG_REG });

    ValidInstructions.push_back({ "cmp_reg_const", faiCMP_REG_CONST });
    ValidInstructions.push_back({ "cmp_reg_reg", faiCMP_REG_REG });

    ValidInstructions.push_back({ "dbg_reg", faiDBG_REG });
    ValidInstructions.push_back({ "dbg_addr", faiDBG_ADDR });


    // Initialize all valid pseudo instuctions
    ValidPseudoInstructions.push_back({ "db", fapiDB });
    ValidPseudoInstructions.push_back({ "dw", fapiDW });
    ValidPseudoInstructions.push_back({ "dd", fapiDD });

    ValidPseudoInstructions.push_back({ "resb", fapiRESB });
    ValidPseudoInstructions.push_back({ "resw", fapiRESW });
    ValidPseudoInstructions.push_back({ "resd", fapiRESD });
}

MemorySize FlexASM::ParseMemorySize(const std::string string)
{
    std::string lower = string;
    str_to_lower(lower);

    if (lower == "byte") return msByte;
    if (lower == "word") return msWord;
    if (lower == "dword") return msDWord;
}

Register FlexASM::ParseRegister(const std::string string)
{
    std::string lower = string;
    str_to_lower(lower);

    for (auto& reg : ValidRegisters)
    {
        if (lower == reg.Name)
            return reg.Register;
    }
    return farUnknown;
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

Instruction FlexASM::GetInstructionByPattern(const std::string pattern)
{
    for (auto& validInstruction : ValidInstructions)
        if (validInstruction.Pattern == pattern)
            return validInstruction.Instruction;
    return faiUnknown;
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
