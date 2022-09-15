section .data

section .text

main:
  ; push variables
  push 0x2f ; current number  = esp-8
  push 0    ; current x value = esp-4
  push 0    ; current y value = esp
  
  
loop_num:
  call @cls

  ; handle number
  mov ebx, [esp-8] ; load current ascii value into ebx
  add ebx, 1       ; increase ascii value
  cmp ebx, 0x3a    ; compare if ascii value is over 40
  mov [esp-8], ebx ; load current ascii value into ebx
  je @exit         ; if end reached, jump exit
  
  ; init y
  mov ecx, 0
  mov [esp], ecx
  
  

loop_char:
  call @print_char

  mov ecx, [esp-4]
  add ecx, 1
  mov [esp-4], ecx
  cmp ecx, 0x40
  jl @loop_char
  
  
  mov ecx, 0
  mov [esp-4], ecx
  call @print_newline
  
  mov ecx, [esp]
  add ecx, 1
  cmp ecx, 0x8
  mov [esp], ecx
  jl @loop_char
  
  call @sleep
  jmp @loop_num
  
  
print_newline:
  mov eax, 0              ; print new line
  int 0x40                ; console system call
  ret
  
print_char:
  mov eax, 1              ; print char
  int 0x40                ; console system call
  ret
  
cls:
  mov eax, 9              ; clear console
  int 0x40                ; console system call  
  ret
  
sleep:
  mov eax, 0
  sleep_loop:
    add eax, 1
    cmp eax, 0xfffff
    jl @sleep_loop
  ret
  
exit:
