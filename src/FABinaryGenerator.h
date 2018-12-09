#pragma once
#include <vector>
#include <string>
#include "FAProgram.h"
#include <fstream>

namespace FlexASM
{
    class FABinaryGenerator
    {
    public:
        FABinaryGenerator();
        ~FABinaryGenerator();

        const std::vector<char> CreateBinaryStream(ProgramPtr program);
        void SaveToFile(ProgramPtr program, const std::string filePath);
    };


}