#pragma once

#include <string>
#include <vector>
#include <memory>

#include "FAProgramCode.h"
#include "FAProgramData.h"

namespace FlexASM
{
    class Program
    {
    private:
    public:
        ProgramCodePtr Code;
        ProgramDataPtr Data;

        Program();
        ~Program();
    };
    typedef std::shared_ptr<Program> FAProgramPtr;

}

