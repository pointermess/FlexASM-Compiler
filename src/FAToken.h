#pragma once

#include <string>
namespace FlexASM
{

    enum FATokenType
    {
        ttUnknown,
        ttCompilerCommand,
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
        ttLabelAlias,
        ttSectionKeyword,
        ttDataAlias,
    };

    struct FAToken
    {
    public:
        std::string Value;
        unsigned int Position;
        unsigned int Line;
        FATokenType Type;

        static FATokenType GetType(std::string TokenValue);
    };

}