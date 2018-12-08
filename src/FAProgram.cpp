#include "stdafx.h"

#include "FAProgram.h"


FlexASM::Program::Program()
{
    Code = std::make_shared<ProgramCode>();
    Data = std::make_shared<ProgramData>();

    LookupTable = std::make_shared<FlexASM::LookupTable>();
}


FlexASM::Program::~Program()
{
}
