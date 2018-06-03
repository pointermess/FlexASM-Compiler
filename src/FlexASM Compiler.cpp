// FlexASM Compiler.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"

#include <vector>
#include <memory>
#include <iostream>

#include "Tokenizer.h"
#include "Preprocessor.h"

void CompileFile(std::string fileName)
{
    std::unique_ptr<FAPreprocessor> preprocessor = std::make_unique<FAPreprocessor>();
    std::string sourceCode = preprocessor->Preprocess(fileName);

    std::cout << sourceCode;

    std::unique_ptr<FATokenizer> tokenizer = std::make_unique<FATokenizer>();
    std::vector<FAToken> tokens;
}

int main()
{
    CompileFile("D:/asm/last.txt");
    getchar();
    return 0;
}

