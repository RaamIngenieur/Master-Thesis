; ModuleID = 'yuv2rgba.cpp'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:32-i16:16:32-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-n32-S64"
target triple = "nemacoreel--linux-gnu"

; Function Attrs: naked noinline nounwind
define void @yuv2rgba() #0 {
entry:
  %0 = tail call <4 x i32> asm sideeffect "mov.v4 $0, v254", "=v"() #1, !srcloc !1
  %1 = tail call i8* asm sideeffect "mov.v4 $0, v0.y", "=d"() #1, !srcloc !2
  %2 = tail call i8* asm sideeffect "mov.v4 $0, v0.x", "=d"() #1, !srcloc !3
  %3 = extractelement <4 x i32> %0, i32 0
  %add.ptr = getelementptr inbounds i8* %1, i32 %3
  %4 = load i8* %add.ptr, align 1, !tbaa !4
  %conv = uitofp i8 %4 to float
  %sub = fadd float %conv, -1.280000e+02
  %add.ptr1 = getelementptr inbounds i8* %2, i32 %3
  %5 = load i8* %add.ptr1, align 1, !tbaa !4
  %conv2 = uitofp i8 %5 to float
  %sub3 = fadd float %conv2, -1.280000e+02
  %mul = fmul float %sub, 0x3FFC5A1CA0000000
  %conv4 = fptosi float %mul to i32
  %mul5 = fmul float %sub3, 0x3FD60418A0000000
  %mul6 = fmul float %sub, 0x3FE6D91680000000
  %add = fadd float %mul6, %mul5
  %sub7 = fsub float -0.000000e+00, %add
  %conv8 = fptosi float %sub7 to i32
  %mul9 = fmul float %sub3, 0x3FF66E9780000000
  %conv10 = fptosi float %mul9 to i32
  %mul11 = shl i32 %3, 1
  %6 = insertelement <4 x i32> %0, i32 %mul11, i32 0
  %7 = extractelement <4 x i32> %0, i32 1
  %mul12 = shl i32 %7, 1
  %8 = insertelement <4 x i32> %6, i32 %mul12, i32 1
  %9 = tail call i8* asm sideeffect "mov.v4 $0, v0.w", "=d"() #1, !srcloc !7
  %10 = tail call i32 asm sideeffect "mov.v4 $0, v128.x", "=d"() #1, !srcloc !8
  %11 = load i8* %9, align 1, !tbaa !4
  %conv13 = zext i8 %11 to i32
  %add14 = add nsw i32 %conv13, %conv4
  %vecinit = insertelement <4 x i32> undef, i32 %add14, i32 0
  %add15 = add nsw i32 %conv8, %conv13
  %vecinit16 = insertelement <4 x i32> %vecinit, i32 %add15, i32 1
  %add17 = add nsw i32 %conv13, %conv10
  %vecinit18 = insertelement <4 x i32> %vecinit16, i32 %add17, i32 2
  %vecinit19 = insertelement <4 x i32> %vecinit18, i32 0, i32 3
  tail call void asm sideeffect "pixout $0, $1, $2", "v,v,I"(<4 x i32> %8, <4 x i32> %vecinit19, i32 5) #1, !srcloc !9
  %add.ptr20 = getelementptr inbounds i8* %9, i32 1
  %12 = load i8* %add.ptr20, align 1, !tbaa !4
  %conv21 = zext i8 %12 to i32
  %add23 = add nsw i32 %conv21, %conv4
  %vecinit24 = insertelement <4 x i32> undef, i32 %add23, i32 0
  %add25 = add nsw i32 %conv21, %conv8
  %vecinit26 = insertelement <4 x i32> %vecinit24, i32 %add25, i32 1
  %add27 = add nsw i32 %conv21, %conv10
  %vecinit28 = insertelement <4 x i32> %vecinit26, i32 %add27, i32 2
  %vecinit29 = insertelement <4 x i32> %vecinit28, i32 0, i32 3
  %add30102 = or i32 %mul11, 1
  %13 = insertelement <4 x i32> %8, i32 %add30102, i32 0
  tail call void asm sideeffect "pixout $0, $1, $2", "v,v,I"(<4 x i32> %13, <4 x i32> %vecinit29, i32 5) #1, !srcloc !10
  %add.ptr31 = getelementptr inbounds i8* %9, i32 %10
  %add.ptr31.sum = add i32 %10, 1
  %add.ptr32 = getelementptr inbounds i8* %9, i32 %add.ptr31.sum
  %14 = load i8* %add.ptr32, align 1, !tbaa !4
  %conv33 = zext i8 %14 to i32
  %add35 = add nsw i32 %conv33, %conv4
  %vecinit36 = insertelement <4 x i32> undef, i32 %add35, i32 0
  %add37 = add nsw i32 %conv33, %conv8
  %vecinit38 = insertelement <4 x i32> %vecinit36, i32 %add37, i32 1
  %add39 = add nsw i32 %conv33, %conv10
  %vecinit40 = insertelement <4 x i32> %vecinit38, i32 %add39, i32 2
  %vecinit41 = insertelement <4 x i32> %vecinit40, i32 0, i32 3
  %inc103 = or i32 %mul12, 1
  %15 = insertelement <4 x i32> %13, i32 %inc103, i32 1
  tail call void asm sideeffect "pixout $0, $1, $2", "v,v,I"(<4 x i32> %15, <4 x i32> %vecinit41, i32 5) #1, !srcloc !11
  %16 = load i8* %add.ptr31, align 1, !tbaa !4
  %conv43 = zext i8 %16 to i32
  %add45 = add nsw i32 %conv43, %conv4
  %vecinit46 = insertelement <4 x i32> undef, i32 %add45, i32 0
  %add47 = add nsw i32 %conv43, %conv8
  %vecinit48 = insertelement <4 x i32> %vecinit46, i32 %add47, i32 1
  %add49 = add nsw i32 %conv43, %conv10
  %vecinit50 = insertelement <4 x i32> %vecinit48, i32 %add49, i32 2
  %vecinit51 = insertelement <4 x i32> %vecinit50, i32 0, i32 3
  %dec = add i32 %add30102, -1
  %vecinit53 = insertelement <4 x i32> undef, i32 %dec, i32 0
  %vecinit54 = insertelement <4 x i32> %vecinit53, i32 %inc103, i32 1
  %vecinit55 = insertelement <4 x i32> %vecinit54, i32 0, i32 2
  %vecinit56 = insertelement <4 x i32> %vecinit55, i32 0, i32 3
  tail call void asm sideeffect "pixout_y $0, $1, $2", "v,v,I"(<4 x i32> %vecinit56, <4 x i32> %vecinit51, i32 5) #1, !srcloc !12
  ret void
}

attributes #0 = { naked noinline nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.4 (tags/RELEASE_34/final) (/tools/GITROOT/llvm34.git/ 2d31eacff8d7648e80827d85c0875ec3961e50e7)"}
!1 = metadata !{i32 -2147475736}
!2 = metadata !{i32 -2147475673}
!3 = metadata !{i32 -2147475601}
!4 = metadata !{metadata !5, metadata !5, i64 0}
!5 = metadata !{metadata !"omnipotent char", metadata !6, i64 0}
!6 = metadata !{metadata !"Simple C/C++ TBAA"}
!7 = metadata !{i32 -2147475529}
!8 = metadata !{i32 -2147475454}
!9 = metadata !{i32 -2147475338}
!10 = metadata !{i32 -2147475141}
!11 = metadata !{i32 -2147474944}
!12 = metadata !{i32 -2147474747}
