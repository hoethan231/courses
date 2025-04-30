; Quiz 2
; Program that will check if each number in the array(numbers) is prime or not.

.386
.model flat, stdcall
ExitProcess proto,dwExitCode:dword

.data
	numbers	WORD	17, 6, 4, 23, 11
	result	WORD	?, ?, ?, ?, ?

.code
main proc
	MOV ECX, 5				; Size of numbers
	MOV ESI, 0				; Index = 0

loopp:
	MOV AX, [numbers + ESI]	; Save arr1[i]
	




	ADD ESI, 2				; i += 1
	LOOP next

	Invoke ExitProcess, 0

main endp
end main