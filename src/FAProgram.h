#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "FAProgramCode.h"
#include "FAProgramData.h"
#include "FALookupTable.h"

namespace FlexASM
{
    class Program
    {
    private:
    public:
        LookupTablePtr LookupTable;

        ProgramCodePtr Code;
        ProgramDataPtr Data;


        Program();
        ~Program();
    };
    typedef std::shared_ptr<Program> ProgramPtr;

}

