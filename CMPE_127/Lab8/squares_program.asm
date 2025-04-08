; Lab 8
; You have given an array of numbers. Find square of each number and store it in result array.

.386
.model flat, stdcall
ExitProcess proto,dwExitCode:dword

.data
numbers		DW		2, 4, 3, 7
result		DW		4 DUP (0)

.code
squares_program proc
	
	MOV ECX, 4						; arr.length
	MOV ESI, 0						; i = 0
	outer_loop:
		MOV AX, 0					; sum = 0
		MOV BX, [numbers+ESI]		; num = numbers[i]
		MOV DX, [numbers+ESI]		; j = numbers[i]
		inner_loop:
			ADD AX, BX				; sum += num
			DEC DX					; j -= 1
			CMP DX, 0
			JNZ inner_loop
		MOV [result+ESI], AX		; result[i] = sum
		ADD ESI, 2					; i += 1
		LOOP outer_loop

	Invoke ExitProcess, 0

squares_program endp
end squares_program