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

        std::vector<Token> Tokens;

        Token GetCurrentToken();
        Token GetNextToken(int add = 1);

        int GetTokenIndex();
        void SetTokenIndex(int index);

		void NextToken();
		void PreviousToken();
        bool IsInRange();

        void Tokenize(std::string str);
    };
    typedef std::shared_ptr<Tokenizer> TokenizerPtr;


}
