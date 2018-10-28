#include "stdafx.h"

#include "FAParser.h"
#include "FATokenizer.h"
#include "FAPreprocessor.h"
#include "FATypes.h"
#include "FAExceptions.h"

#include <iostream>

void FlexASM::Parser::Parse(FATokenizerPtr tokenizer, FAProgramPtr program)
{
    FAToken token = tokenizer->GetCurrentToken();

    if (token.Type == ttSectionKeyword)
    {
        ParseSection(tokenizer, program);
    }
}

void FlexASM::Parser::ParseSection(FATokenizerPtr tokenizer, FAProgramPtr program)
{
    FAToken token = tokenizer->GetCurrentToken();

    if (token.Type == ttSectionKeyword)
    {
        tokenizer->NextToken();
        token = tokenizer->GetCurrentToken();

        if (token.Value == ".data")
        {
            tokenizer->NextToken();
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

void FlexASM::Parser::ParseProgram(FATokenizerPtr tokenizer, FAProgramPtr program)
{
    try
    {
        while (tokenizer->IsInRange())
        {
            FAToken token = tokenizer->GetCurrentToken();

            if (token.Type == ttSectionKeyword)
            {
                tokenizer->NextToken();
                token = tokenizer->GetCurrentToken();

                if (token.Value == ".data")
                {
                    tokenizer->NextToken();
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
            else if (token.Type == ttAlias)
            {

            }
        }
    }
    catch (ParserUnexpectedTokenException& e)
    {
        std::cout << e.GetMessage() << std::endl;
    }
}

FlexASM::Parser::Parser()
{
}


FlexASM::Parser::~Parser()
{
}



std::shared_ptr<FlexASM::Program> FlexASM::Parser::ParseFile(const std::string filePath)
{
    // Preprocess file
    std::shared_ptr<Preprocessor> preprocessor = std::make_unique<Preprocessor>();
    std::string sourceCode = preprocessor->Preprocess(filePath);

    // Tokenize preprocessed source code
    std::shared_ptr<Tokenizer> tokenizer = std::make_shared<Tokenizer>();
    tokenizer->Tokenize(sourceCode);

    // Parse tokens
    std::shared_ptr<Program> result = std::make_shared<Program>();

    

    /* 
    
    Print all tokens and its types for debugging purposes

    */
    for (FAToken & token : tokenizer->Tokens)
    {
        std::cout << token.Type << ": " << token.Value << std::endl;
    }

    try
    {

    }
    catch (ParserUnexpectedTokenException& e)
    {
        std::cout << e.GetMessage() << std::endl;
    }


    return result;
}

