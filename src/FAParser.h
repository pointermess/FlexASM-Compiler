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
        void Parse(TokenizerPtr tokenizer, ProgramPtr program);

        void ParseSection(TokenizerPtr tokenizer, ProgramPtr program);

        void ParseDataSection(TokenizerPtr tokenizer, ProgramPtr program);
        void ParseDataSectionItem(TokenizerPtr tokenizer, ProgramPtr program);

		void ParseTextSection(TokenizerPtr tokenizer, ProgramPtr program);
		void ParseTextSectionSection(TokenizerPtr tokenizer, ProgramPtr program);
		void ParseTextSectionSectionItem(TokenizerPtr tokenizer, ProgramPtr program, ProgramSectionPtr programSection);



		void ParseProgram(TokenizerPtr tokenizer, ProgramPtr program);
    public:
        Parser();
        ~Parser();

        ProgramPtr ParseFile(const std::string filePath);
    };
}

