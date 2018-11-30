# FlexApplication Excutable Format (Version 0x00)

This document describes the most recent version (FlexAssembler Compiler Version RC2) structure of a FlexApplication Binary Executable file.

The FlexASM Compiler builds binaries in a very special and unique format which aims to be very simple and fast to parse.

The FlexApplication Executable Binary consists of a very small header followed by multiple sections responsible for static memory allocations and code execution.

## Header

The header gives the operating system / virtual machine informations about the executable file. As of this version only the section sizes are specifed but in the future it will contain resources aswell as entries to shared code.

### FileType Information

To specify a FlexApplication Binary it is required to add 5 bytes to the beginning of the file. The first 3 bytes consist of the ASCII chars ``FAE`` which stands for "FlexApplication Executable" which are followed by two zero-bytes ``0x00 0x00``, where the second zero-byte stands for the FlexApplication Executable format version. 

### Section Informations

After the FileType Information the Header contains informations about its sections. As of this version only the sizes are specified as four bytes each.

### Example Header

 ``0x46 0x41 0x45 0x00 0x00 0x00 0x00 0x00 0x12 0x00 0x00 0x00 0xFA``

## Data Section

The Data Section contains all static memory declarations for this specific binary file. It is almost built like the text section but has different parameters.

Example:

``0x30 0x00 0x00 0x00 0xFF
0x31 0x00 0x00 0x00 0x02 0x04 0x20``

This example reserves 255 uninitialized bytes and defines 2 bytes. (`0x4` and `0x20`)

## Text Section

The Text Section consists of the executable code. The instruction always follow the same rules. First comes the instruction opcode followed by the parameters.

There are only three types of parameters on the binary level:
- Constant values
- Registers
- Addresses

Constant values and addresses must specify an operation size in front of them.

|Operation Size Byte|Size|
|---|---|
|0x01|BYTE|
|0x02|WORD|
|0x04|DWORD|


### Constant Values

Very simple: Just the operation size followed by either one, two or four bytes of data.

Examples:
``0x01 0xFF``

``0x02 0x04 0x20``

``0x04 0x04 0x20 0x13 0x37``

### Registers

Registers are also very simple and just contains a specific byte of the register. You can see every register and its bytes in this table:

|Register|Byte|
|---|---|
|AL|0x01|
|BL|0x01|
|CL|0x02|
|DL|0x03|
|AH|0x04|
|BH|0x05|
|CH|0x06|
|DH|0x07|
|AX|0x08|
|BX|0x09|
|CX|0x0a|
|DX|0x0b|
|EAX|0x0c|
|EBX|0x0d|
|ECX|0x0e|
|EDX|0x0f|
|ESP|0x10|
|EBP|0x11|

Note that register dont need any operation size specification as the register itself does that.

### Addresses

Addresses are the only complex parameter type in a FlexApplication Executable.

An address can consist of either just a constant value, a register or even an addition / subtraction of both. More informations about that is in the FlexASM QuickStart Guide.

To achieve this there is one byte prepended which specifies all parts of an address definition.

Part of Byte|Description
---|---
[000]00000|Left Value Type
000[00]000|Operation Type
00000[000]|Right Value Type

Possible Value Type Values:

Value|Description
---|---
0b000|Constant Value
0b001|Register
0b010|Reserved
0b011|Reserved
0b100|Reserved
0b101|Reserved
0b111|Reserved

Possible Operation Type Values:

Value|Description
---|---
0b00|Addition
0b01|Subtraction
0b10|Reserved
0b11|Reserved

For example, we want to compile this address: ``[eax+8]``

The correspondent byte we need to prepend would be: ``0b00100000`` or ``0x20``

After that follow the two paramters. They are simply written as in the examples above.

Full example of the address ``[eax+420]``:

``0x20 0x0C 0x02 0x01 0xA4 ``

## Backwards Compatibility
Unfortunately the version which is described here is not backwards compatible with older formats which older compilers have generated. We try to keep backwards compatibilty for the next versions but we can not guarantee it as everything is very experimental yet.
