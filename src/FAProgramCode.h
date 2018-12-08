#pragma once
#include <string>
#include <vector>
#include <memory>

#include "FAProgramInstruction.h"

namespace FlexASM
{

    class ProgramSection
    {
    public:
        std::string Name;
        std::vector<std::shared_ptr<ProgramInstruction>> Instructions;
        std::vector<char> GetOpcode();
        int GetSize();
    };
    typedef std::shared_ptr<ProgramSection> ProgramSectionPtr;

    class ProgramCode
    {
    private:
    public:
        std::vector<ProgramSectionPtr> Sections;
        void AddSection(ProgramSectionPtr sections);
        ProgramSectionPtr FindSection(std::string& name);
        bool GetAddressOfSection(const std::string name, uint32_t& address);
        std::vector<char> GetOpcode();
        int GetSize();

    };
    typedef std::shared_ptr<ProgramCode> ProgramCodePtr;
}