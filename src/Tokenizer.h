#pragma once
#include <vector>
#include <string>
#include <set>
#include "Token.h"


class FATokenizer
{
private:
    int FCurrentTokenIndex;
public:
    FATokenizer();
    ~FATokenizer();

    char StringChar;
    std::set<char> StopChars;
    std::set<char> IgnoreChars;
    std::set<std::string> KeepTogether;

    std::vector<FAToken> Tokens;

    FAToken GetCurrentToken();
    FAToken GetNextToken(int add = 1);

    int GetTokenIndex();
    void SetTokenIndex(int index);

    void NextToken();
    bool IsInRange();

    void Tokenize(string str, std::vector<FAToken> * output);
};

