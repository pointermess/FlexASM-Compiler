#include "stdafx.h"
#include "Preprocessor.h"
#include <fstream>
#include <streambuf>
#include <memory>
#include <iostream>
#include "Tokenizer.h"
#include "Utilities.h"


FAPreprocessor::FAPreprocessor()
{
    CommentChar = ';';
}


FAPreprocessor::~FAPreprocessor()
{
}

std::string FAPreprocessor::RemoveComments(std::string input)
{
    std::string result = "";

    bool inComment = false;
    for (char& currentChar : input)
    {
        if (!inComment)
        {
            if (currentChar != CommentChar)
            {
                result += currentChar;
                continue;
            }
            else
            {
                inComment = true;
                continue;
            }
        }

        if (currentChar == 10)
            inComment = false;
    }

    return result;
}

std::string FAPreprocessor::IncludeFiles(std::string input, std::string filePath)
{
    return std::string();
}



std::string FAPreprocessor::Preprocess(std::string fileName)
{
    // prepare result
    std::string result = "";

    // load file into temp string
    std::string temp = read_file(fileName);
    temp = RemoveComments(temp);

    // tokenize
    std::unique_ptr<FATokenizer> tokenizer = std::make_unique<FATokenizer>();
    std::vector<FAToken> tokens;
    tokenizer->Tokenize(temp, &tokens);

    std::string includeStrigs = "";
    // parse through tokens and look for things to preprocess
    while (tokenizer->IsInRange())
    {
        FAToken token = tokenizer->GetCurrentToken();
        if (token.Type == ttCompilerCommand)
        {
            if (token.Value == "%include")
            {
                FAToken nextToken = tokenizer->GetNextToken();

                if (nextToken.Type == ttConstString)
                {
                    std::string filePath = nextToken.Value.substr(1, nextToken.Value.length() - 2);
                    std::string fileSource = Preprocess(filePath);

                    includeStrigs += fileSource;
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
    result += includeStrigs;
    return result;
}
