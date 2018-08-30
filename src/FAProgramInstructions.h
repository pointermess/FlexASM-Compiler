#pragma once
#include <vector>
#include <memory>

class FAProgramInstructionParameter
{
    virtual std::vector<char> GetOpcode() = 0;
};
typedef  std::vector<std::unique_ptr<FAProgramInstructionParameter>> FAProgramInstructionParamterVector;

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
