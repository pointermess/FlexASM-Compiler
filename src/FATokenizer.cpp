#include "stdafx.h"
#include <iostream>

#include "Utilities.h"

#include "FATokenizer.h"


FlexASM::Tokenizer::Tokenizer()
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


FlexASM::Tokenizer::~Tokenizer()
{
}

FlexASM::FAToken FlexASM::Tokenizer::GetCurrentToken()
{
    return Tokens[FCurrentTokenIndex];
}

FlexASM::FAToken FlexASM::Tokenizer::GetNextToken(int add)
{
    return Tokens[FCurrentTokenIndex + add];
}

int FlexASM::Tokenizer::GetTokenIndex()
{
    return FCurrentTokenIndex;
}

void FlexASM::Tokenizer::SetTokenIndex(int index)
{
    FCurrentTokenIndex = index;
}

void FlexASM::Tokenizer::NextToken()
{
    FCurrentTokenIndex += 1;
}

bool FlexASM::Tokenizer::IsInRange()
{
    return FCurrentTokenIndex < Tokens.size();
}

void FlexASM::Tokenizer::Tokenize(std::string str)
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

        if (isCurrentCharInStopChars && !isCurrentCharInIgnoreChars)
        {
            /* Needs still do be ported right here*/

            /* Delphi Code: (Author: Milos Stanojevic) */
            /*
            
            if LCurrentChar in FKeepTogetherChars then
            begin
                for c := 0 to KeepTogether.Count-1 do
                begin
                    LKeepBuffer := Copy(AString, LCurrentCharIndex, Length(KeepTogether[c]));

                    if LKeepBuffer = KeepTogether[c] then
                    begin
                        ATokens.Add(TFPFlexPascalToken.Create());
                        ATokens.Last.Value := LKeepBuffer;
                        ATokens.Last.Position :=  LPos - Length(LKeepBuffer);
                        ATokens.Last.Line := LLine;
                        ATokens.Last.TokenType := FlexPascalTokenType(LKeepBuffer);

                        LKeepTogether := Length(KeepTogether[c])-1;
                    end;
                end;
            end;

            */
            
            if (keepTogether == 0)
            {
                Tokens.push_back({ std::string(1, currentChar), position, line, FAToken::GetType(std::string(1, currentChar)) });
            }
        }
    }
}

