	.file	"rvv.c"
	.option nopic
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_v1p0_zicsr2p0_zifencei2p0_zve32f1p0_zve32x1p0_zve64d1p0_zve64f1p0_zve64x1p0_zvl128b1p0_zvl32b1p0_zvl64b1p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	vec_add_rvv
	.type	vec_add_rvv, @function
vec_add_rvv:
.LFB11:
	.cfi_startproc
	vsetvli	a5,a3,e32,m2,ta,ma
	beq	a5,zero,.L8
.L3:
	vle32.v	v2,0(a1)
	vle32.v	v4,0(a2)
	sub	a3,a3,a5
	slli	a4,a5,2
	add	a1,a1,a4
	add	a2,a2,a4
	vadd.vv	v2,v2,v4
	vse32.v	v2,0(a0)
	vsetvli	a5,a3,e32,m2,ta,ma
	add	a0,a0,a4
	bne	a5,zero,.L3
.L8:
	ret
	.cfi_endproc
.LFE11:
	.size	vec_add_rvv, .-vec_add_rvv
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align	3
.LC0:
	.string	"%d "
	.section	.text.startup,"ax",@progbits
	.align	1
	.globl	main
	.type	main, @function
main:
.LFB12:
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	lui	a2,%hi(.LANCHOR0)
	sd	s0,16(sp)
	addi	a1,a2,%lo(.LANCHOR0)
	.cfi_offset 8, -16
	lui	s0,%hi(.LANCHOR1)
	addi	a0,s0,%lo(.LANCHOR1)
	addi	a1,a1,40
	addi	a2,a2,%lo(.LANCHOR0)
	li	a3,10
	addi	s0,s0,%lo(.LANCHOR1)
	sd	s1,8(sp)
	sd	s2,0(sp)
	sd	ra,24(sp)
	.cfi_offset 9, -24
	.cfi_offset 18, -32
	.cfi_offset 1, -8
	addi	s2,s0,40
	call	vec_add_rvv
	lui	s1,%hi(.LC0)
.L12:
	lw	a1,0(s0)
	addi	a0,s1,%lo(.LC0)
	addi	s0,s0,4
	call	printf
	bne	s0,s2,.L12
	li	a0,10
	call	putchar
	ld	ra,24(sp)
	.cfi_restore 1
	ld	s0,16(sp)
	.cfi_restore 8
	ld	s1,8(sp)
	.cfi_restore 9
	ld	s2,0(sp)
	.cfi_restore 18
	li	a0,0
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE12:
	.size	main, .-main
	.globl	z
	.globl	y
	.globl	x
	.data
	.align	3
	.set	.LANCHOR0,. + 0
	.type	y, @object
	.size	y, 40
y:
	.word	0
	.word	9
	.word	8
	.word	7
	.word	6
	.word	5
	.word	4
	.word	3
	.word	2
	.word	1
	.type	x, @object
	.size	x, 40
x:
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	9
	.word	0
	.bss
	.align	3
	.set	.LANCHOR1,. + 0
	.type	z, @object
	.size	z, 40
z:
	.zero	40
	.ident	"GCC: (g04696df09) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
