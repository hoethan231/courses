; Lab 5 Arithetic Instrctions

.686p
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword


.code
main2 proc
	
	MOV AL, 05h
	MOV BL, 05h
	ADD AL, BL
	DAA

	MOV AL, 20h
	MOV BL, 05h
	SUB AL, BL
	DAS

	MOV AL, 35h
	MOV BL, 32h
	ADD AL, BL
	AAA

	MOV AL, 38h
	MOV BL, 32h
	SUB AL, BL
	AAS

	MOV AL, 32h
	MOV BL, 38h
	SUB AL, BL
	AAS

	MOV AL, 11d
	MOV BL, 03d
	MUL BL
	AAM

	MOV AX, 0408h
	MOV BL, 04h
	AAD
	DIV BL
	DAA

	invoke ExitProcess, 0

main2 endp
end main2