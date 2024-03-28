; Declare Memory Data
section .data



; Setup Environment
section .text
	bits 64
	default rel		; to handle address relocation
	global asmDotProduct



; Dot Product Function in x86_64 Assembly
asmDotProduct:

	; Reset Values
	pxor XMM0, XMM0
	pxor XMM1, XMM1
	pxor XMM2, XMM2
	pxor XMM3, XMM3
	pxor XMM4, XMM4

	; Loop for each index
	L1:

		; Get each element of Vector A and B
		MOVSS XMM1, [RDX]
		MOVSS XMM2, [R8]

		; Multiply and add result to XXMM$
		VMULSS XMM3, XMM1, XMM2
		ADDSS XMM4, XMM3

		ADD RDX, 4
		ADD R8, 4

		LOOP L1

	; Put result into XMM0
	MOVSS XMM0, XMM4
	
	ret