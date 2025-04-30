; Lab 9 Working with Stacks and Strings	
; A program that will print using Irvine perimeter of a circle given a radius

.386
.model flat, stdcall
ExitProcess proto,dwExitCode:dword
include Irvine32.inc

.data
	radius	real4	3.0
	pi		real4	3.14
	two		real4	2.0
	msg		BYTE	"The perimeter is: "
	output	real4	?

.code
perim proc
	
	fld two					; loads 2 into the stack
	fld pi					; loads pi as well
	fmul					; 2 * pi

	fld radius				; loads radius
	fmul					; raidus * (2*pi)
	fstp output				; saves result in perim

	mov edx, offset msg		; loads msg to print
	call WriteString

	fld output				; loads float
	call WriteFloat			; prints float

	Invoke ExitProcess, 0

perim endp
end perim