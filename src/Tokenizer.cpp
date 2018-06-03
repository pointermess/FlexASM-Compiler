#include "stdafx.h"
#include "Tokenizer.h"
#include <iostream>
#include "Utilities.h"


FATokenizer::FATokenizer()
{
    // Initialize private variables
    FCurrentTokenIndex = 0;

    // specifying string char
    StringChar = 0x27;

    // specifying stop chars
    StopChars = { ' ', ',', '[', ']', '+', '-', 10, 13, StringChar };

    // specifying ignore chars
    IgnoreChars = { ' ', 10, 13, StringChar };
}


FATokenizer::~FATokenizer()
{
}

FAToken FATokenizer::GetCurrentToken()
{
    return Tokens[FCurrentTokenIndex];
}

FAToken FATokenizer::GetNextToken(int add)
{
    return Tokens[FCurrentTokenIndex + add];
}

int FATokenizer::GetTokenIndex()
{
    return FCurrentTokenIndex;
}

void FATokenizer::SetTokenIndex(int index)
{
    FCurrentTokenIndex = index;
}

void FATokenizer::NextToken()
{
    FCurrentTokenIndex += 1;
}

bool FATokenizer::IsInRange()
{
    return FCurrentTokenIndex < Tokens.size();
}

void FATokenizer::Tokenize(string str)
{
    unsigned int position = 0;
    unsigned int line = 0;

    unsigned int keepTogether = 0;

    bool inString = false;

    std::string buffer = "";


    // loop through provided string
    int currentCharIndex = -1;
    for (char& currentChar : str)
    {
        currentCharIndex += 1;

        // skip any chars from keeptogether
        if (keepTogether > 0)
        {
            keepTogether -= 1;
            continue;
        }


        // check if in string
        if (inString)
        {
            if (currentChar != StringChar) // check if string continues
            {
                buffer += currentChar;
            }
            else
            {
                buffer = StringChar + buffer + StringChar;

                Tokens.push_back({ buffer, position, line, FAToken::GetType(buffer) });

                buffer = "";
                inString = false;
            }

            continue;
        }

        position += 1;

        if (currentChar == 0xA)
        {
            position = 0;
            line += 1;
        }

        bool isCurrentCharInStopChars = in_set<char>(StopChars, currentChar);
        bool isCurrentCharInIgnoreChars = in_set<char>(IgnoreChars, currentChar);

        // if current char is in StopChars set
        if (!isCurrentCharInStopChars)
        {
            buffer += currentChar;
        }

        if (((isCurrentCharInStopChars) ||
            (currentCharIndex == str.length() - 1)) &&
            (buffer != ""))
        {
            Tokens.push_back({ buffer, position, line, FAToken::GetType(buffer) });
            buffer = "";
        }

        if (currentChar == StringChar)
            inString = true;

        // needs keep together stuff
    }
}

