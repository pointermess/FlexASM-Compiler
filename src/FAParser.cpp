#include "stdafx.h"

#include "FAParser.h"
#include "FATokenizer.h"
#include "FAPreprocessor.h"
#include "FATypes.h"
#include "FAExceptions.h"
#include "FAProgramData.h"
#include "Utilities.h"

#include <iostream>

using namespace FlexASM;

void Parser::Parse(TokenizerPtr tokenizer, ProgramPtr program)
{
    while (tokenizer->IsInRange())
    {
        Token token;

        try
        {
            token = tokenizer->GetCurrentToken();
        }
        catch (TokenizerEndOfFileException e)
        {
        }

        if (token.Type == ttSectionKeyword)
        {
            ParseSection(tokenizer, program);
        }
        else
        {
            throw ParserUnexpectedEndOfFile(tokenizer->Tokens[tokenizer->Tokens.size() - 1]);
        }
    }
}

void Parser::ParseSection(TokenizerPtr tokenizer, ProgramPtr program)
{
    Token token = tokenizer->GetCurrentToken();

    if (token.Type == ttSectionKeyword)
    {
        tokenizer->NextToken();

        try
        {
            token = tokenizer->GetCurrentToken();
        }
        catch (TokenizerEndOfFileException e)
        {
            throw ParserUnexpectedEndOfFile(tokenizer->Tokens[tokenizer->Tokens.size() - 1]);
        }

        if (token.Value == ".data")
        {
            tokenizer->NextToken();
            ParseDataSection(tokenizer, program);
        }
        else if (token.Value == ".text")
        {
            tokenizer->NextToken();
            ParseTextSection(tokenizer, program);
        }
        else
        {
            throw ParserUnexpectedSectionException(token);
        }
    }
}

void Parser::ParseProgram(TokenizerPtr tokenizer, ProgramPtr program)
{
}

void FlexASM::Parser::ParseDataSection(TokenizerPtr tokenizer, ProgramPtr program)
{
    try
    {
        while (tokenizer->GetCurrentToken().Type == ttLabel)
        {
            ParseDataSectionItem(tokenizer, program);
        }
    }
    catch (TokenizerEndOfFileException e)
    {
        throw ParserEndOfFileException();
    }
}

/*
 * ParseDataSectionItem
 *
 * Parses an item inside the data section.
 * It handles both, initialized and uninitialized, types of items.
 */
void FlexASM::Parser::ParseDataSectionItem(TokenizerPtr tokenizer, ProgramPtr program)
{
    try
    {
        Token token = tokenizer->GetCurrentToken();

        if (token.Type == ttLabel)
        {
            // extract label name and check if it already exists
            std::string labelName;
            labelName.assign(token.Value, 0, token.Value.length() - 1);

            uint32_t address = 0;
            if (!program->Data->GetAddressOfVariable(labelName, address))
            {
                // parse instruction
                tokenizer->NextToken();
                token = tokenizer->GetCurrentToken();

                if (IsValidPseudoInstruction(token.Value))
                {
                    Instruction instruction = PseudoInstruction(token.Value);
                    MemorySize operationSize = PseudoInstructionOperationSize(instruction);


                    // define variable to be parsed
                    std::shared_ptr<ProgramDataVariableInterface> dataVariable;

                    if (IsPseudoInstructionReservation(instruction))
                    {
                        // Parse uninitialized data (reservations)


                        tokenizer->NextToken();
                        token = tokenizer->GetCurrentToken();

                        if (token.Type == ttConstDec)
                        {
                            int tokenValue = std::stoi(token.Value);

                            if (tokenValue != 0)
                            {
                                dataVariable = std::make_shared<ProgramDataVariable>(labelName, operationSize, tokenValue);
                                tokenizer->NextToken();
                            }
                            else
                            {
                                throw ParserUnexpectedTokenException(token);
                            }
                        }
                    }
                    else
                    {
                        // Parse initialized data

                        std::vector<uint32_t> data;

                        // parse arguments
                        bool reachedEnd = false;

                        while (!reachedEnd)
                        {
                            tokenizer->NextToken();
                            token = tokenizer->GetCurrentToken();


                            // check argument and add if complient
                            if (token.Type == ttConstDec || token.Type == ttConstHex)
                            {
                                int tokenValue = parse_number(token.Value);

                                data.push_back(tokenValue);
                            }
                            else if (token.Type == ttConstString)
                            {
                                std::string str;
                                str.assign(token.Value, 1, token.Value.length() - 2);

                                for (auto& c : str)
                                {
                                    data.push_back(c);
                                }
                            }
                            else
                            {
                                throw ParserUnexpectedTokenException(token);
                            }

                            try
                            {
                                // check if it was the last argument
                                tokenizer->NextToken();
                                token = tokenizer->GetCurrentToken();

                                if (token.Type != ttOperandSplitter)
                                {
                                    reachedEnd = true;
                                }
                            }
                            catch (TokenizerEndOfFileException e)
                            {
                                dataVariable = std::make_shared<ProgramDataInitializedVariable>(labelName, operationSize, data);
                                program->Data->Variables.push_back(dataVariable);

                                throw ParserEndOfFileException();
                            }
                        }


                        dataVariable = std::make_shared<ProgramDataInitializedVariable>(labelName, operationSize, data);
                    }

                    program->Data->Variables.push_back(dataVariable);
                }
                else
                {
                    throw ParserInvalidPseudoInstructionException(token, token.Value);
                }
            }
            else
            {
                throw ParserIdentifierRedefinedException(token, labelName);
            }
        }
    }
    catch (TokenizerEndOfFileException e)
    {
        throw ParserUnexpectedEndOfFile(tokenizer->Tokens[tokenizer->Tokens.size() - 1]);
    }
}

