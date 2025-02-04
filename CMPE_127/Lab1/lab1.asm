a	WORD 9
sum	DWORD ?
diff DWORD ?

. code
main proc
	mov eax, 7
	add eax, 4
	mov sum, eax

	mov eax, 12345
	sub eax, 2
	mov diff, eax

	invoke ExitProcess, 0

main endp
end main