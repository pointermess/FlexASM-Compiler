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
#include "FABinaryGenerator.h"

#include <fstream>
#include <filesystem>


void ParseAndGenerate(std::string inputPath, std::string outputPath)
{
    auto parser = std::make_unique<FlexASM::Parser>();
    auto program = parser->ParseFile(inputPath);

    if (program != nullptr)
    {
        auto generator = std::make_shared<FABinaryGenerator>();
        const std::vector<char> stream = generator->CreateBinaryStream(program);


        std::ofstream writeFile;
        writeFile.open(outputPath, std::ios::out);
        writeFile.flush();
        writeFile.write(&stream[0], stream.size());
        writeFile.close();
    }
}

int main(int argc, char *argv[])
{

    FlexASM::InitValidRegisters();
    FlexASM::InitValidInstructions();

    std::cout << "FlexASM Compiler Version 0.1" << std::endl << std::endl;

    if (argc < 2)
    {
        std::filesystem::path binName = argv[0];

        std::cout << "Following run parameters are supported:" << std::endl;
        std::cout << "- " << binName.filename() << " INPUT_FILE" << std::endl;
        std::cout << "- " << binName.filename() << " INPUT_FILE_PATH OUTPUT_FILE_PATH" << std::endl;
    }
    else if (argc == 2)
    {
        std::filesystem::path inputPath(argv[1]);
        inputPath = std::filesystem::absolute(inputPath);

        if (std::filesystem::exists(inputPath))
        {
            std::filesystem::path path = inputPath.root_path();
            path /= inputPath.parent_path();
            path /= inputPath.stem();
            path += ".fae";

            ParseAndGenerate(inputPath.u8string(), path.u8string());

            std::cout << "Compilation finished." << std::endl;
            std::cout << "Created binary at " << path << std::endl;
        }
    }
    else if (argc == 3)
    {
        std::filesystem::path inputPath(argv[1]);
        inputPath = std::filesystem::absolute(inputPath);
        std::filesystem::path outputPath(argv[2]);
        outputPath = std::filesystem::absolute(outputPath);

        if (std::filesystem::exists(inputPath))
        {
            ParseAndGenerate(inputPath.u8string(), outputPath.u8string());

            std::cout << "Created binary at " << outputPath << std::endl;
        }
    }

    return 0;
}
