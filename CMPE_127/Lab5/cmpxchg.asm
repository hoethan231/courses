; Lab 5 Arithetic Instrctions

.686p
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword


.code
main proc
	
	MOV AL, 5
	MOV CL, 5
	MOV DL, 1
	CMPXCHG CL, DL
	CMPXCHG CL, DL

	invoke ExitProcess, 0

main endp
end main