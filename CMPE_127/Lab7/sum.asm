; Lab 7 Arrays
; Even or Odd Sum Program

.386
.model flat, stdcall
ExitProcess proto,dwExitCode:dword

.data
	arr			DW	34, 45, 56, 67, 75, 89
	even_sum	DW	?
	odd_sum		DW	?

.code
even_odd_program proc
	MOV ECX, 6						; i = arr.size
	MOV ESI, 0						; j = 0


loopp:
	MOV AX, [arr + ESI]				; eax = arr[i]
	TEST [arr + ESI], 1b			; check the last bit whether its 1 or 0
	JZ even_num						; jump if even

	odd_num:
		ADD odd_sum, AX				; odd_sum += arr[i]
		JMP done					; skip even label

	even_num:
		ADD even_sum, AX			; odd_sum += arr[i]

	done:
		ADD ESI, 2					; j += 1
		LOOP loopp
	Invoke ExitProcess, 0

even_odd_program endp
end even_odd_program