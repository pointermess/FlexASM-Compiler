# FlexASM Compiler
This repository contains the new FlexASM compiler which is open source and written in modern C++.

The reasons for the complete rewrite are following:
- To provide an open source assembler written in modern C++.
- To add features which were not easily possible with the first version.
- To use the things I learned from writing the first (two) version(s).
- And most important, to learn modern C++.

It takes in the FlexASM assembly dialect and generates an executable binary file which can be run using the Flex Runtime Environment.

### How to run?

``flasm.exe INPUT_FILE_PATH``

Compiles the input file into a FlexApplication Executable and saves it on the same path with the same name but a ``.fae`` file extension.

``flasm.exe INPUT_FILE_PATH OUTPUT_FILE_PATH``

Compiles the input file into a FlexApplication Executable and saves it to the output file path.
