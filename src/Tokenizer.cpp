#include "stdafx.h"
#include "Tokenizer.h"
#include <iostream>


FATokenizer::FATokenizer()
{
	// specifying string char
	StringChar = '\'';

	// specifying stop chars
	StopChars = { ' ', ',', '[', ']', '+', '-', 10, 13 };

	// specifying ignore chars
	IgnoreChars = { ' ', 10, 13 };
}


FATokenizer::~FATokenizer()
{
}

void FATokenizer::Tokenize(string str, vector<FAToken>* output)
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

		// check if keeptogether (?)
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

				output->push_back({ buffer, position, line, FAToken::GetType(buffer) });

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

		bool isCurrentCharInStopChars = StopChars.find(currentChar) != StopChars.end();
		bool isCurrentCharInIgnoreChars = IgnoreChars.find(currentChar) != IgnoreChars.end();

		// if current char is in StopChars set
		if (!isCurrentCharInStopChars)
		{
			buffer += currentChar;
		}

		if ((isCurrentCharInStopChars) ||
			(currentCharIndex == str.length() - 1) ||
			(buffer != ""))
		{
			output->push_back({ buffer, position, line, FAToken::GetType(buffer) });
			buffer = "";
		}

		if (currentChar == StringChar)
			inString = true;
	}
}

