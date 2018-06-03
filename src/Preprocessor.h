#pragma once
#include <string>

class FAPreprocessor
{
public:
	char CommentChar;

	FAPreprocessor();
	~FAPreprocessor();

	std::string RemoveComments(std::string input);
	std::string IncludeFiles(std::string input, std::string filePath);
	std::string Preprocess(std::string fileName);
};

