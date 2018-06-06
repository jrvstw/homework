    .data
    .align 4

    .type a, %object
    .size a, 32
    a:
    .word 1
    .word 10
    .word 6
    .word 3
    .word 20
    .word 40
    .word 9
    .word 8

    .section .text
    .global main
    .type main,%function
.addra:
    .word a

main:
    MOV ip, sp
    STMFD sp!, {fp, ip, lr, pc}
    SUB fp, ip, #4

    LDR r0, .addra    /* array address */
    MOV r1, #8    /* array size */

    STR r0, [sp, #-4]!
    STR r1, [sp, #-4]!

    bl NumSort

    LDMEA fp, {fp, sp, pc}
    .end
