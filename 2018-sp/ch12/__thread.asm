GAS LISTING /tmp/ccwt2Gyp.s 			page 1


   1              		.file	"__thread.c"
   2              		.globl	global
   3              		.bss
   4              		.align 4
   7              	global:
   8 0000 00000000 		.zero	4
   9              		.comm	mutex,40,32
  10              		.globl	thread_local
  11              		.section	.tbss,"awT",@nobits
  12              		.align 4
  15              	thread_local:
  16 0000 00000000 		.zero	4
  17              		.section	.rodata
  18              	.LC0:
  19 0000 40746872 		.string	"@thread_local = %p\n"
  19      6561645F 
  19      6C6F6361 
  19      6C203D20 
  19      25700A00 
  20              		.text
  21              		.globl	thread
  23              	thread:
  24              	.LFB2:
  25              		.cfi_startproc
  26 0000 55       		pushq	%rbp
  27              		.cfi_def_cfa_offset 16
  28              		.cfi_offset 6, -16
  29 0001 4889E5   		movq	%rsp, %rbp
  30              		.cfi_def_cfa_register 6
  31 0004 4883EC10 		subq	$16, %rsp
  32 0008 C745FC00 		movl	$0, -4(%rbp)
  32      000000
  33 000f EB17     		jmp	.L2
  34              	.L3:
  35 0011 648B0425 		movl	%fs:thread_local@tpoff, %eax
  35      00000000 
  36 0019 83C001   		addl	$1, %eax
  37 001c 64890425 		movl	%eax, %fs:thread_local@tpoff
  37      00000000 
  38 0024 8345FC01 		addl	$1, -4(%rbp)
  39              	.L2:
  40 0028 817DFCFF 		cmpl	$999999999, -4(%rbp)
  40      C99A3B
  41 002f 7EE0     		jle	.L3
  42 0031 64488B04 		movq	%fs:0, %rax
  42      25000000 
  42      00
  43 003a 48050000 		addq	$thread_local@tpoff, %rax
  43      0000
  44 0040 4889C6   		movq	%rax, %rsi
  45 0043 BF000000 		movl	$.LC0, %edi
  45      00
  46 0048 B8000000 		movl	$0, %eax
  46      00
  47 004d E8000000 		call	printf
  47      00
  48 0052 BF000000 		movl	$mutex, %edi
GAS LISTING /tmp/ccwt2Gyp.s 			page 2


  48      00
  49 0057 E8000000 		call	pthread_mutex_lock
  49      00
  50 005c 8B150000 		movl	global(%rip), %edx
  50      0000
  51 0062 648B0425 		movl	%fs:thread_local@tpoff, %eax
  51      00000000 
  52 006a 01D0     		addl	%edx, %eax
  53 006c 89050000 		movl	%eax, global(%rip)
  53      0000
  54 0072 BF000000 		movl	$mutex, %edi
  54      00
  55 0077 E8000000 		call	pthread_mutex_unlock
  55      00
  56 007c 90       		nop
  57 007d C9       		leave
  58              		.cfi_def_cfa 7, 8
  59 007e C3       		ret
  60              		.cfi_endproc
  61              	.LFE2:
  63              		.section	.rodata
  64              	.LC1:
  65 0014 31303030 		.string	"1000000000+1000000000 = %d\n"
  65      30303030 
  65      30302B31 
  65      30303030 
  65      30303030 
  66              		.text
  67              		.globl	main
  69              	main:
  70              	.LFB3:
  71              		.cfi_startproc
  72 007f 55       		pushq	%rbp
  73              		.cfi_def_cfa_offset 16
  74              		.cfi_offset 6, -16
  75 0080 4889E5   		movq	%rsp, %rbp
  76              		.cfi_def_cfa_register 6
  77 0083 4883EC20 		subq	$32, %rsp
  78 0087 64488B04 		movq	%fs:40, %rax
  78      25280000 
  78      00
  79 0090 488945F8 		movq	%rax, -8(%rbp)
  80 0094 31C0     		xorl	%eax, %eax
  81 0096 BE000000 		movl	$0, %esi
  81      00
  82 009b BF000000 		movl	$mutex, %edi
  82      00
  83 00a0 E8000000 		call	pthread_mutex_init
  83      00
  84 00a5 488D45E8 		leaq	-24(%rbp), %rax
  85 00a9 B9000000 		movl	$0, %ecx
  85      00
  86 00ae BA000000 		movl	$thread, %edx
  86      00
  87 00b3 BE000000 		movl	$0, %esi
  87      00
  88 00b8 4889C7   		movq	%rax, %rdi
GAS LISTING /tmp/ccwt2Gyp.s 			page 3


  89 00bb E8000000 		call	pthread_create
  89      00
  90 00c0 488D45F0 		leaq	-16(%rbp), %rax
  91 00c4 B9000000 		movl	$0, %ecx
  91      00
  92 00c9 BA000000 		movl	$thread, %edx
  92      00
  93 00ce BE000000 		movl	$0, %esi
  93      00
  94 00d3 4889C7   		movq	%rax, %rdi
  95 00d6 E8000000 		call	pthread_create
  95      00
  96 00db 488B45E8 		movq	-24(%rbp), %rax
  97 00df BE000000 		movl	$0, %esi
  97      00
  98 00e4 4889C7   		movq	%rax, %rdi
  99 00e7 E8000000 		call	pthread_join
  99      00
 100 00ec 488B45F0 		movq	-16(%rbp), %rax
 101 00f0 BE000000 		movl	$0, %esi
 101      00
 102 00f5 4889C7   		movq	%rax, %rdi
 103 00f8 E8000000 		call	pthread_join
 103      00
 104 00fd 8B050000 		movl	global(%rip), %eax
 104      0000
 105 0103 89C6     		movl	%eax, %esi
 106 0105 BF000000 		movl	$.LC1, %edi
 106      00
 107 010a B8000000 		movl	$0, %eax
 107      00
 108 010f E8000000 		call	printf
 108      00
 109 0114 B8000000 		movl	$0, %eax
 109      00
 110 0119 488B55F8 		movq	-8(%rbp), %rdx
 111 011d 64483314 		xorq	%fs:40, %rdx
 111      25280000 
 111      00
 112 0126 7405     		je	.L6
 113 0128 E8000000 		call	__stack_chk_fail
 113      00
 114              	.L6:
 115 012d C9       		leave
 116              		.cfi_def_cfa 7, 8
 117 012e C3       		ret
 118              		.cfi_endproc
 119              	.LFE3:
 121              		.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
 122              		.section	.note.GNU-stack,"",@progbits
GAS LISTING /tmp/ccwt2Gyp.s 			page 4


DEFINED SYMBOLS
                            *ABS*:0000000000000000 __thread.c
     /tmp/ccwt2Gyp.s:7      .bss:0000000000000000 global
                            *COM*:0000000000000028 mutex
     /tmp/ccwt2Gyp.s:15     .tbss:0000000000000000 thread_local
     /tmp/ccwt2Gyp.s:23     .text:0000000000000000 thread
     /tmp/ccwt2Gyp.s:69     .text:000000000000007f main

UNDEFINED SYMBOLS
_GLOBAL_OFFSET_TABLE_
printf
pthread_mutex_lock
pthread_mutex_unlock
pthread_mutex_init
pthread_create
pthread_join
__stack_chk_fail
