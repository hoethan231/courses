; Lab 2 Intro to Status Flags

.386
.model flat, stdcall
ExitProcess proto,dwExitCode:dword

.code
main proc

	;Example 1
	mov al, 10
	mov bl, 9
	sub bl, al

	;Example 2
	mov al, 100
	mov bl, 50
	add al, bl

	;Example 3
	mov al, 50
	mov bl, 50
	cmp al, bl
	sub al, bl
	cmp al,bl

	;Example 4
	mov al, 39h
	mov bl, 2bh
	add al, bl

	;Example 5
	mov al, 1
	mov bl, 1
	add bl, al
	add bl, al

	;Example 6
	mov al, 0ffh
	mov bl, 1h
	add al, bl
	mov al, 10
	mov bl, 9
	sub bl, al

main endp
end main