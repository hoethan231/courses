; Lab 9 Palindrome	
; Check whether a string is a palindrome or not

.386
.model flat, stdcall
ExitProcess proto,dwExitCode:dword
include Irvine32.inc

.data
	mymsg		byte	"level", 0
	reversemsg	byte lengthof mymsg DUP (0)
	isPal		byte    "The string is a palindrome.",0
    notPal	    byte    "The string is NOT a palindrome.",0

.code
main proc
	; Push original message into stack
	mov edx, offset mymsg
	call WriteString
	mov ebx, offset mymsg
	mov esi, 0
	mov ecx, lengthof mymsg

	push_next:
		mov eax, 0
		mov al, [ebx+esi]
		push ax
		inc esi
		loop push_next

	mov ebx, offset reversemsg
	mov ecx, lengthof mymsg - 1
	mov esi, 0

	; Pop message out of stack for reverse
	pop_next:
		pop ax
		mov [ebx+esi], al
		inc esi
		loop pop_next

    mov ecx, lengthof mymsg - 1
    mov esi, offset mymsg
    mov edi, offset reversemsg

compare_loop:
    mov al, [esi]
    mov bl, [edi]
    cmp al, bl
    je not_palindrome
    inc esi
    inc edi
    loop compare_loop

    ; If all characters matched
    mov edx, offset isPal
    call WriteString
    jmp done
	
	; If not matches
	not_palindrome:
		mov edx, offset notPal
		call WriteString

	done:
		Invoke ExitProcess, 0

main endp
end main