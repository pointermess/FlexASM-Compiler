section .data
  xlimit: db 0x12
  ylimit: db 0x40
  str: db 'Hello world from FlexASM'

section .text

main:
  mov ecx, 0
  
loop_x:
  call @print_newline
  mov edx, 0
  
loop_y:
  call @print_char
  add edx, 1
  mov eax, BYTE [.ylimit]
  cmp edx, eax
  jl @loop_y


  add ecx, 1
  mov eax, BYTE [.xlimit]
  cmp ecx, eax
  jne @loop_x
  
  call @print_newline
  jmp @exit
  
  
print_newline:
  mov eax, 0              ; print new line
  int 0x40                ; console system call
  ret
  
print_char:
  mov eax, 4              ; print char
  mov ebx, 43             ; ASCII "+"
  int 0x40                ; console system call
  ret
  
  
exit:
  mov eax, 3              ; print until 0
  mov ebx, .str           ; mem-address of 'str' variable
  int 0x40                ; console system call
