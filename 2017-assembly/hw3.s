	.section .text
	.global main
	.type main, %function
main:
    MOV r0, #100            @ assign a number to r0
    AND r1, r0, #0xff       @ r1 := r0[7:0]
    MOV r2, r0, LSR #8      @ r2 := r0 >> 8
    AND r2, r2, #0xff       @ r2 := r2[7:0]
    MOV r3, r0, LSR #18     @ r3 := r0 >> 18
    BIC r3, r3, #0x2000     @ r3 := r3[12:0]
	nop
	.end
