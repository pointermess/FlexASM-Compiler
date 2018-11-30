#pragma once
#include <vector>
#include <memory>
#include "FATypes.h"

using namespace FlexASM;

namespace FlexASM
{

    class ProgramInstructionParameterInterface
    {
    public:
        MemorySize OperationSize;
        virtual std::vector<char> GetOpcode() = 0;
        virtual std::string GetPattern() = 0;
    };
    typedef  std::shared_ptr<ProgramInstructionParameterInterface> ProgramInstructionParameterInterfacePtr;

    class ProgramInstructionConstIntParameter : public ProgramInstructionParameterInterface
    {
    public:
        unsigned int Value;
        std::vector<char> GetOpcode() override;
        std::string GetPattern();
    };
    typedef std::shared_ptr< ProgramInstructionConstIntParameter> ProgramInstructionConstIntParameterPtr;

    class ProgramInstructionConstStrParameter : public ProgramInstructionParameterInterface
    {

    };

    class ProgramInstructionRegisterParameter : public ProgramInstructionParameterInterface
    {
    public:
        Register Value;
        std::vector<char> GetOpcode() override;
        std::string GetPattern();
    };
    typedef std::shared_ptr< ProgramInstructionRegisterParameter> ProgramInstructionRegisterParameterPtr;


    class ProgramInstructionAddressParameter : public ProgramInstructionParameterInterface
    {
    public:
        Register OperandLeftRegister;
        uint32_t OperandLeftConstant;

        Register OperandRightRegister;
        uint32_t OperandRightConstant;

        OperandType OperandLeft;
        OperandType OperandRight;
        OperationType Operation;

        std::vector<char> GetOpcode() override;
        std::string GetPattern();
    };
    typedef std::shared_ptr< ProgramInstructionAddressParameter> ProgramInstructionAddressParameterPtr;


    class ProgramInstruction
    {
    public:
        std::string InstructionStr;
        std::vector<ProgramInstructionParameterInterfacePtr> Parameters;

        std::vector<char> GetOpcode();
        const std::string BuildPattern();
    };
    typedef  std::shared_ptr<ProgramInstruction> ProgramInstructionPtr;
}
