section .data
  helloWorldStr: db 'Hello World!', 0

section .text
main:
  mov eax, 3
  mov ebx, [.helloWorldStr]
  int 0x40
