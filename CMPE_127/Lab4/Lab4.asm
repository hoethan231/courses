; Lab 4 Introduction to Arithmetic and Logical Instructions

.386
.model flat, stdcall
ExitProcess proto,dwExitCode:dword

.data
	a			WORD	9
	b			WORD	5
	maskk		WORD	30
	x			WORD	2

	sum			WORD	?
	sub1		WORD	?
	product		WORD	?
	quotient	WORD	?
	remainder	WORD	?
	a_minus		WORD	?
	b_plus1		WORD	?
	a_and_maskk	WORD	?
	b_or_maskk	WORD	?
	a_shr_x		WORD	?
	b_shl_x		WORD	?
	a_ror_x		WORD	?
	b_rcl_x		WORD	?

.code
main proc

	MOV AX, a
	ADD AX, b
	MOV sum, AX				; Sum a+b

	MOV AX, a
	SUB AX, b
	MOV sub1, AX			; Sub a-b

	MOV AX, a
	MOV BX, b
	MUL BX
	MOV product, AX			; Mul a*b

	MOV AX, a
	MOV BX, b
	DIV BX
	MOV quotient, AX		; Div a/b
	MOV remainder, DX		; Mod a%b

	MOV AX, a
	NEG AX
	MOV a_minus, AX			; Neg -a

	MOV AX, b
	INC AX
	MOV b_plus1, AX			; Inc b++

	MOV AX, a
	AND AX, maskk
	MOV a_and_maskk, AX		; And a & maskk

	MOV AX, b
	OR AX, maskk
	MOV b_or_maskk, AX		; Or b | maskk

	MOV AX, a
	MOV CX, x
	SHR AX, CL
	MOV a_shr_x, AX			; Shift right a >> x

	MOV AX, b
	MOV CX, x
	SHL AX, CL
	MOV b_shl_x, AX			; Shift left b << x

	MOV AX, a
	MOV CX, x
	ROR AX, CL
	MOV a_ror_x, AX			; Rotate right a ror x

	MOV AX, b
	MOV CX, x
	RCL AX, CL
	MOV b_rcl_x, AX			; Rotate left b rcl x

main endp
end main
