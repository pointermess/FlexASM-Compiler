#include "stdafx.h"
#include <algorithm>

#include "Utilities.h"

#include "FAToken.h"
#include "FATypes.h"

using namespace FlexASM;

FATokenType FlexASM::Token::GetType(std::string TokenValue)
{
    std::string token = TokenValue;

    // set token to lowercase
    str_to_lower(token);

    if (token[token.length() - 1] == ':')
        return ttLabel;
    else if (token == "byte" || token == "word" || token == "dword")
        return ttSize;
    else if (token == "section")
        return ttSectionKeyword;
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
    else if (IsValidRegister(token))
        return ttRegister;
    else if (token[0] == '0' && token[1] == 'x')
        return ttConstHex;
    else if (token[0] == '@')
        return ttLabelAlias;
    else if (token[0] == '.')
        return ttDataAlias;
    else if (token[0] == '%')
        return ttCompilerCommand;
    else if (token[0] == 0x27 && token[token.length() - 1] == 0x27)
        return ttConstString;
    else if (is_number(token))
        return ttConstDec;
    else
    {
        // check instruction
        for (auto instruction : ValidInstructions)
        {
            std::string compareTo;
            compareTo.assign(instruction.Pattern, 0, token.length());

            if (compareTo == token) return ttInstruction;
        }
    }
    // tt instruction

    return ttUnknown;
}
