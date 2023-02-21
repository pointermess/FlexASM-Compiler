
# FlexASM QuickStart Guide [Version 0.2.2b]
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
    
    ; strings can be mixed with db, dw and dd
    strHelloWorld: db 'Hello World', 0
    strFourTwenty: db '4', 0x32, '0', 0
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
The first argument is the destination and the second is the source location/value.

|  Syntax | Opcode |
|   ---   |  ---   | 
| mov \<reg\>, \<con\> | 0xA0 |
| mov \<reg\>, \<reg\> | 0xA1 |
| mov \<reg\>, \<mem\> | 0xA2 |
| mov \<mem\>, \<con\> | 0xA3 |
| mov \<mem\>, \<reg\> | 0xA4 |
| mov \<mem\>, \<mem\> | 0xA5 |

#### PUSH - Push Instruction
Pushes data on top of the stack.

|  Syntax | Opcode |
|   ---   |  ---   | 
| push \<const\> | 0xAC |
| push \<reg\> | 0xAD |
| push \<addr\> | 0xAE |

#### POP - Pop Instruction
Pops the top of the stack to a register.

|  Syntax | Opcode |
|   ---   |  ---   | 
| pop \<reg\> | 0xAF |

### Arithmetic operations
### Binary operations
### Control-Flow operations
### Debug operations
## System Calls
### System Utilities
### Graphics Output



|  Syntax | Opcode |
|   ---   |  ---   | 
| mov \<reg\>, \<con\> | 0xA0 |
| mov \<reg\>, \<reg\> | 0xA1 |
| mov \<reg\>, \<mem\> | 0xA2 |
| mov \<mem\>, \<con\> | 0xA3 |
| mov \<mem\>, \<reg\> | 0xA4 |
| mov \<mem\>, \<mem\> | 0xA5 |
| lea \<reg\>, \<mem\> | 0xA8 |
| push \<con\> | 0xAC |
| push \<reg\> | 0xAD |
| push \<mem\> | 0xAE |
| pop \<reg\> | 0xAF |
| jmp \<label\> | 0x70 |
| jmp \<addr\> | 0x71 |
| jo \<label\> | 0x72 |
| jo \<addr\> | 0x73 |
| jno \<label\> | 0x74 |
| jno \<addr\> | 0x75 |
| js \<label\> | 0x76 |
| js \<addr\> | 0x77 |
| jns \<label\> | 0x78 |
| jns \<addr\> | 0x79 |
| je \<label\> | 0x7a |
| je \<addr\> | 0x7b |
| jne \<label\> | 0x7c |
| jne \<addr\> | 0x7d |
| jb \<label\> | 0x7e |
| jb \<addr\> | 0x7f |
| jbe \<label\> | 0x80 |
| jbe \<addr\> | 0x81 |
| ja \<label\> | 0x82 |
| ja \<addr\> | 0x83 |
| jae \<label\> | 0x84 |
| jae \<addr\> | 0x85 |
| jl \<label\> | 0x86 |
| jl \<addr\> | 0x87 |
| jle \<label\> | 0x88 |
| jle \<addr\> | 0x89 |
| jg \<label\> | 0x8a |
| jg \<addr\> | 0x8b |
| jge \<label\> | 0x8c |
| jge \<addr\> | 0x8d |
| jp \<label\> | 0x8e |
| jp \<addr\> | 0x8f |
| jnp \<label\> | 0x90 |
| jnp \<addr\> | 0x91 |
| call \<label\> | 0x92 |
| call \<addr\> | 0x93 |
| ret | 0x94 |
| int \<con\> | 0x98 |
| add \<reg\>, \<con\> | 0xE0 |
| add \<reg\>, \<reg\> | 0xE1 |
| sub \<reg\>, \<con\> | 0xE2 |
| sub \<reg\>, \<reg\> | 0xE3 |
| mul \<reg\>, \<con\> | 0xE4 |
| mul \<reg\>, \<reg\> | 0xE5 |
    | div \<reg\>, \<con\> | 0xE6 |
    | div \<reg\>, \<reg\> | 0xE7 |
    | iadd \<reg\>, \<con\> | 0xE8 |
    | iadd \<reg\>, \<reg\> | 0xE9 |
    | isub \<reg\>, \<con\> | 0xEA |
    | isub \<reg\>, \<reg\> | 0xEB |
    | imul \<reg\>, \<con\> | 0xEC |
    | imul \<reg\>, \<reg\> | 0xED |
    | idiv \<reg\>, \<con\> | 0xEE |
    | idiv \<reg\>, \<reg\> | 0xEF |
    | cmp \<reg\>, \<con\> | 0xF0 |
    | cmp \<reg\>, \<reg\> | 0xF1 |
    | dbg \<reg\> | 0xFE |
    | dbg \<mem\> | 0xFF |
