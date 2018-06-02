// FlexASM Compiler.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <vector>
#include "Tokenizer.h"
#include <memory>
#include <iostream>

void CompileFile(std::string FileName)
{
	std::unique_ptr<FATokenizer> tokenizer = std::make_unique<FATokenizer>();
	std::vector<FAToken> tokens;

	tokenizer->Tokenize("test", &tokens);
	std::cout << tokens[0].Value;
}

int main()
{
	CompileFile("asm test");
	getchar();
    return 0;
}

