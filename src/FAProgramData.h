#pragma once

#include <string>
#include <vector>
#include <memory>

#include "FAProgramInstruction.h"
#include "FATypes.h"

namespace FlexASM
{
    class ProgramDataVariableInterface
    {
    public:
        std::string Name;
        MemorySize Size;
        virtual uint32_t GetLength() = 0;
        virtual std::vector<uint8_t> GetOpcode() = 0;
    };
    typedef std::shared_ptr<ProgramDataVariableInterface> ProgramDataVariableInterfacePtr;
    /*
    * ProgramDataInitializedVariable
    * A class used to reserve uninitialized space in memory.
    *
    * Can return the executable opcode.
    */
    class ProgramDataVariable : public ProgramDataVariableInterface
    {
    private:
    public:
        uint32_t Length;


        ProgramDataVariable(const std::string name, MemorySize size, uint32_t length = 1);

        virtual uint32_t GetLength() override;
        std::vector<uint8_t> GetOpcode() override;
    };
    typedef std::shared_ptr<ProgramDataVariable> ProgramDataVariablePtr;

    /*
    * ProgramDataInitializedVariable
    * A class which holds initialized data in a vector array to be stored in memory.
    *
    * Can return the executable opcode.
    */
    class ProgramDataInitializedVariable : public ProgramDataVariableInterface
    {
    public:
        std::vector<uint32_t> Data;
        ProgramDataInitializedVariable(const std::string name, MemorySize size, std::vector<uint32_t>& data);

        uint32_t GetLength() override;
        std::vector<uint8_t> GetOpcode() override;
    };
    typedef std::shared_ptr<ProgramDataInitializedVariable> ProgramDataInitializedVariablePtr;

    class ProgramData
    {
    public:
        std::vector<ProgramDataVariableInterfacePtr> Variables;
        bool GetAddressOfVariable(const std::string name, uint32_t& address);
        std::vector<uint8_t> GetOpcode();
    };
    typedef std::shared_ptr<ProgramData> ProgramDataPtr;

}
