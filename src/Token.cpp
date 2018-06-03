#include "stdafx.h"
#include "Token.h"
#include <algorithm>
#include "Utilities.h"

FATokenType FAToken::GetType(string TokenValue)
{
    string token = TokenValue;

    // set token to lowercase
    str_to_lower(token);

    if (token[token.length() - 1] == ':')
        return ttLabel;
    else if (token == "byte" || token == "word" || token == "dword")
        return ttSize;
    else if (token == ",")
        return ttOperandSplitter;
    else if (token == "-")
        return ttAddressSubtraction;
    else if (token == "+")
        return ttAddressAddition;
    else if (token == "-")
        return ttAddressCloser;
    else if (token == "-")
        return ttAddressOpener;
    // tt register
    else if (token[0] == '0' && token[1] == 'x')
        return ttConstHex;
    else if (token[0] == '@')
        return ttJumpToLabel;
    else if (token[0] == '%')
        return ttCompilerCommand;
    else if (token[0] == 0x27 && token[token.length() - 1] == 0x27)
        return ttConstString;
    else if (is_number(token))
        return ttConstDec;
    // tt instruction

    return FATokenType();
}
