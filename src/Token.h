#pragma once

#include <string>
using namespace std;

enum FATokenType
{
	ttUnknown,
	ttInstruction,
	ttConstString,
	ttConstDec,
	ttConstHex,
	ttRegister,
	ttAddressOpener,
	ttAddressCloser,
	ttAddressAddition,
	ttAddressSubtraction,
	ttOperandSplitter,
	ttSize,
	ttLabel,
	ttJumpToLabel,
	ttAlias
};

struct FAToken
{
public:
	std::string Value;
	int Position;
	int Line;
	FATokenType Type;

	static FATokenType GetType(string TokenValue);
};

