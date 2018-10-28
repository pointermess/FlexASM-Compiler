#pragma once
#include <string>

namespace FlexASM
{
    class Preprocessor
    {
    public:
        char CommentChar;
        char StringChar;

        Preprocessor();
        ~Preprocessor();

        std::string RemoveComments(std::string input);
        std::string IncludeFiles(std::string input, std::string filePath);
        std::string Preprocess(std::string fileName);
    };

}