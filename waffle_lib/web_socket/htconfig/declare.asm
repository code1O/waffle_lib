
section .text
  .global sum_two_nums
  .global prod_two_nums


sum_two_nums:
  
  mov rax, rdi
  mov rbx, rsi

  add rax, rbx
  ret

