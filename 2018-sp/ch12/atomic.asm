GAS LISTING /tmp/ccFj7Jct.s 			page 1


   1              		.file	"atomic.c"
   2              		.text
   3              	.Ltext0:
   4              		.globl	global
   5              		.bss
   6              		.align 4
   9              	global:
  10 0000 00000000 		.zero	4
  11              		.text
  12              		.globl	thread
  14              	thread:
  15              	.LFB2:
  16              		.file 1 "atomic.c"
   1:atomic.c      **** #include <stdio.h>
   2:atomic.c      **** #include <pthread.h>
   3:atomic.c      **** #include <stdatomic.h>
   4:atomic.c      **** 
   5:atomic.c      **** atomic_int global=0;
   6:atomic.c      **** 
   7:atomic.c      **** void thread(void) {
  17              		.loc 1 7 0
  18              		.cfi_startproc
  19 0000 55       		pushq	%rbp
  20              		.cfi_def_cfa_offset 16
  21              		.cfi_offset 6, -16
  22 0001 4889E5   		movq	%rsp, %rbp
  23              		.cfi_def_cfa_register 6
   8:atomic.c      **** 	int i;
   9:atomic.c      **** 	for (i=0; i<1000000; i++)
  24              		.loc 1 9 0
  25 0004 C745FC00 		movl	$0, -4(%rbp)
  25      000000
  26 000b EB0C     		jmp	.L2
  27              	.L3:
  10:atomic.c      **** 		atomic_fetch_add(&global, 1);
  28              		.loc 1 10 0 discriminator 3
  29 000d F0830500 		lock addl	$1, global(%rip)
  29      00000001 
   9:atomic.c      **** 		atomic_fetch_add(&global, 1);
  30              		.loc 1 9 0 discriminator 3
  31 0015 8345FC01 		addl	$1, -4(%rbp)
  32              	.L2:
   9:atomic.c      **** 		atomic_fetch_add(&global, 1);
  33              		.loc 1 9 0 is_stmt 0 discriminator 1
  34 0019 817DFC3F 		cmpl	$999999, -4(%rbp)
  34      420F00
  35 0020 7EEB     		jle	.L3
  11:atomic.c      **** }
  36              		.loc 1 11 0 is_stmt 1
  37 0022 90       		nop
  38 0023 5D       		popq	%rbp
  39              		.cfi_def_cfa 7, 8
  40 0024 C3       		ret
  41              		.cfi_endproc
  42              	.LFE2:
  44              		.section	.rodata
  45              	.LC0:
GAS LISTING /tmp/ccFj7Jct.s 			page 2


  46 0000 31303030 		.string	"1000000+1000000 = %d\n"
  46      3030302B 
  46      31303030 
  46      30303020 
  46      3D202564 
  47              		.text
  48              		.globl	main
  50              	main:
  51              	.LFB3:
  12:atomic.c      **** 
  13:atomic.c      **** int main(void) {
  52              		.loc 1 13 0
  53              		.cfi_startproc
  54 0025 55       		pushq	%rbp
  55              		.cfi_def_cfa_offset 16
  56              		.cfi_offset 6, -16
  57 0026 4889E5   		movq	%rsp, %rbp
  58              		.cfi_def_cfa_register 6
  59 0029 4883EC20 		subq	$32, %rsp
  60              		.loc 1 13 0
  61 002d 64488B04 		movq	%fs:40, %rax
  61      25280000 
  61      00
  62 0036 488945F8 		movq	%rax, -8(%rbp)
  63 003a 31C0     		xorl	%eax, %eax
  14:atomic.c      **** 	pthread_t id1, id2;
  15:atomic.c      **** 	pthread_create(&id1,NULL,(void *) thread,NULL);
  64              		.loc 1 15 0
  65 003c 488D45E8 		leaq	-24(%rbp), %rax
  66 0040 B9000000 		movl	$0, %ecx
  66      00
  67 0045 BA000000 		movl	$thread, %edx
  67      00
  68 004a BE000000 		movl	$0, %esi
  68      00
  69 004f 4889C7   		movq	%rax, %rdi
  70 0052 E8000000 		call	pthread_create
  70      00
  16:atomic.c      **** 	pthread_create(&id2,NULL,(void *) thread,NULL);
  71              		.loc 1 16 0
  72 0057 488D45F0 		leaq	-16(%rbp), %rax
  73 005b B9000000 		movl	$0, %ecx
  73      00
  74 0060 BA000000 		movl	$thread, %edx
  74      00
  75 0065 BE000000 		movl	$0, %esi
  75      00
  76 006a 4889C7   		movq	%rax, %rdi
  77 006d E8000000 		call	pthread_create
  77      00
  17:atomic.c      **** 	pthread_join(id1,NULL);
  78              		.loc 1 17 0
  79 0072 488B45E8 		movq	-24(%rbp), %rax
  80 0076 BE000000 		movl	$0, %esi
  80      00
  81 007b 4889C7   		movq	%rax, %rdi
  82 007e E8000000 		call	pthread_join
GAS LISTING /tmp/ccFj7Jct.s 			page 3


  82      00
  18:atomic.c      **** 	pthread_join(id2,NULL);
  83              		.loc 1 18 0
  84 0083 488B45F0 		movq	-16(%rbp), %rax
  85 0087 BE000000 		movl	$0, %esi
  85      00
  86 008c 4889C7   		movq	%rax, %rdi
  87 008f E8000000 		call	pthread_join
  87      00
  19:atomic.c      **** 	printf("1000000+1000000 = %d\n", global);
  88              		.loc 1 19 0
  89 0094 8B050000 		movl	global(%rip), %eax
  89      0000
  90 009a 8945E4   		movl	%eax, -28(%rbp)
  91 009d 8B45E4   		movl	-28(%rbp), %eax
  92 00a0 89C6     		movl	%eax, %esi
  93 00a2 BF000000 		movl	$.LC0, %edi
  93      00
  94 00a7 B8000000 		movl	$0, %eax
  94      00
  95 00ac E8000000 		call	printf
  95      00
  20:atomic.c      **** 	return (0);
  96              		.loc 1 20 0
  97 00b1 B8000000 		movl	$0, %eax
  97      00
  21:atomic.c      **** }
  98              		.loc 1 21 0
  99 00b6 488B55F8 		movq	-8(%rbp), %rdx
 100 00ba 64483314 		xorq	%fs:40, %rdx
 100      25280000 
 100      00
 101 00c3 7405     		je	.L6
 102 00c5 E8000000 		call	__stack_chk_fail
 102      00
 103              	.L6:
 104 00ca C9       		leave
 105              		.cfi_def_cfa 7, 8
 106 00cb C3       		ret
 107              		.cfi_endproc
 108              	.LFE3:
 110              	.Letext0:
 111              		.file 2 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h"
GAS LISTING /tmp/ccFj7Jct.s 			page 4


DEFINED SYMBOLS
                            *ABS*:0000000000000000 atomic.c
     /tmp/ccFj7Jct.s:9      .bss:0000000000000000 global
     /tmp/ccFj7Jct.s:14     .text:0000000000000000 thread
     /tmp/ccFj7Jct.s:50     .text:0000000000000025 main

UNDEFINED SYMBOLS
pthread_create
pthread_join
printf
__stack_chk_fail
