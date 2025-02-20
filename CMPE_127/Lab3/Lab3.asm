; Lab 3 Introduction to Addressing Modes

.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data

sum WORD ?
var1 WORD 5

.code
main proc

	MOV AX, 0FFFFh
	MOV BX, 7h
	ADD AX, BX

	LEA EBX, var1
	MOV AX, [EBX]

	MOV ESI, OFFSET sum
	MOV BX, [ESI + 02]

	LEA EBX, sum
	MOV ESI, 02
	MOV CX, [EBX + ESI]

	invoke ExitProcess, 0

main endp
end main