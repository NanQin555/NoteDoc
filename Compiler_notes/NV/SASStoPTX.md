# intro

SASS(Streaming Assembler) and PTX(Parallel Thread Execution) is IR

# PTX

1. 硬件无关：It can used in different GPU arch, and CUDA compiler will transform it to SASS, which can run on GPU directly.
2. 编译步骤：CUDA程序 -> PTX code -> Machine code

# SASS

SASS is the final machine code, which is the lowest asm language.

PTX -> SASS

Depend on specific arch

不可移植

# 工具

``` shell

nvcc kernel.cu -gencode=arch=compute_52,code=\"sm_52,compute_52\" -gencode=arch=compute_61,code=\"sm_61,compute_61\" -gencode=arch=compute_70,code=\"sm_70,compute_70\" -gencode=arch=compute_75,code=\"sm_75,compute_75\" -gencode=arch=compute_80,code=\"sm_80,compute_80\" -gencode=arch=compute_90,code=\"sm_90,compute_90\"

cuobjdump --dump-ptx a.out

cuobjdump --dump-sass a.out

nvcc kernel.cu -gencode=arch=compute_90,code=sm_90 --cubin

nvdisasm kernel.cubin

nvdisasm -bbcfg kernel.cubin | dot -o1.png -Tpng

```