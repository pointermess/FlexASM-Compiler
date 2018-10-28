#pragma once
#include <vector>
#include <memory>

namespace FlexASM
{

    class FAProgramInstructionParameter
    {
        virtual std::vector<char> GetOpcode() = 0;
    };
    typedef  std::vector<std::shared_ptr<FAProgramInstructionParameter>> FAProgramInstructionParamterVector;

    class FAProgramInstructionConstIntParameter : public FAProgramInstructionParameter
    {

    };

    class FAProgramInstructionConstStrParameter : public FAProgramInstructionParameter
    {

    };

    class FAProgramInstruction
    {
    public:
        std::string Instruction;
        FAProgramInstructionParamterVector Parameters;

        std::vector<char> GetOpcode();
    };
    typedef  std::vector<std::shared_ptr<FAProgramInstruction>> FAProgramInstructionVector;
}
