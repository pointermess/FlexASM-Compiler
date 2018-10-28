#pragma once
#include <exception>
#include <string>
#include "FAToken.h"


namespace FlexASM
{

    class Exception : public std::exception
    {

    public:


    };

    class ParserUnexpectedTokenException : public Exception
    {
    private:
        FAToken _token;
    public:
        ParserUnexpectedTokenException(FAToken token);

        std::string GetMessage();
    };

}
