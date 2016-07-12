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
	mov.v4 v1, v254                       # read_coords(coords);
	#NO_APP
	#APP
	mov.v4 v8.x, v0.y                     # read_reg(pChromaCb, "v0.y");
	#NO_APP
	#APP
	mov.v4 v8.y, v0.x                     # read_reg(pChromaCr, "v0.x");
	#NO_APP

	fset	v6.x,  1060554932               # v6.x = 0.714f
	srl	v9.x, v1.x, 1                     # v9.x = coords.x / 2
	addu	v9.y, v8.y, v9.x                # v9.y = pChromaCb +  coords.x / 2
	lbu	v8.y, v9.y, 0                     # v8.y = *(pChromaCb +  coords.x / 2)
	addu	v9.x, v8.x, v9.x                # v9.x = pChromaCr +  coords.x / 2
	addiu	v8.y, v8.y, -128                # v8.y = *(pChromaCb +  coords.x / 2) - 128
	lbu	v8.x, v9.x, 0                     # v8.x = *(pChromaCr +  coords.x / 2)
	fset	v9.y,  1051730117               # v9.y = 0.344f
	i2f.v4	v8.y, v8.y                    # v8.y = (float)(*(pChromaCb +  coords.x / 2) - 128)
	mul.v4	v8.z, v8.y, v9.y              # v8.z = 0.344f * Cr
	addiu	v8.x, v8.x, -128                # v8.x = *(pChromaCr +  coords.x / 2) - 128
	i2f.v4	v8.x, v8.x                    # v8.x = (float) (*(pChromaCr +  coords.x / 2) - 128)
	mov.v4	v9.w, v8.x                    # v9.w = (float) (*(pChromaCr +  coords.x / 2) - 128)
	madd.v4	v9.w, v9.w, v6.x, v8.z        # v9.w = g1
	fset	v9.y,  1071829221               # v9.y = 1.772f
	mul.v4	v8.y, v8.y, v9.y              # v8.y = r1
	fset	v9.x,  1068725436               # v9.x = 1.402f
	mul.v4	v6.y, v8.x, v9.x              # v6.y = b1




	#APP
	mov.v4 v9.x, v0.w                     # v9.x = pLuma_interp
	#NO_APP
	#APP
	mov.v4 v9.y, v128.x                   # v9.y = uiLStride
	#NO_APP



	fset	v8.w,  2147483648               # v8.w = -0.0f
	add.v4	v8.w, v8.w, -v9.w             # v8.w = -g1
	lbu	v9.z, v9.x, 0                     # v9.z = *(pLuma_interp) = Y
	addiu	v3.x, v1.x, 1                   # v3.x = coords.x + 1
	f2i.v4	v8.y, v8.y                    # v8.y = (int) r1


	addu	v8.z, v8.y, v9.z                # v8.z = y + r1   = r
	f2i.v4	v8.x, v6.y                    # v8.x = (int) b1
	f2i.v4	v8.w, v8.w                    # v8.w = (int) g1
	fset	v3.y, 0                         # v3.y = 0.0f
	addu	v11.x, v8.x, v9.z               # v11.x = y + b1  = b
	sll	v8.z, v8.z, 16                    # v8.z = r << 16
	addu	v6.x, v8.w, v9.z                # v6.x = y + g1   = g
	mov.v4	v2.x, v1.x                    # v2.x = coords.x
	fset	v3.z, 0                         # v3.z = 0.0f
	or	v8.z, v8.z, v11.x                 # v8.z = (r << 16) | b
	sll	v9.z, v6.x, 8                     # v9.z = g << 8
	fset	v3.w, 0                         # v3.w = 0.0f
	or	v6.y, v8.z, v9.z                  # v6.y = (r << 16) | (g << 8) | b
	mov.v4	v10, v3                       # v10 = (coords.x + 1, 0.0f, 0.0f, 0.0f)
	#APP
	pixout v1, v6.y, 6                    # pixout
	#NO_APP
	lbu	v8.z, v9.x, 1                     # v8.z = *(pLuma_interp + 1) = Y
	addiu	v10.y, v1.y, 1                  # v10.y = coords.y + 1
	mov.v4	v3.y, v1.y                    # v3.y = coords.y
	addiu	v2.y, v1.y, 1                   # v2.y = coords.y + 1
	mov.v4	v1.y, v8.y                    # v1.y = r1
	mov.v4	v1.x, v8.x                    # v1.x = b1
	addu	v1.y, v8.z, v1.y                # v1.y = r1 + y = r
	sll	v6.x, v1.y, 16                    # v6.x = r << 16
	addu	v1.x, v8.z, v1.x                # v1.x = b1 + y = b
	or	v6.x, v6.x, v1.x                  # v6.x = (r << 16) | b
	mov.v4	v1.x, v8.z                    # v1.x = Y
	addu	v8.z, v8.w, v1.x                # v8.z = g1 + Y = g
	mov.v4	v12.x, v9.x                   # v12.x = Y
	fset	v3.z, 0                         # v3.z = 0.0f
	sll	v1.x, v8.z, 8                     # v1.x = g << 8
	or	v6.y, v6.x, v1.x                  # v6.y = (r << 16) | (g << 8) | b
	fset	v3.w, 0                         # v3.w = 0.0f
	addu	v9.y, v12.x, v9.y               # v9.y = uiLStride + uiLStride + 1
	#APP
	pixout v3, v6.y, 6
	#NO_APP
	lbu	v8.z, v9.y, 1
	mov.v4	v1.y, v8.w
	mov.v4	v1.x, v8.x
	addu	v1.y, v8.z, v1.y
	sll	v6.x, v1.y, 8
	addu	v1.x, v8.z, v1.x
	or	v6.x, v6.x, v1.x
	mov.v4	v1.x, v8.y
	addu	v8.z, v8.z, v1.x
	fset	v10.z, 0
	sll	v1.x, v8.z, 16
	or	v6.y, v6.x, v1.x
	fset	v10.w, 0
	#APP
	pixout v10, v6.y, 6
	#NO_APP
	lbu	v8.z, v9.y, 0
	mov.v4	v1.y, v8.w
	mov.v4	v1.x, v8.x
	addu	v8.x, v8.z, v1.y
	addu	v1.x, v8.z, v1.x
	sll	v8.x, v8.x, 8
	or	v8.x, v8.x, v1.x
	mov.v4	v1.x, v8.y
	addu	v8.y, v8.z, v1.x
	fset	v2.z, 0
	sll	v1.x, v8.y, 16
	fset	v2.w, 0
	or	v6.y, v8.x, v1.x
	#APP
	pixout_y v2, v6.y, 6
	#NO_APP
	jr	v7.w
	.set	at
	.set	macro
	.set	reorder
	.end	yuv2rgba
$tmp0:
	.size	yuv2rgba, ($tmp0)-yuv2rgba


	.ident	"clang version 3.4 (tags/RELEASE_34/final) (/tools/GITROOT/llvm34.git/ 2d31eacff8d7648e80827d85c0875ec3961e50e7)"
