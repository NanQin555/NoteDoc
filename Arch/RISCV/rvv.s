	.text
	.attribute	4, 16
	.attribute	5, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_v1p0_zvl128b1p0_zvl32b1p0_zvl64b1p0"
	.file	"rvv.c"
	.globl	vec_add_rvv                     # -- Begin function vec_add_rvv
	.p2align	2
	.type	vec_add_rvv,@function
vec_add_rvv:                            # @vec_add_rvv
# %bb.0:
	vsetvli	a4, a3, e32, m2, ta, mu
	beqz	a4, .LBB0_2
.LBB0_1:                                # =>This Inner Loop Header: Depth=1
	vle32.v	v8, (a1)
	vle32.v	v10, (a2)
	vadd.vv	v8, v8, v10
	vse32.v	v8, (a0)
	sub	a3, a3, a4
	slli	a5, a4, 2
	add	a1, a1, a5
	add	a2, a2, a5
	vsetvli	a4, a3, e32, m2, ta, mu
	add	a0, a0, a5
	bnez	a4, .LBB0_1
.LBB0_2:
	ret
.Lfunc_end0:
	.size	vec_add_rvv, .Lfunc_end0-vec_add_rvv
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   # @main
# %bb.0:
	addi	sp, sp, -48
	sd	ra, 40(sp)                      # 8-byte Folded Spill
	sd	s0, 32(sp)                      # 8-byte Folded Spill
	sd	s1, 24(sp)                      # 8-byte Folded Spill
	sd	s2, 16(sp)                      # 8-byte Folded Spill
	sd	s3, 8(sp)                       # 8-byte Folded Spill
	vsetivli	a0, 10, e32, m2, ta, mu
	beqz	a0, .LBB1_3
# %bb.1:
	lui	a1, %hi(y)
	addi	a1, a1, %lo(y)
	lui	a2, %hi(x)
	addi	a2, a2, %lo(x)
	lui	a3, %hi(z)
	addi	a3, a3, %lo(z)
	li	a4, 10
.LBB1_2:                                # =>This Inner Loop Header: Depth=1
	vle32.v	v8, (a2)
	vle32.v	v10, (a1)
	vadd.vv	v8, v8, v10
	vse32.v	v8, (a3)
	sub	a4, a4, a0
	slli	a5, a0, 2
	add	a2, a2, a5
	add	a1, a1, a5
	vsetvli	a0, a4, e32, m2, ta, mu
	add	a3, a3, a5
	bnez	a0, .LBB1_2
.LBB1_3:
	li	s1, 0
	lui	a0, %hi(z)
	addi	s2, a0, %lo(z)
	lui	a0, %hi(.L.str)
	addi	s0, a0, %lo(.L.str)
	li	s3, 40
.LBB1_4:                                # =>This Inner Loop Header: Depth=1
	add	a0, s1, s2
	lw	a1, 0(a0)
	mv	a0, s0
	call	printf
	addi	s1, s1, 4
	bne	s1, s3, .LBB1_4
# %bb.5:
	li	a0, 10
	call	putchar@plt
	li	a0, 0
	ld	ra, 40(sp)                      # 8-byte Folded Reload
	ld	s0, 32(sp)                      # 8-byte Folded Reload
	ld	s1, 24(sp)                      # 8-byte Folded Reload
	ld	s2, 16(sp)                      # 8-byte Folded Reload
	ld	s3, 8(sp)                       # 8-byte Folded Reload
	addi	sp, sp, 48
	ret
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
                                        # -- End function
	.type	x,@object                       # @x
	.data
	.globl	x
	.p2align	2
x:
	.word	1                               # 0x1
	.word	2                               # 0x2
	.word	3                               # 0x3
	.word	4                               # 0x4
	.word	5                               # 0x5
	.word	6                               # 0x6
	.word	7                               # 0x7
	.word	8                               # 0x8
	.word	9                               # 0x9
	.word	0                               # 0x0
	.size	x, 40

	.type	y,@object                       # @y
	.globl	y
	.p2align	2
y:
	.word	0                               # 0x0
	.word	9                               # 0x9
	.word	8                               # 0x8
	.word	7                               # 0x7
	.word	6                               # 0x6
	.word	5                               # 0x5
	.word	4                               # 0x4
	.word	3                               # 0x3
	.word	2                               # 0x2
	.word	1                               # 0x1
	.size	y, 40

	.type	z,@object                       # @z
	.bss
	.globl	z
	.p2align	2
z:
	.zero	40
	.size	z, 40

	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%d "
	.size	.L.str, 4

	.ident	"Ubuntu clang version 14.0.0-1ubuntu1.1"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym x
	.addrsig_sym y
	.addrsig_sym z
