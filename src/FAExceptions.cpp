#include "stdafx.h"
#include "FAExceptions.h"


FlexASM::ParserUnexpectedTokenException::ParserUnexpectedTokenException(FAToken token, const std::string expected)
    : Exception(token)
{
    _expected = expected;
}


std::string FlexASM::ParserUnexpectedTokenException::GetMessage()
{
    std::string message = "[Error] (" + std::to_string(_token.Line) + ", " + std::to_string(_token.Position) + ") Unexpected token '" + _token.Value + "'";

    if (!_expected.empty())
        message += ", expected '" + _expected + "'";

    return message + ".";
}

FlexASM::ParserIdentifierRedefinedException::ParserIdentifierRedefinedException(FAToken token, const std::string variableName)
    : Exception(token)
{
    _token = token;
    _variableName = variableName;
}

std::string FlexASM::ParserIdentifierRedefinedException::GetMessage()
{
    return "[Error] (" + std::to_string(_token.Line) + ", " + std::to_string(_token.Position) + ") Identifier '" + _variableName + "' already in use.";
}

FlexASM::Exception::Exception(FAToken token)
{
    _token = token;
}

FlexASM::ParserInvalidPseudoInstructionException::ParserInvalidPseudoInstructionException(FAToken token, const std::string instructionName)
    : Exception(token)
{
    _token = token;
    _instructionName = instructionName;
}

std::string FlexASM::ParserInvalidPseudoInstructionException::GetMessage()
{
    return "[Error] (" + std::to_string(_token.Line) + ", " + std::to_string(_token.Position) + ") Pseudo-Instruction '" + _instructionName + "' is invalid.";

}

std::string FlexASM::ParserUnexpectedSectionException::GetMessage()
{
	return "[Error] (" + std::to_string(_token.Line) + ", " + std::to_string(_token.Position) + ") Unexpected section '" + _token.Value + "', expected '.data' or '.text'";
}
