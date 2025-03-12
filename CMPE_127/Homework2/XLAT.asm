; Homework 2 Problem 43

; Write a short program that uses the XLAT instruction to convert the BCD numbers 0–9 into
; ASCII-coded numbers 30H–39H. Store the ASCII-coded data in a TABLE located within
; the data segment.

.386
.model flat, stdcall
ExitProcess proto,dwExitCode:dword

.data
	TABLE DB 30H, 31H, 32H, 33H, 34H, 35H, 36H, 37H, 38H, 39H

.code
main proc
	
	MOV AL, 03H			; BCD of 3
	LEA EBX, TABLE		; Loads address of Table
	XLAT				; Should store 33H in AL

	INVOKE ExitProcess, 0

main endp
end main