void FlexASM::Parser::ParseTextSection(TokenizerPtr tokenizer, ProgramPtr program)
{
    try
    {
        while (tokenizer->GetCurrentToken().Type == ttLabel)
        {
            ParseTextSectionSection(tokenizer, program);
        }
    }
    catch (TokenizerEndOfFileException e)
    {
        throw ParserEndOfFileException();
    }
}

void FlexASM::Parser::ParseTextSectionSection(TokenizerPtr tokenizer, ProgramPtr program)
{
    Token token = tokenizer->GetCurrentToken();

    if (token.Type == ttLabel)
    {
        // extract label name and check if it already exists
        std::string labelName;
        labelName.assign(token.Value, 0, token.Value.length() - 1);


        if (program->Code->FindSection(labelName) == nullptr)
        {
            ProgramSectionPtr programSection = std::make_shared<ProgramSection>();
            programSection->Name = labelName;

            tokenizer->NextToken();

            try
            {
            while (tokenizer->GetCurrentToken().Type == ttInstruction)
            {
                ParseTextSectionSectionItem(tokenizer, program, programSection);
            }
            }
            catch (TokenizerEndOfFileException e)
            {
            }



            program->Code->AddSection(programSection);
        }
        else
        {
        throw ParserIdentifierRedefinedException(token, labelName);
        }
    }
}

void FlexASM::Parser::ParseTextSectionSectionItem(TokenizerPtr tokenizer, ProgramPtr program, ProgramSectionPtr programSection)
{
    ProgramInstructionPtr instruction = std::make_shared<ProgramInstruction>();

    Token token = tokenizer->GetCurrentToken();

    if (token.Type == ttInstruction)
    {

        instruction->InstructionStr = token.Value;

        // parse arguments
        try
        {

            bool reachedEnd = false;

            while (!reachedEnd)
            {
                tokenizer->NextToken();
                token = tokenizer->GetCurrentToken();

                FATokenType checkTokenType = token.Type;

                if (checkTokenType == ttSize)
                    checkTokenType = tokenizer->GetNextToken().Type;

                if (checkTokenType == ttConstDec || checkTokenType == ttConstHex || checkTokenType == ttDataAlias)
                {
                    ParseTextSectionSectionItemConst(tokenizer, program, instruction);
                }
                else if (checkTokenType == ttRegister)
                {
                    ParseTextSectionSectionItemRegister(tokenizer, program, instruction);
                }
                else if (checkTokenType == ttAddressOpener)
                {
                    ParseTextSectionSectionItemAddress(tokenizer, program, instruction);
                }
                else
                {
                    if (checkTokenType != ttOperandSplitter)
                        reachedEnd = true;
                }
            }
        }
        catch (TokenizerEndOfFileException e)
        {
        }

        if (IsValidInstruction(instruction->BuildPattern()))
        {
            instruction->InstructionEnum = GetInstructionByPattern(instruction->BuildPattern());
            programSection->Instructions.push_back(instruction);
        }
        else
        {
            throw ParserUnknownInstructionException(instruction->BuildPattern());
        }

    }
}

void FlexASM::Parser::ParseTextSectionSectionItemConst(TokenizerPtr tokenizer, ProgramPtr program, ProgramInstructionPtr programInstruction)
{
    Token token = tokenizer->GetCurrentToken();
    ProgramInstructionConstIntParameterPtr param = std::make_shared<ProgramInstructionConstIntParameter>();

    if (token.Type == ttSize)
    {
        param->OperationSize = ParseMemorySize(token.Value);
        tokenizer->NextToken();
        token = tokenizer->GetCurrentToken();
    }

    if (token.Type == ttConstDec || token.Type == ttConstHex)
    {
        param->Value = parse_number(token.Value);
        programInstruction->Parameters.push_back(param);
    }
    else if (token.Type == ttDataAlias)
    {
        std::string aliasName = token.Value.substr(1, token.Value.length() - 1);
        
        uint32_t address = 0;

        if (program->Data->GetAddressOfVariable(aliasName, address))
        {
            param->Value = address;
            programInstruction->Parameters.push_back(param);
        }
    }
}

