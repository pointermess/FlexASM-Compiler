
# FlexASM QuickStart Guide [Version 0.2.2]
## Syntax
### Constant Values

As of version RC2, the assembler supports four ways of defining constant numeric values.

| Base | Example | Formatter | Supported version |
| --- | --- | --- | --- |
| 10 (decimal) | 123 | none | First version |
| 16 (hexadecimal) | 0x7B | Prefixed "0x" | First version |
| 8 (octal) | 0o173 | Prefixed "0o" | After RC2 |
| 2 (binary) | 0b1111011 | Prefixed "0b" | After RC2 |

***Note:** Binary representation wil l only work with 8 bit values. (0 - 255)*

### Registers

FlexVM works with only 6 registers, where 4 of them are for general purpose and 2 of them are used for stack operations:

| Register | Description |
|---|---|
| EAX | General Purpose |
| EBX | General Purpose |
| ECX | General Purpose |
| EDX | General Purpose |
| ESP | Stack Pointer |
| EBP | Base Pointer |

All general purpose registers can be accessed by either one, two or four bytes at a time.

| Pattern | Bytes | Size |
|---|---|---|
| \*L | 000000\[00] | 1 Byte |
| \*H | 0000\[00]00 | 1 Byte |
| \*X | \[0000]0000 | 2 Bytes |
| E\*X | \[00000000] | 4 Bytes |

### Addresses

### Operation Size

It is possible to specify an operation size for any type of argument which holds data such as constant values, registers and addresses. Since labels do not store or point to any data in memory, it is not possible to use an operation size with them.

There are all three basic sizes available to use.

| Operation | Size |
|---|---|
| BYTE | 1 Byte |
| WORD | 2 Bytes |
| DWORD | 4 Bytes |

To specify an operation size you have to put its keyword in front of an element.

Example:
```assembly
mov eax, WORD [esp] ; moves two bytes at the address of esp in to eax
```

### Labels
## Memory
### Declaring static data regions

As of version RC2 it is possible to declare static data regions. These can hold a defined amount of data and can be named to gain easy access to these regions by using aliases and operations.

| Operation | Description |
|---|---|
| db | Defines a Byte |
| dw | Defines a Word |
| dd | Defines a DWord |
| resb | Reserves unitialized Bytes |
| resw | Reserves unitialized Words |
| resd | Reserves unitialized DWords |

These declarations must be placed in the `.data` section of every file.

Example:

```assembly
section .data
    ; reserve uninitialized memory space
    reservedBytes: resb 4
    reservedWords: resw 2
    reservedDWord: resd 1

    ; single data values
    byteData: db 42
    wordData: dw 420
    intData:  dd 0x420

    ; multi data values
    byteArray: db 4,204,20
    wordArray: dw 420,420,420
    intArray:  dd 0x42000,0x420
```

***Note:** Every declaration, unless it's one with "res", has to be initalized with a default value.*

### Addressing Memory
## Instructions

In the following chapter we will look at the instruction set.

| Notation | Desctiption |
| --- | --- |
| \<con\> | A constant value (ex. 4) |
| \<reg\> | A register (ex. [eax]) |
| \<mem\> | A memory address (ex. [eax+4]) |

### Data operations
#### MOV - Move Instruction

Moves data from one place to an other.

|  Syntax: |
|   ---   |
| mov \<reg\>, \<con\> |
| mov \<reg\>, \<reg\> |
| mov \<reg\>, \<mem\> |
| mov \<mem\>, \<con\> |
| mov \<mem\>, \<reg\> |
| mov \<mem\>, \<mem\> |

### Arithmetic operations
### Binary operations
### Control-Flow operations
### Debug operations
## System Calls
### System Utilities
### Graphics Output
