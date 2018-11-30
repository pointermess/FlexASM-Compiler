#pragma once
#include <exception> 
#include <string>
#include "FAToken.h"


namespace FlexASM
{

    class Exception : public std::exception
    {
    protected:
        Token _token;

    public:
        Exception(Token token);

        virtual std::string GetMessage() = 0;

    };

    class TokenizerEndOfFileException : public std::exception
    {
    public:
        std::string GetMessage();
    };

    class ParserUnexpectedTokenException : public Exception
    {
    private:
        std::string _expected;
    public:
        ParserUnexpectedTokenException(Token token, const std::string expected);
        ParserUnexpectedTokenException(Token token) : Exception(token) {};

        std::string GetMessage();
    };

    class ParserUnknownInstructionException : public Exception
    {
    private:
        std::string _instruction;
    public:
        ParserUnknownInstructionException(const std::string instruction);

        std::string GetMessage();
    };

    class ParserUnexpectedSectionException : public Exception
    {
    private:
        std::string _expected;
    public:
        ParserUnexpectedSectionException(Token token) : Exception(token) {};

        std::string GetMessage();
    };

    class ParserUnexpectedEndOfFile : public Exception
    {
    private:
        std::string _lastToken;
    public:
        ParserUnexpectedEndOfFile(Token token) : Exception(token) {};

        std::string GetMessage();
    };

    class ParserEndOfFileException : public Exception
    {
    public:
        ParserEndOfFileException() : Exception({}) {};

        std::string GetMessage();
    };

    class ParserIdentifierRedefinedException : public Exception
    {
    private:
        Token _token;
        std::string _variableName;
    public:
        ParserIdentifierRedefinedException(Token token, const std::string variableName);
        std::string GetMessage();
    };

    class ParserInvalidPseudoInstructionException : public Exception
    {
    private:
        Token _token;
        std::string _instructionName;
    public:
        ParserInvalidPseudoInstructionException(Token token, const std::string instructionName);
        std::string GetMessage();
    };

    class ParserUndeclaredIdentifierException : public Exception
    {
    private:
        std::string _name;
        std::string _instructionName;
    public:
        ParserUndeclaredIdentifierException(const std::string identifierName);
        std::string GetMessage();
    };

    

}
