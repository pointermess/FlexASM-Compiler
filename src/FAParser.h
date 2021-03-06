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
        void PopulateLookupTable(ProgramPtr program);

        void ParseSection(TokenizerPtr tokenizer, ProgramPtr program);

        void ParseDataSection(TokenizerPtr tokenizer, ProgramPtr program);
        void ParseDataSectionItem(TokenizerPtr tokenizer, ProgramPtr program);

		void ParseTextSection(TokenizerPtr tokenizer, ProgramPtr program);
		void ParseTextSectionSection(TokenizerPtr tokenizer, ProgramPtr program);
        void ParseTextSectionSectionItem(TokenizerPtr tokenizer, ProgramPtr program,
            ProgramSectionPtr programSection);
        void ParseTextSectionSectionItemConst(TokenizerPtr tokenizer, ProgramPtr program,
            ProgramInstructionPtr programInstruction);
        void ParseTextSectionSectionItemRegister(TokenizerPtr tokenizer, ProgramPtr program,
            ProgramInstructionPtr programInstruction);
        void ParseTextSectionSectionItemAddress(TokenizerPtr tokenizer, ProgramPtr program,
            ProgramInstructionPtr programInstruction);
        void ParseTextSectionSectionItemDataAlias(TokenizerPtr tokenizer, ProgramPtr program,
            ProgramInstructionPtr programInstruction);
        void ParseTextSectionSectionItemLabelAlias(TokenizerPtr tokenizer, ProgramPtr program,
            ProgramInstructionPtr programInstruction);



		void ParseProgram(TokenizerPtr tokenizer, ProgramPtr program);
    public:
        Parser();
        ~Parser();

        ProgramPtr ParseFile(const std::string filePath);
    };
}

