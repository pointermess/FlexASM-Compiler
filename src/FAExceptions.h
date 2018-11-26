#pragma once
#include <exception> 
#include <string>
#include "FAToken.h"


namespace FlexASM
{

    class Exception : public std::exception
    {
    protected:
        FAToken _token;

    public:
        Exception(FAToken token);

        virtual std::string GetMessage() = 0;

    };

	class ParserUnexpectedTokenException : public Exception
	{
	private:
		std::string _expected;
	public:
		ParserUnexpectedTokenException(FAToken token, const std::string expected);
		ParserUnexpectedTokenException(FAToken token) : Exception(token) {};

		std::string GetMessage();
	};

	class ParserUnexpectedSectionException : public Exception
	{
	private:
		std::string _expected;
	public:
		ParserUnexpectedSectionException(FAToken token) : Exception(token) {};

		std::string GetMessage();
	};

    class ParserIdentifierRedefinedException : public Exception
    {
    private:
        FAToken _token;
        std::string _variableName;
    public:
        ParserIdentifierRedefinedException(FAToken token, const std::string variableName);
        std::string GetMessage();
    };

    class ParserInvalidPseudoInstructionException : public Exception
    {
    private:
        FAToken _token;
        std::string _instructionName;
    public:
        ParserInvalidPseudoInstructionException(FAToken token, const std::string instructionName);
        std::string GetMessage();
    };

}
