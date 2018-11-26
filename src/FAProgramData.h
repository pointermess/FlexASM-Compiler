#pragma once

#include <string>
#include <vector>
#include <memory>

#include "FAProgramInstruction.h"
#include "FATypes.h"

namespace FlexASM
{
    /*
    * ProgramDataInitializedVariable
    * A class used to reserve uninitialized space in memory.
    *
    * Can return the executable opcode.
    */
    class ProgramDataVariable
    {
    private:
    public:
		std::string Name;
		MemorySize Size;
		uint32_t Length;

		uint32_t GetLength();

        ProgramDataVariable(const std::string name, MemorySize size, uint32_t length = 1);

        std::vector<uint8_t> GetOpcode();
    };
    typedef std::shared_ptr<ProgramDataVariable> ProgramDataVariablePtr;

    /*
    * ProgramDataInitializedVariable
    * A class which holds initialized data in a vector array to be stored in memory.
    *
    * Can return the executable opcode.
    */
    class ProgramDataInitializedVariable : public ProgramDataVariable
    {
    public:
        std::vector<uint32_t> Data;
        ProgramDataInitializedVariable(const std::string name, MemorySize size, std::vector<uint32_t>& data);

		uint32_t GetLength();
        std::vector<uint8_t> GetOpcode();
    };
    typedef std::shared_ptr<ProgramDataInitializedVariable> ProgramDataInitializedVariablePtr;

    class ProgramData
    {
    public:
        std::vector<ProgramDataVariablePtr> Variables;
        bool GetAddressOfVariable(const std::string name, uint32_t& address);
    };
    typedef std::shared_ptr<ProgramData> ProgramDataPtr;

}
