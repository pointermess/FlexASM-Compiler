#pragma once
#include <map>
#include <string>

namespace FlexASM
{
    class LookupTable
    {
    private:
        std::map<std::string, unsigned int> _LookupTable;
    public:
        LookupTable();
        ~LookupTable();
        void Add(const std::string name, const unsigned int value);
        const bool Find(const std::string name, unsigned int& value);
    };
    typedef std::shared_ptr<LookupTable> LookupTablePtr;
}
