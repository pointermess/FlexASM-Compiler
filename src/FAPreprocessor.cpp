#include "stdafx.h"
#include <fstream>
#include <streambuf>
#include <memory>
#include <iostream>

#include "Utilities.h"

#include "FATokenizer.h"
#include "FAPreprocessor.h"


FlexASM::Preprocessor::Preprocessor()
{
    CommentChar = ';';
    StringChar = 0x27;
}


FlexASM::Preprocessor::~Preprocessor()
{
}

const std::string FlexASM::Preprocessor::RemoveComments(std::string input)
{
    std::string result = "";

    bool inComment = false;
    bool inString = false;
    for (char& currentChar : input)
    {
        if (!inString && currentChar == StringChar)
        {
            inString = true;
        }
        else
        {
            if (inString && currentChar == StringChar)
            {
                inString = false;
            }
        }

        if (!inComment)
        {
            if (currentChar == CommentChar && !inString)
            {
                inComment = true;
                continue;
            }
            else
            {
                result += currentChar;
                continue;
            }
        }

        if (currentChar == 10)
            inComment = false;
    }

    return result;
}

const std::string FlexASM::Preprocessor::IncludeFiles(const std::string input, const std::string filePath)
{
    return std::string();
}


///

const std::string FlexASM::Preprocessor::Preprocess(const std::string fileName)
{
    // prepare result
    std::string result = "";

    // load file into temp string
    std::string temp = read_file(fileName);

    // preprocess (remove) comments
    temp = RemoveComments(temp);

    // tokenize
    std::unique_ptr<Tokenizer> tokenizer = std::make_unique<Tokenizer>();
    tokenizer->Tokenize(temp);

    std::string includeStrings = "";
    // parse through tokens and look for things to preprocess
    while (tokenizer->IsInRange())
    {
        Token token = tokenizer->GetCurrentToken();
        if (token.Type == ttCompilerCommand)
        {
            if (token.Value == "%include")
            {
                Token nextToken = tokenizer->GetNextToken();

                if (nextToken.Type == ttConstString)
                {
                    std::string filePath = nextToken.Value.substr(1, nextToken.Value.length() - 2);
                    std::string fileSource = Preprocess(filePath);

                    includeStrings += fileSource;
                }
                tokenizer->NextToken();
            }
        }
        else
        {
            result += tokenizer->GetCurrentToken().Value + ' ';
        }
        tokenizer->NextToken();
    }
    result += includeStrings;
    return result;
}
