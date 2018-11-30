#include "stdafx.h"
#include "FAExceptions.h"


FlexASM::ParserUnexpectedTokenException::ParserUnexpectedTokenException(Token token, const std::string expected)
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

FlexASM::ParserIdentifierRedefinedException::ParserIdentifierRedefinedException(Token token, const std::string variableName)
    : Exception(token)
{
    _token = token;
    _variableName = variableName;
}

std::string FlexASM::ParserIdentifierRedefinedException::GetMessage()
{
    return "[Error] (" + std::to_string(_token.Line) + ", " + std::to_string(_token.Position) + ") Identifier '" + _variableName + "' already in use.";
}

FlexASM::Exception::Exception(Token token)
{
    _token = token;
}

FlexASM::ParserInvalidPseudoInstructionException::ParserInvalidPseudoInstructionException(Token token, const std::string instructionName)
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

std::string FlexASM::TokenizerEndOfFileException::GetMessage()
{
    return "End of file exception";
}

std::string FlexASM::ParserUnexpectedEndOfFile::GetMessage()
{
    return "Unexpected end of file after token: '"+_token.Value+"'";
}

std::string FlexASM::ParserEndOfFileException::GetMessage()
{
    return "Finished";
}

FlexASM::ParserUnknownInstructionException::ParserUnknownInstructionException(const std::string instruction)
    : Exception({})
{
    _instruction = instruction;
}

std::string FlexASM::ParserUnknownInstructionException::GetMessage()
{
    return "Unknown instruction '" + _instruction + "'";
}

FlexASM::ParserUndeclaredIdentifierException::ParserUndeclaredIdentifierException(const std::string identifierName)
    : Exception({})
{
    _name = identifierName;
}

std::string FlexASM::ParserUndeclaredIdentifierException::GetMessage()
{
    return "[Error] (" + std::to_string(_token.Line) + ", " + std::to_string(_token.Position) + ") Undeclared identifier '" + _name + "'.";
}
