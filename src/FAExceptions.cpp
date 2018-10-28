#include "stdafx.h"
#include "FAExceptions.h"

FlexASM::ParserUnexpectedTokenException::ParserUnexpectedTokenException(FAToken token)
{
    _token = token;
    
}


std::string FlexASM::ParserUnexpectedTokenException::GetMessage()
{
    return "[Error] ("+ std::to_string(_token.Line) + ", " + std::to_string(_token.Position) + ") Unexpected token '" + _token.Value + "'.";
}
