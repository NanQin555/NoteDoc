# Pre-Task

完成 meanStdDiv RVV 版本

第一阶段仅针对 u8 类型做优化

DDL: 1周 12.9 19:00

**最终：完成 8UC1, 8UC4, F32C1 类型; 加速效果不错, 且矩阵越大加速比越高**

Reference:
1. (线上测试平台)[https://cloud.spacemit.com/]
2. opencv测试工具： ./opencv_perf_core --gtest_filter="Size_MatType_meanStdDev.meanStdDev/*" or/3 `./opencv_perf_core --gtest_filter="Size_MatType_meanStdDev.meanStdDev/*" --gtest_output=xml:./result.xml`
3. (编译opencv)[https://gist.github.com/hanliutong/fad882f1b0df24183d50eac92f576aad]
   `cmake -G Ninja .. -DCMAKE_TOOLCHAIN_FILE=../platforms/linux/riscv64-gcc.toolchain.cmake -DBUILD_EXAMPLES=OFF -DWITH_OPENCL=OFF  -DTOOLCHAIN_COMPILER_LOCATION_HINT=/opt/riscv/bin -DENABLE_RVV=ON -DWITH_HAL_RVV=ON -DBUILD_SHARED_LIBS=OFF -DOPENCV_EXTRA_CXX_FLAGS="-static -static-libgcc -static-libstdc++" -DOPENCV_EXTRA_C_FLAGS="-static -static-libgcc -static-libstdc++"`
    -DWITH_HAL_RVV=ON or OFF
4. 对比效果：`/home/nanqin/project/opencv/modules/ts/misc/summary.py test1.xml test2.xml`

## 要点/难点
1. 找到可以向量化的部分 
2. 实现rvv intrinsic
   1. 确认数据类型
   2. 考虑返回值/参数类型
   3. 考虑指令格式

## 思路

已知RGB (0-255)

1. 每次处理一行中vl个元素，进行redsum，累加到sum中
2. 循环展开一次处理多行中vl个元素，进行redsum，累加到sum中

累加的时候至少 u8 -> u16 才能放下

## 过程

看代码，了解函数作用

实现标量版本

寻找并行/向量化 可能性

实现向量化 -> RVV Intrinsic 不熟 -> 学习 RVV Intrinsic 手册 + RVV ISA + 小实验

向量化ver1.0: 仅针对内层循环进行向量化 -> 改进方向：对内层进行循环展开 将mask也进行向量化

向量化ver1.1: 完成对mask的向量化 -> 改进方向：对内层进行循环展开

向量化ver1.2: 完成外层的循环展开 -> 改进方向: 扩大lmul

向量化ver1.3: 扩大lmul

向量化ver2.0: 完成CV_8UC4的向量化

向量化ver3.0: 完成CV_32FC1的向量化

对比效果

12.6 done
   
## compare

原版：original.xml

标量版：scalar.xml

rvv版：vector1.xml vector1_1.xml vector1_2.xml vector1_3.xml vector2_0.xml vector3_0.xml

### 结论

original.xml <-> vector1_0.xml : CV_8UC1 向量化有效 加速比在 2.53~2.95

vector1.xml <-> vector1_1.xml : CV_8UC1 几乎相同，mask是否向量化对性能几乎没有影响

original.xml <-> vector1_2.xml && vector1_1.xml <-> vector1_2.xml : CV_8UC1 外循环进行循环展开，提升巨大, 对比original加速比在 9.62~663.89

vector1_2.xml <-> vector1_3.xml : CV_8UC1 扩大lmul，加速效果降低 0.68~0.9

original.xml <-> vector2_0.xml : CV_8UC4 加速有效 加速比在 34.31~1744.84

original.xml <-> vector3_0.xml : CV_32FC1 加速有效, 加速比在 36.08~2875.51

vector2_0.xml <-> vector3_0.xml : CV_8UC4 加速略有降低

## 存在问题

1. 不为全局最优解
2. 代码抽象程度不够

## Q & A

1. Q: src_step 和 width 有什么区别？

    A: width表示图像每一行的像素数；step表示图像每一行的字节数（实际图像数据+填充的字节）

2. Q：极端情况下的溢出问题？

    A: 采用宽指令

3. Q：vwxxx 类型指令，type只能向上扩展一次？

    A：yep, i8->i16, i16->i32, i32->i64...

4. Q：rvv中 x s v w 的含义？ 
    
    A: x，s都是标量，x代表一个普通类型的值，s代表vec1[0], v向量， w宽向量

5. Q: vwredsum指令格式？
   
    A: returnType __riscv_vwredsumu_vs_argType_returnType (argType arg2, returnType arg1, size_t vl);  // sum(arg2[*], arg1[0]); 

6. Q: 如何确定booln_t类型?
    
    A: 与需要mask的数据类型的 vl 一致， 如 u8m4: vl = vlen / 8 * 4 = vlen / 2 则选择 bool2_t; 如 u16mf2: vl = vlen / 16 * (1/2) = vlen / 32 则选择 bool32_t;

    1.5 h / day * 5