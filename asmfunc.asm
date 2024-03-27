; Declare Memory Data
section .data
	sdot dd 0.0



; Setup Environment
section .text
	bits 64
	default rel		; to handle address relocation
	global asmDotProduct



; Dot Product Function in x86_64 Assembly
asmDotProduct:

	MOVSS XMM4, [sdot]

	L1:
		DEC RCX

		MOVSS XMM1, [RDX + RCX * 4]
		MOVSS XMM2, [R8 + RCX * 4]
		VMULSS XMM3, XMM1, XMM2

		ADDSS XMM4, XMM3

		INC RCX
		LOOP L1

	MOVSS [sdot], XMM4
	MOVSS XMM0, [sdot]
	
	ret