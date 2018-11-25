#include "stdafx.h"

#include "FAParser.h"
#include "FATokenizer.h"
#include "FAPreprocessor.h"
#include "FATypes.h"
#include "FAExceptions.h"
#include "FAProgramData.h"

#include <iostream>

using namespace FlexASM;

void Parser::Parse(TokenizerPtr tokenizer, ProgramPtr program)
{
    FAToken token = tokenizer->GetCurrentToken();

    if (token.Type == ttSectionKeyword)
    {
        ParseSection(tokenizer, program);
    }
    else
    {
        throw ParserUnexpectedTokenException(token, "section");
    }
}

void Parser::ParseSection(TokenizerPtr tokenizer, ProgramPtr program)
{
    FAToken token = tokenizer->GetCurrentToken();

    if (token.Type == ttSectionKeyword)
    {
        tokenizer->NextToken();
        token = tokenizer->GetCurrentToken();

        if (token.Value == ".data")
        {
            tokenizer->NextToken();
            ParseDataSection(tokenizer, program);
        }
        else if (token.Value == ".text")
        {
            tokenizer->NextToken();
        }
        else
        {
            throw ParserUnexpectedTokenException(token);
        }
    }
}

void Parser::ParseProgram(TokenizerPtr tokenizer, ProgramPtr program)
{
}

void FlexASM::Parser::ParseDataSection(TokenizerPtr tokenizer, ProgramPtr program)
{
    while (tokenizer->GetCurrentToken().Type == ttLabel)
    {
        ParseDataSectionItem(tokenizer, program);
    }
}

void FlexASM::Parser::ParseDataSectionItem(TokenizerPtr tokenizer, ProgramPtr program)
{
    FAToken token = tokenizer->GetCurrentToken();

    if (token.Type == ttLabel)
    {
        // extract label name and check if it already exists
        std::string labelName;
        labelName.assign(token.Value, 0, token.Value.length() - 1);

        uint32_t address = 0;
        if (!program->Data->GetAddressOfVariable(labelName, address))
        {
            // parse instruction
            tokenizer->NextToken();
            token = tokenizer->GetCurrentToken();

            if (IsValidPseudoInstruction(token.Value))
            {
				Instruction instruction = PseudoInstruction(token.Value);
				MemorySize operationSize = PseudoInstructionOperationSize(instruction);

                std::vector<uint32_t> data;

				// define variable to be parsed
                ProgramDataVariablePtr dataVariable;

				if (IsPseudoInstructionReservation(instruction))
					dataVariable = std::make_shared<ProgramDataVariable>(labelName, operationSize, 0);
				else
					dataVariable = std::make_shared<ProgramDataInitializedVariable>(labelName, operationSize, 0);

                // parse arguments
                bool reachedEnd = false;

                while (!reachedEnd)
                {
                    tokenizer->NextToken();
                    token = tokenizer->GetCurrentToken();

					if (token.Type == ttConstDec)
					{

					}
					if (token.Type == tt)
					else
					{
						throw ParserUnexpectedTokenException(token);
					}
                }

                program->Data->Variables.push_back(dataVariable);
            }
            else
            {
                throw ParserInvalidPseudoInstructionException(token, token.Value);
            }
        }
        else
        {
            throw ParserIdentifierRedefinedException(token, labelName);
        }
    }
}


Parser::Parser()
{
}


Parser::~Parser()
{
}


/*
 * ParseFile
 *
 * Public function is used to parse FlexASM code in a specific file using its path.
 * This function calls private functions to generate an output representing the parsed program.
 */
ProgramPtr Parser::ParseFile(const std::string filePath)
{
    // Preprocess file
    std::shared_ptr<Preprocessor> preprocessor = std::make_unique<Preprocessor>();
    std::string sourceCode = preprocessor->Preprocess(filePath);

    // Tokenize preprocessed source code
    std::shared_ptr<Tokenizer> tokenizer = std::make_shared<Tokenizer>();
    tokenizer->Tokenize(sourceCode);

    // Parse tokens
    std::shared_ptr<Program> result = std::make_shared<Program>();

    try
    {
        Parse(tokenizer, result);
    }
    catch (Exception& e)
    {
        std::cout << e.GetMessage() << std::endl;
    }

    return result;
}

