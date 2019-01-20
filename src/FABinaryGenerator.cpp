#include "stdafx.h"
#include "FABinaryGenerator.h"


FlexASM::FABinaryGenerator::FABinaryGenerator()
{
}


FlexASM::FABinaryGenerator::~FABinaryGenerator()
{
}

const std::vector<char> FlexASM::FABinaryGenerator::CreateBinaryStream(ProgramPtr program)
{
    // FileType Information
    std::vector<char> result = { 'F', 'A', 'E', 0, 0 };

    // Header Section
    std::vector<char> headerSection = { 0, 0, 0, 0 };
    result.insert(result.end(), headerSection.begin(), headerSection.end());

    // Get Data and Text Section Opcodes
    std::vector<char> dataSection = program->Data->GetOpcode();
    std::vector<char> textSection = program->Code->GetOpcode();

    // Data Section Size
    uint32_t length = dataSection.size();
    std::vector<char> size = { (char)(length >> 24), (char)(length >> 16), (char)(length >> 8), (char)length };
    result.insert(result.end(), size.begin(), size.end());

    // Text Section Size
    length = textSection.size();
    size = { (char)(length >> 24), (char)(length >> 16), (char)(length >> 8), (char)length };
    result.insert(result.end(), size.begin(), size.end());

    // Data Section
    result.insert(result.end(), dataSection.begin(), dataSection.end());

    // Text Section
    result.insert(result.end(), textSection.begin(), textSection.end());

    return result;
}

void FlexASM::FABinaryGenerator::SaveToFile(ProgramPtr program, const std::string filePath)
{
    const std::vector<char> stream = this->CreateBinaryStream(program);


    std::ofstream writeFile;
    writeFile.open(filePath, std::ios::out | std::ios::binary);
    writeFile.flush();
    writeFile.write(&stream[0], stream.size());
    writeFile.close();
}
