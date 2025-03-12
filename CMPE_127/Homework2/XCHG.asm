; Homework 2 Problem 49

; Develop a sequence of instructions that exchanges the contents of AX with BX, ECX with
; EDX, and SI with DI.

.386
.model flat, stdcall
ExitProcess proto,dwExitCode:dword

.code
main2 proc

	MOV AX, 1H
	MOV BX, 2H
	XCHG AX, BX

	MOV ECX, 3H
	MOV EDX, 4H
	XCHG ECX, EDX

	MOV SI, 5H
	MOV DI, 6H
	XCHG SI, DI

	INVOKE ExitProcess, 0

main2 endp
end main2