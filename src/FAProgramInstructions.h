#pragma once
#include <vector>
#include <memory>

class FAProgramInstructionParameter
{
public:
    virtual std::vector<char> GetOpcode() = 0;
};

class FAProgramInstructionConstIntParameter : public FAProgramInstructionParameter
{
public:
    std::vector<char> GetOpcode();
    void test();
};

class FAProgramInstructionConstStrParameter : public FAProgramInstructionParameter
{

};

class FAProgramInstruction
{
public:
    std::string Instruction;
    std::vector<std::shared_ptr<FAProgramInstructionParameter>> Parameters;

    std::vector<char> GetOpcode();
};
