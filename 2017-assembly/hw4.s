/* ========================= */
/*       DATA section        */
/* ========================= */
	.data
	.align 4

/* --- variable a --- */
	.type a, %object
	.size a, 40
a:
	.word 1
	.word 2
	.word 3
	.word 4
	.word 5
	.word 6
	.word 7
	.word 8
	.word 9
	.word 10

/* --- variable b --- */
	.type b, %object
	.size b, 40
b:
	.word 10
	.word 9
	.word 8
	.word 7
	.word 6
	.word 5
	.word 4
	.word 3
	.word 2
	.word 1

c:
	.space 16, 0

/* ========================= */
/*       TEXT section        */
/* ========================= */
	.section .text
	.global main
	.type main,%function
.matrixa:
	.word a
.matrixb:
    .word b
.matrixc:
    .word c

main:
    MOV     r1, #0              @ let {r1,r2,r3,r4} be C[2][2]
    MOV     r2, #0
    MOV     r3, #0
    MOV     r4, #0

	LDR     r9, .matrixa        @ let r9 be the address of a[0][0]
    ADD     r10, r9, #20        @ let r10 be the address of a[1][0]
    LDR     r11, .matrixb       @ let r11 be the address of b[0][0]
    MOV     r12, #5             @ set countdown = 5

.LABEL1:
    LDR     r5, [r9], #4        @ load a[0][i], a[1][i] into r5, r6
    LDR     r6, [r10], #4
    LDMIA   r11!, {r7, r8}      @ load b[i][0], b[i][1] into r7, r8
    MLA     r1, r5, r7, r1      @ multiply these elements and add to matrix c
    MLA     r2, r5, r8, r2
    MLA     r3, r6, r7, r3
    MLA     r4, r6, r8, r4
    SUB     r12 , r12, #1       @ countdown--
    CMP     r12, #0
    BNE     .LABEL1

    LDR     r0, .matrixc        @ let r0 be the address of c
    STMIA   r0, {r1, r2, r3, r4}
    MOV     r1, r0              @ move the address to r1

        nop

