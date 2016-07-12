#!/bin/sh

export TOOL_CHAIN_PATH=/homes/zynqfs/mesa-built/
export TOOL_CHAIN_LIB=/homes/zynqfs/mesa-built/nemaweaver-elf/lib

set -x

$TOOL_CHAIN_PATH/bin/clang++ -m32 -w -fno-builtin -emit-llvm -S -fno-builtin -target nemacoreel-linux-gnu -O3 $1.cpp -o test.ll &&
$TOOL_CHAIN_PATH/bin/llc -march=nemacoreel -asm-verbose -relocation-model=static -vectorize-slp  -vectorize-loops -vectorize-slp-aggressive -mattr=+condmov,+single-float,-dsp,-fp64,+o32,-bitcount,+Vectors4f,+maddfloat,+fset -O3  test.ll -o test.s &&
$TOOL_CHAIN_PATH/bin/nemaweaver-elf-as -EL -no-reljump-conversion test.s -o test.o &&
#$NEMATOOLCHAIN/bin/nemaweaver-elf-ld -EL -Map ../image.map -N -T../platform.ld -O3 -L$NEMATOOLCHAIN/lib -L. -L$NEMATOOLCHAIN/nemaweaver-elf/lib ../bootlcd.o test.o -o test.obj  -lc -lm -lsoft&&
#$TOOL_CHAIN_PATH/bin/nemaweaver-elf-ld -EL -N -T./platform.ld -O3 -L$TOOL_CHAIN_LIB boot.o test.o -o test.obj  -lc -lm -lsoft &&
$TOOL_CHAIN_PATH/bin/nemaweaver-elf-ld -EL -N -T./platform.ld -O3 -L$TOOL_CHAIN_LIB test.o -o test.obj  -lc -lm -lsoft &&
$TOOL_CHAIN_PATH/bin/nemaweaver-elf-objcopy -Rcomment --set-section-flags .bss=alloc,load,contents -O binary test.obj $1.bin
