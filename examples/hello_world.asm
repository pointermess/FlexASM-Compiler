section .data
  helloWorldStr: db 'Hello World!', 0

section .text
  mov eax, 3
  mov ebx, [helloWorldStr]
  int 0x40