void FlexASM::Parser::ParseTextSectionSectionItemRegister(TokenizerPtr tokenizer, ProgramPtr program, ProgramInstructionPtr programInstruction)
{
    Token token = tokenizer->GetCurrentToken();
    ProgramInstructionRegisterParameterPtr param = std::make_shared<ProgramInstructionRegisterParameter>();

    if (token.Type == ttSize)
    {
        param->OperationSize = ParseMemorySize(token.Value);
        tokenizer->NextToken();
        token = tokenizer->GetCurrentToken();
    }

    if (token.Type == ttRegister)
    {
        param->Value = ParseRegister(token.Value);
        programInstruction->Parameters.push_back(param);
    }
}

void FlexASM::Parser::ParseTextSectionSectionItemAddress(TokenizerPtr tokenizer, ProgramPtr program, ProgramInstructionPtr programInstruction)
{
    Token token = tokenizer->GetCurrentToken();
    ProgramInstructionAddressParameterPtr param = std::make_shared<ProgramInstructionAddressParameter>();

    // check if operation size is defined
    if (token.Type == ttSize)
    {
        param->OperationSize = ParseMemorySize(token.Value);
        tokenizer->NextToken();
        token = tokenizer->GetCurrentToken();
    }

    // start parsing fun part
    if (token.Type == ttAddressOpener)
    {
        tokenizer->NextToken();
        token = tokenizer->GetCurrentToken();

        // parse left operand
        if (token.Type == ttConstDec || token.Type == ttConstHex)
        {
            param->OperandLeft = vtConstantValue;
            param->OperandLeftConstant = parse_number(token.Value);
        }
        else if (token.Type == ttDataAlias)
        {
            param->OperandLeft = vtConstantValue;

            uint32_t address;
            std::string name = token.Value.substr(1, token.Value.length() - 1);
            if (program->Data->GetAddressOfVariable(name, address))
            {
                param->OperandLeftConstant = address;
            }
            else
            {
                throw ParserUndeclaredIdentifierException(name);
            }
        }
        else if (token.Type == ttRegister)
        {
            param->OperandLeft = vtRegister;    
            param->OperandLeftRegister = ParseRegister(token.Value);
        }
        else
        {
            throw ParserUnexpectedTokenException(token, "register or constant value as left operand");
        }

        tokenizer->NextToken();
        token = tokenizer->GetCurrentToken();

        // check if there is an operation and a right operand
        if (token.Type == ttAddressCloser)
        {
            // no right operand
            programInstruction->Parameters.push_back(param); 
        }
        else if (token.Type == ttAddressAddition || token.Type == ttAddressSubtraction)
        {
            // get operation
            OperationType operation = otAddition;
            if (token.Type == ttAddressSubtraction) operation = otSubtraction;

            param->Operation = operation;

            tokenizer->NextToken();
            token = tokenizer->GetCurrentToken();

            if (token.Type == ttConstDec || token.Type == ttConstHex)
            {
                param->OperandRight = vtConstantValue;
                param->OperandRightConstant = parse_number(token.Value);
            }
            else if (token.Type == ttDataAlias)
            {
                param->OperandRight = vtConstantValue; 

                uint32_t address;
                std::string name = token.Value.substr(1, token.Value.length() - 1);
                if (program->Data->GetAddressOfVariable(name, address))
                {
                    param->OperandRightConstant = address;
                }
                else
                {
                    throw ParserUndeclaredIdentifierException(name);
                }
            }
            else if (token.Type == ttRegister)
            {
                param->OperandRight = vtRegister;
                param->OperandRightRegister = ParseRegister(token.Value);
            }
            else
            {
                throw ParserUnexpectedTokenException(token, "register or constant value as right operand");
            }

            tokenizer->NextToken();
            token = tokenizer->GetCurrentToken();

            if (token.Type == ttAddressCloser)
            {
                // no right operand
                programInstruction->Parameters.push_back(param);
            }
            else
            {
                throw ParserUnexpectedTokenException(token);
            }
        }
        else
        {
            throw ParserUnexpectedTokenException(token, "register or constant value as left operand");
        }
    }
}



Parser::Parser()
{
}


Parser::~Parser()
{
}


/*
 * ParseFile
 *
 * The public function which is used to parse FlexASM code in a specific file using its path.
 * This function calls private functions to generate an output representing the parsed program.
 */
ProgramPtr Parser::ParseFile(const std::string filePath)
{
    // Preprocess file
    std::shared_ptr<Preprocessor> preprocessor = std::make_unique<Preprocessor>();
    std::string sourceCode = preprocessor->Preprocess(filePath);

    // Tokenize preprocessed source code
    std::shared_ptr<Tokenizer> tokenizer = std::make_shared<Tokenizer>();
    tokenizer->Tokenize(sourceCode);

    // Parse tokens
    std::shared_ptr<Program> result = std::make_shared<Program>();

    try
    {
        Parse(tokenizer, result);
        std::cout << "Compilation successful. [OK]" << std::endl;
    }
    catch (ParserEndOfFileException& e)
    {
        std::cout << "Compilation successful. [EOF]" << std::endl;
    }
    catch (Exception& e)
    {
        std::cout << e.GetMessage() << std::endl;
        return nullptr;
    }

    return result;
}

