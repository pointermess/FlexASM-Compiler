// FlexASM Compiler.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"

#include <vector>
#include <memory>
#include <iostream>

#include "FATokenizer.h"
#include "FAPreprocessor.h"

void CompileFile(std::string fileName)
{
    std::unique_ptr<FAPreprocessor> preprocessor = std::make_unique<FAPreprocessor>();
    std::string sourceCode = preprocessor->Preprocess(fileName);


    std::unique_ptr<FATokenizer> tokenizer = std::make_unique<FATokenizer>();
    tokenizer->Tokenize(sourceCode);


    for (FAToken & token : tokenizer->Tokens)
    {
        std::cout << token.Type << ": " << token.Value << std::endl;
    }
}

int main()
{
    CompileFile("D:/asm/cpp/main.txt");
    getchar();
    return 0;
}

