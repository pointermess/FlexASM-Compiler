#pragma once
#include <vector>
#include <string>
#include <set>
#include "Token.h"


class FATokenizer
{
public:
	FATokenizer();
	~FATokenizer();

	char StringChar;
	std::set<char> StopChars;
	std::set<char> IgnoreChars;
	std::set<std::string> KeepTogether;

	void Tokenize(string str, std::vector<FAToken> * output);
};

