section .data
  helloWorldStr: db 'Hello World!', 0

section .text
main:
  mov eax, 3              ; print until 0
  mov ebx, .helloWorldStr ; address of 'helloWorldStr'
  int 0x40                ; console system call
