#pragma once
#include <vector>
#include <memory>
#include <string>
#include <set>
#include "FAToken.h"

namespace FlexASM
{
    class Tokenizer
    {
    private:
        int FCurrentTokenIndex;
    public:
        Tokenizer();
        ~Tokenizer();

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

        void Tokenize(std::string str);
    };
    typedef std::shared_ptr<Tokenizer> FATokenizerPtr;


}
