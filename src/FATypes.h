#pragma once

#include <string>
#include <vector>

namespace FlexASM
{

    enum MemorySize {
        msUndefined = 0,
        msByte = 1,
        msWord = 2,
        msDWord = 4
    };

    enum Register {
        farUnknown = -1,
        // General purpose registers

        // Least significant bytes 000000[00]
        // floor(n / 4) = 0
        farAL = 0, // mod 4 = 0
        farBL = 1, // mod 4 = 1
        farCL = 2, // mod 4 = 2
        farDL = 3, // mod 4 = 3

                   // Significant byte of lower byte-pair 0000[00]00
                   // floor(n / 4) = 1
                   farAH = 4, // mod 4 = 0
                   farBH = 5, // mod 4 = 1
                   farCH = 6, // mod 4 = 2
                   farDH = 7, // mod 4 = 3

                              // Two most significant bytes [0000]0000
                              // floor(n / 4) = 2
                              farAX = 8,  // mod 4 = 0
                              farBX = 9,  // mod 4 = 1
                              farCX = 10, // mod 4 = 2
                              farDX = 11, // mod 4 = 3

                                          // All four bytes [00000000]
                                          // floor(n / 4) = 3
                                          farEAX = 12, // mod 4 = 0
                                          farEBX = 13, // mod 4 = 1
                                          farECX = 14, // mod 4 = 2
                                          farEDX = 15, // mod 4 = 3

                                                       // Stack registers
                                                       // floor(n / 4) = 4
                                                       farESP = 16, // mod 4 = 0
                                                       farEBP = 17  // mod 4 = 1
    };

    enum Instruction {
        faiUnknown = 0,

        // Move instructions (0xA0 - 0xA5)
        faiMOV_REG_CONST = 0xa0,
        faiMOV_REG_REG = 0xa1,
        faiMOV_REG_ADDR = 0xa2,
        faiMOV_ADDR_CONST = 0xa3,
        faiMOV_ADDR_REG = 0xa4,
        faiMOV_ADDR_ADDR = 0xa5,

        // Stack instructions (0xAC - 0xAF)
        faiPUSH_CONST = 0xac,
        faiPUSH_REG = 0xad,
        faiPUSH_ADDR = 0xae,
        faiPOP_REG = 0xaf,

        // Flowcontrol instructions (0x70 - 0x94)
        faiJMP_LABEL = 0x70,
        faiJMP_ADDR = 0x71,
        faiJO_LABEL = 0x72,
        faiJO_ADDR = 0x73,
        faiJNO_LABEL = 0x74,
        faiJNO_ADDR = 0x75,
        faiJS_LABEL = 0x76,
        faiJS_ADDR = 0x77,
        faiJNS_LABEL = 0x78,
        faiJNS_ADDR = 0x79,
        faiJE_LABEL = 0x7a,
        faiJE_ADDR = 0x7b,
        faiJNE_LABEL = 0x7c,
        faiJNE_ADDR = 0x7d,
        faiJB_LABEL = 0x7e,
        faiJB_ADDR = 0x7f,
        faiJBE_LABEL = 0x80,
        faiJBE_ADDR = 0x81,
        faiJA_LABEL = 0x82,
        faiJA_ADDR = 0x83,
        faiJAE_LABEL = 0x84,
        faiJAE_ADDR = 0x85,
        faiJL_LABEL = 0x86,
        faiJL_ADDR = 0x87,
        faiJLE_LABEL = 0x88,
        faiJLE_ADDR = 0x89,
        faiJG_LABEL = 0x8a,
        faiJG_ADDR = 0x8b,
        faiJGE_LABEL = 0x8c,
        faiJGE_ADDR = 0x8d,
        faiJP_LABEL = 0x8e,
        faiJP_ADDR = 0x8f,
        faiJNP_LABEL = 0x90,
        faiJNP_ADDR = 0x91,

        faiCALL_LABEL = 0x92,
        faiCALL_ADDR = 0x93,
        faiRET = 0x94,

        // System Call instruction (0x98)
        faiINT_CONST = 0x98,

        // Math instructions (0xE0 - 0xEF)
        // Unsigned
        faiADD_REG_CONST = 0xe0,
        faiADD_REG_REG = 0xe1,
        faiSUB_REG_CONST = 0xe2,
        faiSUB_REG_REG = 0xe3,
        faiMUL_REG_CONST = 0xe4,
        faiMUL_REG_REG = 0xe5,
        faiDIV_REG_CONST = 0xe6,
        faiDIV_REG_REG = 0xe7,

        // signed
        faiIADD_REG_CONST = 0xe8,
        faiIADD_REG_REG = 0xe9,
        faiISUB_REG_CONST = 0xea,
        faiISUB_REG_REG = 0xeb,
        faiIMUL_REG_CONST = 0xec,
        faiIMUL_REG_REG = 0xed,
        faiIDIV_REG_CONST = 0xee,
        faiIDIV_REG_REG = 0xef,

        faiCMP_REG_CONST = 0xf0,
        faiCMP_REG_REG = 0xf1,

        faiDBG_REG = 0xfe,
        faiDBG_ADDR = 0xff,


        // pseude instructions (0x30 - 0x3f)
        fapiRESB = 0x30, // reserves an amount of bytes
        fapiRESW = 0x31, // reserves an amount of words
        fapiRESD = 0x32, // reserves an amount of double words

        fapiDB = 0x33, // defines a byte
        fapiDBA = 0x34, // defines an array of bytes
        fapiDW = 0x36, // defines a word
        fapiDWA = 0x37, // defines an array of words
        fapiDD = 0x39,  // defines a double word
        fapiDDA = 0x3A  // defines an array of double words
    };

    // Valid registers for the assembler
    struct ValidRegisterStruct
    {
        std::string Name;
        Register Register;
    };
    extern std::vector<ValidRegisterStruct> ValidRegisters;
    void InitValidRegisters();
    bool IsValidRegister(const std::string string);

    // Valid instructions for the assembler
    struct ValidInstructionStruct
    {
        std::string Pattern;
        Instruction Instruction;
    };
    extern std::vector<ValidInstructionStruct> ValidInstructions;
    void InitValidInstructions();
    bool IsValidInstruction(const std::string pattern);
    bool IsValidInstructionMnemonic(const std::string mnemonic);





}