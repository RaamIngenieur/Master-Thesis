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
	#APP
	mov.v4 v8.x, v0.y
	#NO_APP
	fset	v6.x,  1060554932
	addu	v3.x, v8.x, v1.x
	#APP
	mov.v4 v8.x, v0.x
	#NO_APP
	addu	v3.y, v8.x, v1.x
	mov.v4	v9, v1
	sll	v9.x, v9.x, 1
	lbu	v8.z, v3.y, 0
	sll	v8.x, v1.x, 1
	sll	v9.y, v1.y, 1
	sll	v8.w, v1.y, 1
	mov.v4	v1.y, v255.z
	i2f.v4	v8.z, v8.z
	ori	v8.y, v8.x, 1
	addiu	v2.x, v8.y, -1
	lbu	v8.y, v3.x, 0
	add.v4	v8.z, v8.z, v1.y
	mov.v4	v11, v9
	fset	v1.x,  3271557120
	i2f.v4	v8.y, v8.y
	add.v4	v8.z, v8.z, v1.x
	ori	v11.x, v8.x, 1
	add.v4	v8.x, v8.y, v1.y
	#APP
	mov.v4 v1.y, v0.w
	#NO_APP
	fset	v1.z,  1051730117
	mul.v4	v12.x, v8.z, v1.z
	#APP
	mov.v4 v1.z, v128.x
	#NO_APP
	add.v4	v8.x, v8.x, v1.x
	fset	v1.w,  1068725436
	mul.v4	v8.z, v8.z, v1.w
	mov.v4	v1.w, v8.x
	fset	v3.x,  1071829221
	mul.v4	v1.x, v8.x, v3.x
	madd.v4	v1.w, v1.w, v6.x, v12.x
	lbu	v8.y, v1.y, 0
	fset	v6.y,  2147483648
	mov.v4	v10.x, v1.y
	add.v4	v8.x, v6.y, -v1.w
	f2i.v4	v1.x, v1.x
	addu	v1.z, v10.x, v1.z
	addu	v10.x, v8.y, v1.x
	mov.v4	v1.w, v8.y
	f2i.v4	v8.x, v8.x
	addu	v10.y, v8.x, v1.w
	f2i.v4	v13.x, v8.z
	addu	v10.z, v8.y, v13.x
	fset	v10.w, 0
	#APP
	pixout v9, v10, 5
	#NO_APP
	lbu	v8.y, v1.y, 1
	mov.v4	v1.y, v8.x
	addu	v6.x, v8.y, v1.x
	addu	v6.y, v8.y, v1.y
	addu	v6.z, v8.y, v13.x
	fset	v6.w, 0
	#APP
	pixout v11, v6, 5
	#NO_APP
	lbu	v8.y, v1.z, 1
	mov.v4	v1.y, v8.x
	addu	v6.x, v8.y, v1.x
	addu	v6.y, v8.y, v1.y
	mov.v4	v3, v11
	addu	v6.z, v8.y, v13.x
	ori	v3.y, v8.w, 1
	fset	v6.w, 0
	#APP
	pixout v3, v6, 5
	#NO_APP
	lbu	v8.y, v1.z, 0
	mov.v4	v3.x, v8.x
	addu	v1.x, v8.y, v1.x
	addu	v1.y, v8.y, v3.x
	ori	v2.y, v8.w, 1
	addu	v1.z, v8.y, v13.x
	fset	v2.z, 0
	fset	v2.w, 0
	fset	v1.w, 0
	#APP
	pixout_y v2, v1, 5
	#NO_APP
	jr	v7.w
	.set	at
	.set	macro
	.set	reorder
	.end	yuv2rgba
$tmp0:
	.size	yuv2rgba, ($tmp0)-yuv2rgba


	.ident	"clang version 3.4 (tags/RELEASE_34/final) (/tools/GITROOT/llvm34.git/ 2d31eacff8d7648e80827d85c0875ec3961e50e7)"
