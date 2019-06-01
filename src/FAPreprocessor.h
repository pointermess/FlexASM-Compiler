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

        const std::string RemoveComments( std::string input);
        const std::string IncludeFiles(const std::string input, const std::string filePath);
        const std::string Preprocess(const std::string fileName);
    };

}