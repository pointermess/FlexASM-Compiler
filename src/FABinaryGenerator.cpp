#include "stdafx.h"
#include "FABinaryGenerator.h"


FlexASM::FABinaryGenerator::FABinaryGenerator()
{
}


FlexASM::FABinaryGenerator::~FABinaryGenerator()
{
}

const std::vector<uint8_t> FlexASM::FABinaryGenerator::CreateBinaryStream(ProgramPtr program)
{
    // FileType Information
    std::vector<uint8_t> result = { 'F', 'A', 'E', 0, 0 };

    // Get Data and Text Section Opcodes
    std::vector<uint8_t> dataSection = program->Data->GetOpcode();
    std::vector<uint8_t> textSection = program->Code->GetOpcode();

    // Data Section Size
    uint32_t length = dataSection.size();
    std::vector<uint8_t> size = { (uint8_t)(length >> 24), (uint8_t)(length >> 16), (uint8_t)(length >> 8), (uint8_t)length };
    result.insert(result.end(), size.begin(), size.end());

    // Text Section Size
    length = textSection.size();
    size = { (uint8_t)(length >> 24), (uint8_t)(length >> 16), (uint8_t)(length >> 8), (uint8_t)length };
    result.insert(result.end(), size.begin(), size.end());

    // Data Section
    result.insert(result.end(), dataSection.begin(), dataSection.end());

    // Text Section
    result.insert(result.end(), textSection.begin(), textSection.end());

    return result;
}
