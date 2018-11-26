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
	while (tokenizer->IsInRange())
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
            throw ParserUnexpectedSectionException(token);
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

/*
 * ParseDataSectionItem
 *
 * Parses an item inside the data section.
 * It handles both, initialized and uninitialized, types of items.
 */
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


				// define variable to be parsed
				ProgramDataVariablePtr dataVariable;

				if (IsPseudoInstructionReservation(instruction))
				{
					// Parse uninitialized data (reservations)

					dataVariable = std::make_shared<ProgramDataVariable>(labelName, operationSize, 0);

					tokenizer->NextToken();
					token = tokenizer->GetCurrentToken();

					if (token.Type == ttConstDec)
					{
						int tokenValue = std::stoi(token.Value);

						if (tokenValue != 0)
						{
							dataVariable->Length = tokenValue;
							tokenizer->NextToken();
						}
						else
						{
							throw ParserUnexpectedTokenException(token);
						}
					}
				}
				else
				{
					// Parse initialized data

					std::vector<uint32_t> data;
					dataVariable = std::make_shared<ProgramDataInitializedVariable>(labelName, operationSize, data);
					
					// parse arguments
					bool reachedEnd = false;

					while (!reachedEnd)
					{
						tokenizer->NextToken();
						token = tokenizer->GetCurrentToken();


						// check argument and add if complient
						if (token.Type == ttConstDec)
						{
							int tokenValue = std::stoi(token.Value);
							
							data.push_back(tokenValue);
						}
						else if (token.Type == ttConstHex)
						{
							std::string hex;
							hex.assign(token.Value, 2, token.Value.length() - 2);
							int tokenValue = std::stoi(hex, nullptr, 16);


							data.push_back(tokenValue);
						}
						else if (token.Type == ttConstString)
						{
							std::string str;
							str.assign(token.Value, 1, token.Value.length() - 2);

							for (auto& c : str)
							{
								data.push_back((int)c);
							}
						}
						else
						{
							throw ParserUnexpectedTokenException(token);
						}

						// check if it was the lastt argument
						tokenizer->NextToken();
						token = tokenizer->GetCurrentToken();

						if (token.Type != ttOperandSplitter)
						{
							reachedEnd = true;
						}
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

