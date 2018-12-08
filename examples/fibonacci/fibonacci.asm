section .data
  nTimes: db 8 ; repeats the fibonacci sequence 8 times
  temp:   db 0 ; temporary variable
  
section .text
main:
  mov eax, 0 ; term 1
  mov ebx, 1 ; term 2
  mov edx, 0 ; loop counter
  
loop_begin:
  dbg eax ; print current term
  
  mov [.temp], eax
  mov eax, ebx
  mov ebx, [.temp]
  add ebx, eax
  
  add edx, 1

  mov ecx, [.nTimes]
  cmp edx, ecx
  jl @loop_begin
