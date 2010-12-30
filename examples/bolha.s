	.file	"bolha.c"
	.file 1 "bolha.c"
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.text
.Ltext0:
	.section	.rodata
	.align	2
.LC0:
	.word	950
	.word	862
	.word	957
	.word	350
	.word	755
	.word	329
	.word	807
	.word	899
	.word	457
	.word	118
	.word	950
	.word	862
	.word	957
	.word	350
	.word	755
	.word	329
	.word	807
	.word	899
	.word	457
	.word	118
	.word	950
	.word	862
	.word	957
	.word	350
	.word	755
	.word	329
	.word	807
	.word	899
	.word	457
	.word	118
	.word	950
	.word	862
	.word	957
	.word	350
	.word	755
	.word	329
	.word	807
	.word	899
	.word	457
	.word	118
	.word	950
	.word	862
	.word	957
	.word	350
	.word	755
	.word	329
	.word	807
	.word	899
	.word	457
	.word	118
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB3:
	.loc 1 3 0
	@ args = 0, pretend = 0, frame = 212
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
.LCFI0:
	stmfd	sp!, {fp, ip, lr, pc}
.LCFI1:
	sub	fp, ip, #4
.LCFI2:
	sub	sp, sp, #212
.LCFI3:
	.loc 1 4 0
.LBB2:
	ldr	r3, .L11
	sub	r2, fp, #224
	mov	ip, #200
	mov	r0, r2
	mov	r1, r3
	mov	r2, ip
	bl	memcpy
	.loc 1 7 0
	mov	r3, #49
	str	r3, [fp, #-16]
.L2:
	ldr	r3, [fp, #-16]
	cmp	r3, #0
	bge	.L5
	b	.L3
.L5:
	.loc 1 10 0
	mov	r3, #1
	str	r3, [fp, #-20]
.L6:
	ldr	r2, [fp, #-20]
	ldr	r3, [fp, #-16]
	cmp	r2, r3
	ble	.L9
	b	.L4
.L9:
	.loc 1 13 0
	ldr	r3, [fp, #-16]
	mvn	r2, #211
	mov	r3, r3, asl #2
	sub	r0, fp, #12
	add	r3, r3, r0
	add	r1, r3, r2
	ldr	r3, [fp, #-20]
	mvn	r2, #211
	mov	r3, r3, asl #2
	sub	r0, fp, #12
	add	r3, r3, r0
	add	r3, r3, r2
	ldr	r2, [r1, #0]
	ldr	r3, [r3, #0]
	cmp	r2, r3
	ble	.L8
	.loc 1 15 0
	ldr	r3, [fp, #-20]
	mvn	r2, #215
	mov	r3, r3, asl #2
	sub	r1, fp, #12
	add	r3, r3, r1
	add	r3, r3, r2
	ldr	r3, [r3, #0]
	str	r3, [fp, #-24]
	.loc 1 16 0
	ldr	r3, [fp, #-20]
	mvn	r2, #215
	mov	r3, r3, asl #2
	sub	r0, fp, #12
	add	r3, r3, r0
	add	r1, r3, r2
	ldr	r3, [fp, #-20]
	mvn	r2, #211
	mov	r3, r3, asl #2
	sub	r0, fp, #12
	add	r3, r3, r0
	add	r3, r3, r2
	ldr	r3, [r3, #0]
	str	r3, [r1, #0]
	.loc 1 17 0
	ldr	r3, [fp, #-20]
	mvn	r2, #211
	mov	r3, r3, asl #2
	sub	r1, fp, #12
	add	r3, r3, r1
	add	r2, r3, r2
	ldr	r3, [fp, #-24]
	str	r3, [r2, #0]
	.loc 1 10 0
.L8:
	ldr	r3, [fp, #-20]
	add	r3, r3, #1
	str	r3, [fp, #-20]
	b	.L6
	.loc 1 7 0
.L4:
	ldr	r3, [fp, #-16]
	sub	r3, r3, #1
	str	r3, [fp, #-16]
	b	.L2
.L3:
	.loc 1 22 0
	mov	r3, #0
	.loc 1 23 0
.LBE2:
	mov	r0, r3
	ldmea	fp, {fp, sp, pc}
.L12:
	.align	2
.L11:
	.word	.LC0
.LFE3:
	.size	main, .-main
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
	.byte	0x4
	.4byte	.LCFI2-.LCFI1
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE0:
	.text
.Letext0:
	.section	.debug_info
	.4byte	0x90
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.Ldebug_line0
	.4byte	.Letext0
	.4byte	.Ltext0
	.4byte	.LC4
	.4byte	.LC5
	.4byte	.LC6
	.byte	0x1
	.uleb128 0x2
	.4byte	0x75
	.byte	0x1
	.4byte	.LC7
	.byte	0x1
	.byte	0x3
	.4byte	0x75
	.4byte	.LFB3
	.4byte	.LFE3
	.byte	0x1
	.byte	0x5b
	.uleb128 0x3
	.ascii	"i\000"
	.byte	0x1
	.byte	0x4
	.4byte	0x75
	.byte	0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x3
	.ascii	"j\000"
	.byte	0x1
	.byte	0x4
	.4byte	0x75
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x4
	.4byte	.LC1
	.byte	0x1
	.byte	0x4
	.4byte	0x75
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x4
	.4byte	.LC2
	.byte	0x1
	.byte	0x4
	.4byte	0x7c
	.byte	0x3
	.byte	0x91
	.sleb128 -224
	.byte	0x0
	.uleb128 0x5
	.ascii	"int\000"
	.byte	0x4
	.byte	0x5
	.uleb128 0x6
	.4byte	0x8c
	.4byte	0x75
	.uleb128 0x7
	.4byte	0x8c
	.byte	0x31
	.byte	0x0
	.uleb128 0x8
	.4byte	.LC3
	.byte	0x4
	.byte	0x7
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
	.byte	0x0
	.section	.debug_pubnames,"",%progbits
	.4byte	0x17
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x94
	.4byte	0x25
	.ascii	"main\000"
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
.LC6:
	.ascii	"GNU C 3.3.2\000"
.LC2:
	.ascii	"numbers\000"
.LC4:
	.ascii	"bolha.c\000"
.LC1:
	.ascii	"temp\000"
.LC7:
	.ascii	"main\000"
.LC5:
	.ascii	"/home/carlos/carlos-mestrado/Projects/Mestrado/Diss"
	.ascii	"ertacao/pesti/examples\000"
.LC3:
	.ascii	"unsigned int\000"
	.ident	"GCC: (GNU) 3.3.2"
