; Lab 7 Arrays 
; Copy the contents of one array to another

.386
.model flat, stdcall
ExitProcess proto,dwExitCode:dword

.data
	arr1	DW	34, 45, 56, 67, 75, 89
	arr2	DW	6 DUP (0)

.code
array_program proc
	MOV ECX, 6				; Size of arr
	MOV ESI, 0				; Index

next:
	MOV AX, [arr1 + ESI]	; Save arr1[i]
	MOV [arr2 + ESI], AX	; arr2[i] = arr1[i]
	ADD ESI, 2				; i += 1
	LOOP next

	Invoke ExitProcess, 0

array_program endp
end array_program