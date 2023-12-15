	.arch msp430g2553
	.p2align 1,0
	.text

	.global redcontrol
	.extern P1OUT

redcontrol:
	cmp #0,r12
	jz off
	bis #1, &P1OUT
	pop r0
off:	and.b #~1, &P1OUT
	pop r0
