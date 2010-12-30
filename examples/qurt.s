	.file	"qurt.c"
	.file 1 "qurt.c"
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.text
.Ltext0:
	.align	2
	.global	main
	.type	main, %function
main:
.LFB3:
	.loc 1 4 0
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
.LCFI0:
	stmfd	sp!, {r4, fp, ip, lr, pc}
.LCFI1:
	sub	fp, ip, #4
.LCFI2:
	sub	sp, sp, #64
.LCFI3:
	.loc 1 8 0
.LBB2:
	adr	r3, .L2
	ldmia	r3, {r3-r4}
	str	r3, [fp, #-40]
	str	r4, [fp, #-36]
	.loc 1 9 0
	adr	r3, .L2+8
	ldmia	r3, {r3-r4}
	str	r3, [fp, #-32]
	str	r4, [fp, #-28]
	.loc 1 10 0
	adr	r3, .L2+16
	ldmia	r3, {r3-r4}
	str	r3, [fp, #-24]
	str	r4, [fp, #-20]
	.loc 1 11 0
	sub	r3, fp, #40
	sub	r2, fp, #56
	sub	ip, fp, #72
	mov	r0, r3
	mov	r1, r2
	mov	r2, ip
	bl	qurt
	mov	r3, r0
	str	r3, [fp, #-80]
	.loc 1 12 0
	ldr	r3, [fp, #-56]
	str	r3, [fp, #-76]
	.loc 1 14 0
	mov	r3, #0
	.loc 1 15 0
.LBE2:
	mov	r0, r3
	ldmea	fp, {r4, fp, sp, pc}
.L3:
	.align	2
.L2:
	.word	1073479680
	.word	0
	.word	-1073112679
	.word	-1717986918
	.word	1073977753
	.word	-1717986918
.LFE3:
	.size	main, .-main
	.align	2
	.global	fabs
	.type	fabs, %function
fabs:
.LFB5:
	.loc 1 18 0
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
.LCFI4:
	stmfd	sp!, {r4, fp, ip, lr, pc}
.LCFI5:
	sub	fp, ip, #4
.LCFI6:
	sub	sp, sp, #16
.LCFI7:
	str	r0, [fp, #-24]
	str	r1, [fp, #-20]
	.loc 1 21 0
.LBB3:
	ldfd	f0, [fp, #-24]
	cmfe	f0, #0
	bmi	.L6
	b	.L5
.L6:
	.loc 1 23 0
	ldfd	f0, [fp, #-24]
	mnfd	f0, f0
	stfd	f0, [fp, #-32]
	b	.L7
.L5:
	.loc 1 27 0
	sub	r3, fp, #24
	ldmia	r3, {r3-r4}
	str	r3, [fp, #-32]
	str	r4, [fp, #-28]
.L7:
	.loc 1 29 0
	sub	r3, fp, #32
	ldmia	r3, {r3-r4}
	.loc 1 30 0
.LBE3:
	stmfd	sp!, {r3, r4}
	ldfd	f0, [sp], #8
	ldmea	fp, {r4, fp, sp, pc}
.LFE5:
	.size	fabs, .-fabs
	.align	2
	.global	sqrt
	.type	sqrt, %function
sqrt:
.LFB7:
	.loc 1 33 0
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
.LCFI8:
	stmfd	sp!, {r4, fp, ip, lr, pc}
.LCFI9:
	sub	fp, ip, #4
.LCFI10:
	sub	sp, sp, #56
.LCFI11:
	str	r0, [fp, #-24]
	str	r1, [fp, #-20]
	.loc 1 34 0
.LBB4:
	ldfd	f0, [fp, #-24]
	dvfd	f0, f0, #10
	stfd	f0, [fp, #-32]
	.loc 1 37 0
	adr	r3, .L20
	ldmia	r3, {r3-r4}
	str	r3, [fp, #-56]
	str	r4, [fp, #-52]
	.loc 1 41 0
	mov	r3, #0
	str	r3, [fp, #-72]
	.loc 1 43 0
	ldfd	f0, [fp, #-24]
	cmf	f0, #0
	beq	.L10
	b	.L9
.L10:
	.loc 1 45 0
	adr	r3, .L20+8
	ldmia	r3, {r3-r4}
	str	r3, [fp, #-32]
	str	r4, [fp, #-28]
	b	.L11
.L9:
	.loc 1 50 0
	mov	r3, #1
	str	r3, [fp, #-68]
.L12:
	ldr	r3, [fp, #-68]
	cmp	r3, #19
	ble	.L15
	b	.L11
.L15:
	.loc 1 53 0
	ldr	r3, [fp, #-72]
	cmp	r3, #0
	beq	.L14
	.loc 1 55 0
	ldfd	f1, [fp, #-32]
	ldfd	f0, [fp, #-32]
	mufd	f1, f1, f0
	ldfd	f0, [fp, #-24]
	sufd	f1, f0, f1
	ldfd	f0, [fp, #-32]
	adfd	f0, f0, f0
	dvfd	f0, f1, f0
	stfd	f0, [fp, #-40]
	.loc 1 56 0
	ldfd	f1, [fp, #-32]
	ldfd	f0, [fp, #-40]
	adfd	f0, f1, f0
	stfd	f0, [fp, #-32]
	.loc 1 57 0
	ldfd	f1, [fp, #-32]
	ldfd	f0, [fp, #-32]
	mufd	f1, f1, f0
	ldfd	f0, [fp, #-24]
	sufd	f0, f0, f1
	stfd	f0, [fp, #-48]
	.loc 1 58 0
	sub	r0, fp, #48
	ldmia	r0, {r0-r1}
	bl	fabs
	stfd	f0, [sp, #-8]!
	ldmfd	sp!, {r3, r4}
	str	r3, [fp, #-64]
	str	r4, [fp, #-60]
	.loc 1 60 0
	ldfd	f1, [fp, #-64]
	ldfd	f0, [fp, #-56]
	cmfe	f1, f0
	bls	.L18
	b	.L14
.L18:
	.loc 1 62 0
	mov	r3, #1
	str	r3, [fp, #-72]
	.loc 1 50 0
.L14:
	ldr	r3, [fp, #-68]
	add	r3, r3, #1
	str	r3, [fp, #-68]
	b	.L12
.L11:
	.loc 1 71 0
	sub	r3, fp, #32
	ldmia	r3, {r3-r4}
	.loc 1 72 0
.LBE4:
	stmfd	sp!, {r3, r4}
	ldfd	f0, [sp], #8
	ldmea	fp, {r4, fp, sp, pc}
.L21:
	.align	2
.L20:
	.word	1055193269
	.word	-1998362383
	.word	0
	.word	0
.LFE7:
	.size	sqrt, .-sqrt
	.align	2
	.global	qurt
	.type	qurt, %function
qurt:
.LFB9:
	.loc 1 75 0
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
.LCFI12:
	stmfd	sp!, {r4, fp, ip, lr, pc}
.LCFI13:
	sub	fp, ip, #4
.LCFI14:
	sub	sp, sp, #48
.LCFI15:
	str	r0, [fp, #-20]
	str	r1, [fp, #-24]
	str	r2, [fp, #-28]
	.loc 1 77 0
.LBB5:
	mov	r3, #0
	str	r3, [fp, #-64]
	.loc 1 80 0
	ldr	r3, [fp, #-20]
	ldfd	f0, [r3, #0]
	cmf	f0, #0
	beq	.L24
	b	.L23
.L24:
	.loc 1 82 0
	ldr	r3, .L31+8
	str	r3, [fp, #-64]
.L23:
	.loc 1 84 0
	mov	r2, #8
	ldr	r3, [fp, #-20]
	add	r1, r2, r3
	mov	r2, #8
	ldr	r3, [fp, #-20]
	add	r3, r2, r3
	ldfd	f1, [r1, #0]
	ldfd	f0, [r3, #0]
	mufd	f2, f1, f0
	ldr	r3, [fp, #-20]
	ldfd	f0, [r3, #0]
	mufd	f1, f0, #4
	mov	r2, #16
	ldr	r3, [fp, #-20]
	add	r3, r2, r3
	ldfd	f0, [r3, #0]
	mufd	f0, f1, f0
	sufd	f0, f2, f0
	stfd	f0, [fp, #-36]
	.loc 1 85 0
	ldr	r3, [fp, #-20]
	ldfd	f0, [r3, #0]
	adfd	f0, f0, f0
	stfd	f0, [fp, #-44]
	.loc 1 86 0
	sub	r0, fp, #36
	ldmia	r0, {r0-r1}
	bl	fabs
	stfd	f0, [sp, #-8]!
	ldmfd	sp!, {r3, r4}
	str	r3, [fp, #-60]
	str	r4, [fp, #-56]
	.loc 1 87 0
	sub	r0, fp, #60
	ldmia	r0, {r0-r1}
	bl	sqrt
	stfd	f0, [sp, #-8]!
	ldmfd	sp!, {r3, r4}
	str	r3, [fp, #-52]
	str	r4, [fp, #-48]
	.loc 1 89 0
	ldfd	f0, [fp, #-36]
	cmfe	f0, #0
	bgt	.L26
	b	.L25
.L26:
	.loc 1 91 0
	ldr	r1, [fp, #-24]
	mov	r2, #8
	ldr	r3, [fp, #-20]
	add	r3, r2, r3
	ldfd	f1, [fp, #-52]
	ldfd	f0, [r3, #0]
	sufd	f1, f1, f0
	ldfd	f0, [fp, #-44]
	dvfd	f0, f1, f0
	stfd	f0, [r1, #0]
	.loc 1 92 0
	mov	r2, #8
	ldr	r3, [fp, #-24]
	add	r2, r2, r3
	adr	r3, .L31
	ldmia	r3, {r3-r4}
	stmia	r2, {r3-r4}	@ double
	.loc 1 93 0
	ldr	r1, [fp, #-28]
	mov	r2, #8
	ldr	r3, [fp, #-20]
	add	r3, r2, r3
	ldfd	f0, [r3, #0]
	mnfd	f1, f0
	ldfd	f0, [fp, #-52]
	sufd	f1, f1, f0
	ldfd	f0, [fp, #-44]
	dvfd	f0, f1, f0
	stfd	f0, [r1, #0]
	.loc 1 94 0
	mov	r2, #8
	ldr	r3, [fp, #-28]
	add	r2, r2, r3
	adr	r3, .L31
	ldmia	r3, {r3-r4}
	stmia	r2, {r3-r4}	@ double
	b	.L27
.L25:
	.loc 1 100 0
	ldfd	f0, [fp, #-36]
	cmf	f0, #0
	beq	.L29
	b	.L28
.L29:
	.loc 1 102 0
	ldr	r1, [fp, #-24]
	mov	r2, #8
	ldr	r3, [fp, #-20]
	add	r3, r2, r3
	ldfd	f0, [r3, #0]
	mnfd	f1, f0
	ldfd	f0, [fp, #-44]
	dvfd	f0, f1, f0
	stfd	f0, [r1, #0]
	.loc 1 103 0
	mov	r2, #8
	ldr	r3, [fp, #-24]
	add	r2, r2, r3
	adr	r3, .L31
	ldmia	r3, {r3-r4}
	stmia	r2, {r3-r4}	@ double
	.loc 1 104 0
	ldr	r2, [fp, #-28]
	ldr	r3, [fp, #-24]
	ldmia	r3, {r3-r4}	@ double
	stmia	r2, {r3-r4}	@ double
	.loc 1 105 0
	mov	r2, #8
	ldr	r3, [fp, #-28]
	add	r2, r2, r3
	adr	r3, .L31
	ldmia	r3, {r3-r4}
	stmia	r2, {r3-r4}	@ double
	b	.L27
.L28:
	.loc 1 109 0
	ldfd	f1, [fp, #-52]
	ldfd	f0, [fp, #-44]
	dvfd	f0, f1, f0
	stfd	f0, [fp, #-52]
	.loc 1 110 0
	ldr	r1, [fp, #-24]
	mov	r2, #8
	ldr	r3, [fp, #-20]
	add	r3, r2, r3
	ldfd	f0, [r3, #0]
	mnfd	f1, f0
	ldfd	f0, [fp, #-44]
	dvfd	f0, f1, f0
	stfd	f0, [r1, #0]
	.loc 1 111 0
	mov	r2, #8
	ldr	r3, [fp, #-24]
	add	r2, r2, r3
	sub	r3, fp, #52
	ldmia	r3, {r3-r4}
	stmia	r2, {r3-r4}	@ double
	.loc 1 112 0
	ldr	r2, [fp, #-28]
	ldr	r3, [fp, #-24]
	ldmia	r3, {r3-r4}	@ double
	stmia	r2, {r3-r4}	@ double
	.loc 1 113 0
	mov	r2, #8
	ldr	r3, [fp, #-28]
	add	r3, r2, r3
	ldfd	f0, [fp, #-52]
	mnfd	f0, f0
	stfd	f0, [r3, #0]
.L27:
	.loc 1 116 0
	ldr	r3, [fp, #-64]
	.loc 1 117 0
.LBE5:
	mov	r0, r3
	ldmea	fp, {r4, fp, sp, pc}
.L32:
	.align	2
.L31:
	.word	0
	.word	0
	.word	999
.LFE9:
	.size	qurt, .-qurt
	.section	.debug_frame,"",%progbits
.Lframe0:
	.4byte	.LECIE0-.LSCIE0
.LSCIE0:
	.4byte	0xffffffff
	.byte	0x1
	.ascii	"\000"
	.uleb128 0x1
	.sleb128 -4
	.byte	0xe
	.byte	0xc
	.uleb128 0xd
	.uleb128 0x0
	.align	2
.LECIE0:
.LSFDE0:
	.4byte	.LEFDE0-.LASFDE0
.LASFDE0:
	.4byte	.Lframe0
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.byte	0x4
	.4byte	.LCFI0-.LFB3
	.byte	0xd
	.uleb128 0xc
	.byte	0x4
	.4byte	.LCFI1-.LCFI0
	.byte	0x8e
	.uleb128 0x2
	.byte	0x8d
	.uleb128 0x3
	.byte	0x8b
	.uleb128 0x4
	.byte	0x84
	.uleb128 0x5
	.byte	0x4
	.4byte	.LCFI2-.LCFI1
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.byte	0x4
	.4byte	.LCFI4-.LFB5
	.byte	0xd
	.uleb128 0xc
	.byte	0x4
	.4byte	.LCFI5-.LCFI4
	.byte	0x8e
	.uleb128 0x2
	.byte	0x8d
	.uleb128 0x3
	.byte	0x8b
	.uleb128 0x4
	.byte	0x84
	.uleb128 0x5
	.byte	0x4
	.4byte	.LCFI6-.LCFI5
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE2:
.LSFDE4:
	.4byte	.LEFDE4-.LASFDE4
.LASFDE4:
	.4byte	.Lframe0
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.byte	0x4
	.4byte	.LCFI8-.LFB7
	.byte	0xd
	.uleb128 0xc
	.byte	0x4
	.4byte	.LCFI9-.LCFI8
	.byte	0x8e
	.uleb128 0x2
	.byte	0x8d
	.uleb128 0x3
	.byte	0x8b
	.uleb128 0x4
	.byte	0x84
	.uleb128 0x5
	.byte	0x4
	.4byte	.LCFI10-.LCFI9
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE4:
.LSFDE6:
	.4byte	.LEFDE6-.LASFDE6
.LASFDE6:
	.4byte	.Lframe0
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.byte	0x4
	.4byte	.LCFI12-.LFB9
	.byte	0xd
	.uleb128 0xc
	.byte	0x4
	.4byte	.LCFI13-.LCFI12
	.byte	0x8e
	.uleb128 0x2
	.byte	0x8d
	.uleb128 0x3
	.byte	0x8b
	.uleb128 0x4
	.byte	0x84
	.uleb128 0x5
	.byte	0x4
	.4byte	.LCFI14-.LCFI13
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE6:
	.text
.Letext0:
	.section	.debug_info
	.4byte	0x1fc
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.Ldebug_line0
	.4byte	.Letext0
	.4byte	.Ltext0
	.4byte	.LC11
	.4byte	.LC12
	.4byte	.LC13
	.byte	0x1
	.uleb128 0x2
	.4byte	0x83
	.byte	0x1
	.4byte	.LC3
	.byte	0x1
	.byte	0x4
	.4byte	0x83
	.4byte	.LFB3
	.4byte	.LFE3
	.byte	0x1
	.byte	0x5b
	.uleb128 0x3
	.ascii	"a\000"
	.byte	0x1
	.byte	0x5
	.4byte	0x8a
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x3
	.ascii	"x1\000"
	.byte	0x1
	.byte	0x5
	.4byte	0xa8
	.byte	0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x3
	.ascii	"x2\000"
	.byte	0x1
	.byte	0x5
	.4byte	0xa8
	.byte	0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x4
	.4byte	.LC0
	.byte	0x1
	.byte	0x6
	.4byte	0x83
	.byte	0x3
	.byte	0x91
	.sleb128 -76
	.uleb128 0x3
	.ascii	"r\000"
	.byte	0x1
	.byte	0x6
	.4byte	0x83
	.byte	0x3
	.byte	0x91
	.sleb128 -80
	.byte	0x0
	.uleb128 0x5
	.ascii	"int\000"
	.byte	0x4
	.byte	0x5
	.uleb128 0x6
	.4byte	0x9a
	.4byte	0xa1
	.uleb128 0x7
	.4byte	0x9a
	.byte	0x2
	.byte	0x0
	.uleb128 0x8
	.4byte	.LC1
	.byte	0x4
	.byte	0x7
	.uleb128 0x8
	.4byte	.LC2
	.byte	0x8
	.byte	0x4
	.uleb128 0x6
	.4byte	0xb8
	.4byte	0xa1
	.uleb128 0x7
	.4byte	0x9a
	.byte	0x1
	.byte	0x0
	.uleb128 0x9
	.4byte	0xec
	.byte	0x1
	.4byte	.LC4
	.byte	0x1
	.byte	0x12
	.byte	0x1
	.4byte	0xa1
	.4byte	.LFB5
	.4byte	.LFE5
	.byte	0x1
	.byte	0x5b
	.uleb128 0xa
	.ascii	"x\000"
	.byte	0x1
	.byte	0x11
	.4byte	0xa1
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x3
	.ascii	"y\000"
	.byte	0x1
	.byte	0x13
	.4byte	0xa1
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.byte	0x0
	.uleb128 0x9
	.4byte	0x175
	.byte	0x1
	.4byte	.LC5
	.byte	0x1
	.byte	0x21
	.byte	0x1
	.4byte	0xa1
	.4byte	.LFB7
	.4byte	.LFE7
	.byte	0x1
	.byte	0x5b
	.uleb128 0xa
	.ascii	"val\000"
	.byte	0x1
	.byte	0x20
	.4byte	0xa1
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x3
	.ascii	"x\000"
	.byte	0x1
	.byte	0x22
	.4byte	0xa1
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x3
	.ascii	"dx\000"
	.byte	0x1
	.byte	0x23
	.4byte	0xa1
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x4
	.4byte	.LC6
	.byte	0x1
	.byte	0x24
	.4byte	0xa1
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x4
	.4byte	.LC7
	.byte	0x1
	.byte	0x25
	.4byte	0xa1
	.byte	0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x4
	.4byte	.LC8
	.byte	0x1
	.byte	0x26
	.4byte	0xa1
	.byte	0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x3
	.ascii	"i\000"
	.byte	0x1
	.byte	0x27
	.4byte	0x83
	.byte	0x3
	.byte	0x91
	.sleb128 -68
	.uleb128 0x4
	.4byte	.LC9
	.byte	0x1
	.byte	0x27
	.4byte	0x83
	.byte	0x3
	.byte	0x91
	.sleb128 -72
	.byte	0x0
	.uleb128 0x9
	.4byte	0x1f9
	.byte	0x1
	.4byte	.LC10
	.byte	0x1
	.byte	0x4b
	.byte	0x1
	.4byte	0x83
	.4byte	.LFB9
	.4byte	.LFE9
	.byte	0x1
	.byte	0x5b
	.uleb128 0xa
	.ascii	"a\000"
	.byte	0x1
	.byte	0x4a
	.4byte	0x1f9
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xa
	.ascii	"x1\000"
	.byte	0x1
	.byte	0x4a
	.4byte	0x1f9
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xa
	.ascii	"x2\000"
	.byte	0x1
	.byte	0x4a
	.4byte	0x1f9
	.byte	0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x3
	.ascii	"d\000"
	.byte	0x1
	.byte	0x4c
	.4byte	0xa1
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x3
	.ascii	"w1\000"
	.byte	0x1
	.byte	0x4c
	.4byte	0xa1
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x3
	.ascii	"w2\000"
	.byte	0x1
	.byte	0x4c
	.4byte	0xa1
	.byte	0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x3
	.ascii	"res\000"
	.byte	0x1
	.byte	0x4c
	.4byte	0xa1
	.byte	0x2
	.byte	0x91
	.sleb128 -60
	.uleb128 0x3
	.ascii	"ret\000"
	.byte	0x1
	.byte	0x4d
	.4byte	0x83
	.byte	0x2
	.byte	0x91
	.sleb128 -64
	.byte	0x0
	.uleb128 0xb
	.byte	0x4
	.4byte	0xa1
	.byte	0x0
	.section	.debug_abbrev
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x10
	.uleb128 0x6
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x24
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x7
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0x24
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",%progbits
	.4byte	0x32
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x200
	.4byte	0x25
	.ascii	"main\000"
	.4byte	0xb8
	.ascii	"fabs\000"
	.4byte	0xec
	.ascii	"sqrt\000"
	.4byte	0x175
	.ascii	"qurt\000"
	.4byte	0x0
	.section	.debug_aranges,"",%progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0x0
	.2byte	0x0
	.2byte	0x0
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	0x0
	.4byte	0x0
	.section	.debug_str,"MS",%progbits,1
.LC4:
	.ascii	"fabs\000"
.LC13:
	.ascii	"GNU C 3.3.2\000"
.LC9:
	.ascii	"flag\000"
.LC0:
	.ascii	"result\000"
.LC3:
	.ascii	"main\000"
.LC5:
	.ascii	"sqrt\000"
.LC10:
	.ascii	"qurt\000"
.LC12:
	.ascii	"/home/carlos/carlos-mestrado/Projects/Mestrado/Diss"
	.ascii	"ertacao/pesti/examples\000"
.LC1:
	.ascii	"unsigned int\000"
.LC11:
	.ascii	"qurt.c\000"
.LC8:
	.ascii	"fdiff\000"
.LC6:
	.ascii	"diff\000"
.LC7:
	.ascii	"min_tol\000"
.LC2:
	.ascii	"double\000"
	.ident	"GCC: (GNU) 3.3.2"
