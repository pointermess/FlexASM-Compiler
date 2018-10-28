// FlexASM Compiler.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"

#include <vector>
#include <memory>
#include <iostream>

#include "FATokenizer.h"
#include "FAPreprocessor.h"
#include "FATypes.h"


#include "FAParser.h"

#include "FAProgramData.h"
#include "FAProgramCode.h"


int main()
{
    FlexASM::InitValidRegisters();
    
    auto parser = std::make_unique<FlexASM::Parser>();
    parser->ParseFile("D:/asm/cpp/main.txt");
    
    getchar();
    return 0;
}

