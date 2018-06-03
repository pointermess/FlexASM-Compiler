#include "stdafx.h"
#include "Utilities.h"
#include <algorithm>
#include <fstream>
#include <streambuf>

bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

void str_to_lower(std::string & s)
{
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
}

std::string read_file(std::string fileName)
{
	std::ifstream t(fileName);
	std::string result((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	return result;
}
