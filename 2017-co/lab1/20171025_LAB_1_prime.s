.data
msgb : .asciiz "\nnearest prime number is:  "
input : .asciiz "pls enter a number : **** user input :  "
.text
.globl main
main :
		#Iinput number
		li      $v0, 4 			# load syscall code (4 : print string)
		la      $a0, input		        # load address of string to be printed into $a0
		syscall				# print str
		li      $v0, 5			# load syscall code (5 : read int)
		syscall				# read int
		add     $t1, $zero, $v0
		addi    $t2, $zero, 1
init:	add     $t3, $zero, $t1
incr:	add     $t3, $t3, $t2		# add 1 (or -1) to t3

		# the section checks if t3 is a prime.
		addi    $t4, $zero, 2
checkf:	div     $t3, $t4
		mfhi    $t5
		beq     $t5, $zero, incr		# if not prime, go back to incr
		addi    $t4, $t4, 1
		mul     $t6, $t4, $t4
		ble     $t6, $t3, checkf		# if there are factors to be checked, go to checkf

		# if it's prime...
		li      $v0, 4
		la      $a0, msgb
		syscall
		add     $a0,$zero $t3
		li      $v0, 1
		syscall
		addi    $t2, $t2, -2
		beq     $t2, -1, init		# if B is not found, go to initial state
		li      $v0, 10
		syscall
