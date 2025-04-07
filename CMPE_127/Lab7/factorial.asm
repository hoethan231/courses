; Lab 7 Arrays
; Factorial Program

.386
.model flat, stdcall
ExitProcess proto,dwExitCode:dword

.data
	fact	DW	0

.code
factorial_program proc
	MOV ECX, 5		; n = 5
	MOV AX, 1		; factorial = 1

factorial:
	MUL ECX			; factorial *= n
	LOOP factorial	; Loop until n == 0

	MOV fact, AX	; fact = factorial

	Invoke ExitProcess, 0

factorial_program endp
end factorial_program