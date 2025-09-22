main:
	ori 	$a0, $0, 0x8000
	ori 	$a1, $0, 0x00A9
	addi 	$s0, $0, 1974
	mult 	$a0, $a0		# a * a
	mflo 	$s1			# x = a * a
	sw 	$s1, 0x20($0)		# [0x20] = x
	mult	$a1, $s1		# x * b
	mflo	$s2			# y = x * b
	sw	$s2, 0x24($0)		# [0x24] = y
	mfhi	$s3
	sw	$s3, 0x28($0)
	sll 	$t2, $s3, 16     	# t2 = HI << 16
	srl	$t4, $s2, 16     	# t4 = LO >> 16
	or  	$s2, $t2, $t4    	# y = y >> 16      	
	div	$s2, $s0		# y / c
	mflo	$t3
	add	$t3, $s0, $t3		# c + y / c
	srl	$s0, $t3, 1		# c = (c + y/c) / 2
	sw	$s0, 0x2C($0)		# [0x2C] = $s0
	addi	$t1, $0, 1665		# 1665
WHILE: 	div	$s2, $s0		# y / c
	mflo	$t0
	add	$t0, $s0, $t0		# c + y / c
	srl	$s0, $t0, 1		# c = (c + y/c) / 2
	bge	$s0, $t1, WHILE		# while c >= 1665
	sll	$s0, $s0, 8			# c = c >> 0
	sw	$s0, 0x30($0)		# [0x30] = c