	#.abicalls
	#.option	pic0
	.section .mdebug.abi32
	.previous
	.file	"test.ll"
	.text
	.globl	yuv2rgba
	.align	2
	.type	yuv2rgba,@function
	.set	nonemacore16            # @yuv2rgba
	.ent	yuv2rgba
yuv2rgba:

	.set	noreorder
	.set	nomacro
	.set	noat
# BB#0:                                 # %entry
	#APP
	mov.v4 v1, v254
	#NO_APP
	addiu	v2.x, v1.x, 1
	srl	v3.x, v1.x, 1
	#APP
	mov.v4 v8.x, v0.y
	#NO_APP
	#APP
	mov.v4 v8.y, v0.x
	#NO_APP
	addu	v3.y, v8.y, v3.x
	lbu	v8.y, v3.y, 0
	fset	v2.y, 0
	fset	v2.z, 0
	mov.v4	v9.x, v1.x
	fset	v2.w, 0
	fset	v3.y,  1051730117
	fset	v3.z,  1068725436
	addiu	v8.y, v8.y, -128
	i2f.v4	v8.y, v8.y
	addu	v3.x, v8.x, v3.x
	lbu	v8.x, v3.x, 0
	addiu	v8.x, v8.x, -128
	i2f.v4	v8.x, v8.x
	mul.v4	v8.z, v8.x, v3.z
	mul.v4	v8.w, v8.y, v3.y
	mov.v4	v3, v2
	mov.v4	v3.y, v1.y
	addiu	v2.y, v1.y, 1
	addiu	v9.y, v1.y, 1
	fset	v11.x,  1071829221
	fset	v6.x,  1060554932
	mul.v4	v8.y, v8.y, v11.x
	fset	v9.z, 0
	fset	v2.z, 0
	fset	v3.z, 0
	#APP
	mov.v4 v11.x, v0.w
	#NO_APP
	lbu	v11.y, v11.x, 0
	fset	v3.w, 0
	fset	v2.w, 0
	fset	v9.w, 0
	mov.v4	v11.z, v8.x
	madd.v4	v8.x, v11.z, v6.x, v8.w
	f2i.v4	v8.z, v8.z
	addu	v11.z, v8.z, v11.y
	f2i.v4	v8.y, v8.y
	addu	v8.w, v8.y, v11.y
	sll	v8.w, v8.w, 16
	or	v8.w, v8.w, v11.z
	f2i.v4	v11.z, v8.x
	mov.v4	v8.x, v11.y
	subu	v8.x, v8.x, v11.z
	sll	v11.y, v8.x, 8
	or	v6.y, v8.w, v11.y
	#APP
	pixout v1, v6.y, 6
	#NO_APP
	lbu	v8.x, v11.x, 1
	mov.v4	v1.x, v8.z
	addu	v1.x, v8.x, v1.x
	mov.v4	v1.y, v8.x
	addu	v8.w, v8.y, v1.y
	sll	v8.w, v8.w, 16
	or	v8.w, v8.w, v1.x
	subu	v8.x, v8.x, v11.z
	sll	v1.x, v8.x, 8
	or	v6.y, v8.w, v1.x
	#APP
	pixout v3, v6.y, 6
	#NO_APP
	lbu	v8.x, v11.x, 2113
	subu	v8.w, v8.x, v11.z
	sll	v8.w, v8.w, 8
	mov.v4	v1.x, v8.z
	addu	v1.x, v8.x, v1.x
	or	v8.w, v8.w, v1.x
	mov.v4	v1.x, v8.y
	addu	v8.x, v8.x, v1.x
	sll	v1.x, v8.x, 16
	or	v6.y, v8.w, v1.x
	#APP
	pixout v2, v6.y, 6
	#NO_APP
	lbu	v8.x, v11.x, 2112
	subu	v8.w, v8.x, v11.z
	sll	v8.w, v8.w, 8
	mov.v4	v1.x, v8.z
	addu	v1.x, v8.x, v1.x
	or	v8.z, v8.w, v1.x
	mov.v4	v1.x, v8.y
	addu	v8.x, v8.x, v1.x
	sll	v1.x, v8.x, 16
	or	v6.y, v8.z, v1.x
	#APP
	pixout_y v9, v6.y, 6
	#NO_APP
	jr	v7.w
	.set	at
	.set	macro
	.set	reorder
	.end	yuv2rgba
$tmp0:
	.size	yuv2rgba, ($tmp0)-yuv2rgba


	.ident	"clang version 3.4 (tags/RELEASE_34/final) (/tools/GITROOT/llvm34.git 74f6662490a6891f4e48c43b4085bd86ca140202)"
