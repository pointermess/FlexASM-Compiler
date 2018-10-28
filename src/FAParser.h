#pragma once

#include <memory>
#include <string>

#include "FAProgram.h"
#include "FATokenizer.h"

namespace FlexASM
{
    class Parser
    {
    private:
        void Parse(FATokenizerPtr tokenizer, FAProgramPtr program);


        void ParseSection(FATokenizerPtr tokenizer, FAProgramPtr program);
        void ParseProgram(FATokenizerPtr tokenizer, FAProgramPtr program);
    public:
        Parser();
        ~Parser();

        std::shared_ptr<Program> ParseFile(const std::string filePath);
    };
}

