.data
	n:	.word	5
.text
main:
	addi 	$s0, $0, 1	# f = 1
	lw	$a0, n
LOOP:	mult	$s0, $a0	# f = f * n
	mflo	$s0	
	addi 	$a0, $a0, -1	# n = n - 1
	bgtz 	$a0, LOOP 
	sw	$s0, 0x10
