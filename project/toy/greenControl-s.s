	.arch msp430g2553
	.p2align 1,0
	.text


	.global ledControl
	.extern P1OUT

ledControl:
	cmp #0, r12            ; Compare the value in register r12 with 0
	jz off                 ; If the comparison result is zero (r12 equals 0), jump to off label
	bis #64, &P1OUT        ; Bitwise OR operation: Set bit 6 of the P1OUT register (turn on LED)
	pop r0                 ; Pop the return address from the stack into register r0
off:                      ; Label indicating where to jump if r12 equals 0
	and #~64, &P1OUT       ; Bitwise AND operation with complement: Clear bit 6 of the P1OUT register (turn off LED)
	pop r0                 ; Pop the return address from the stack into register r0
