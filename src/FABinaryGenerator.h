#pragma once
#include <vector>
#include "FAProgram.h"

namespace FlexASM
{
    class FABinaryGenerator
    {
    public:
        FABinaryGenerator();
        ~FABinaryGenerator();

        const std::vector<uint8_t> CreateBinaryStream(ProgramPtr program);
    };


}