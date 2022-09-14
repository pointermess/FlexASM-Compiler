section .data
  xlimit: db 0x40
  ylimit: db 0x20

section .text

main:
  mov eax, 0
loop_x:

  mov ebx, 0

loop_y:
  add ebx, 1
  dbg ebx
  mov ecx, BYTE [.ylimit]
  cmp ebx, ecx
  jl @loop_y


  add eax, 1
  mov ecx, BYTE [.xlimit]
  cmp eax, ecx
  jne @loop_x

 
exit:
