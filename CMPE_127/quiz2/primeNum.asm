; Quiz 2
; Program that will check if each number in the array is prime or not
; Ethan Ho 017157582

.386
.model flat, stdcall
ExitProcess proto,dwExitCode:dword
.data
    numbers WORD    17, 6, 4, 23, 11
    result  WORD    ?, ?, ?, ?, ?
.code
main proc
    
    mov ecx, lengthof numbers       ; length of numbers
    mov esi, 0                      ; set i = 0
next:                               ; now we will iterate through each of the nums in the arr
    mov eax, 0                      ; clear eax
    mov ebx, 0                      ; clear ebx
    mov ax, [numbers + esi]         ; ax = numbers[i]
    mov bx, 2                       ; loading 2 to increment upto ax
division:
    mov edx, 0                      ; clearing edx for division
    div bx                          ; ax/bx
    cmp dx, 0                       ; check if there is a remainder
    je not_prime                    ; jump if NO remainder
    mov ax, [numbers+esi]           ; put the num[i] back in ax to check again
    inc bx                          ; bx += 1
    cmp bx, ax                      ; check if equal
    je is_prime                     ; it is a prime if no divisors
    jmp division                    ; if not equal then keep checking for prime num
is_prime:
    mov [result+esi], 1             ; if equal than prime, result[i] = 1
    jmp done                        ; jump to next num
not_prime:
    mov [result+esi], 0             ; result[i] = 0
done:
    add esi, 2                      ; i += 2
    loop next                       ; while ecx > 0
    Invoke ExitProcess, 0
main endp
end main