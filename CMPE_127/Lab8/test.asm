; Lab 8
; You have given an array of numbers. Find factorial of each number and store it in result array.

.386
.model flat, stdcall
ExitProcess proto, dwExitCode:dword

.data
	numbers		DW		2, 4, 3, 7
	result		DW		4 DUP (0)
	sizee		DW		4

.code
	factorial_program proc
	
		MOV CX, [sizee]					; size
		MOV ESI, 0						; i = 0
		outer_loop:
			MOV AX, 1					; sum = 1
			MOV BX, [numbers+ESI]		; num = numbers[i]
			inner_loop:
				MUL BX
				DEC BX
				JNZ inner_loop			; loop if num > 0
			MOV [result+ESI], AX		; result[i] = sum
			ADD ESI, 2					; i += 1
			LOOP outer_loop

		INVOKE ExitProcess, 0

factorial_program endp
end factorial_program