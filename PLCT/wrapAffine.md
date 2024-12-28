# opencv

vscode + riscv64-unknown-linux-gnu-gdb 调试: 先手动启动qemu

cmake -G Ninja .. -DCMAKE_TOOLCHAIN_FILE=../platforms/linux/riscv64-gcc.toolchain.cmake -DBUILD_EXAMPLES=OFF -DWITH_OPENCL=OFF  -DTOOLCHAIN_COMPILER_LOCATION_HINT=/opt/riscv/bin -DENABLE_RVV=ON -DWITH_HAL_RVV=ON -DBUILD_SHARED_LIBS=OFF -DOPENCV_EXTRA_CXX_FLAGS="-static -static-libgcc -static-libstdc++" -DOPENCV_EXTRA_C_FLAGS="-static -static-libgcc -static-libstdc++" -DCMAKE_BUILD_TYPE=Debug

测试: 
1. " ./opencv_test_imgproc --gtest_filter="*WarpAffine*" "
2. " ./opencv_perf_imgproc --gtest_filter="*WarpAffine*" --gtest_output=xml:./result.xml"
   
# 仿射变换

二维坐标的线性变换

图像翻转(Flip)，旋转(Rotations)，平移(Translations)，缩放(Scale)等

## 插值

插值: 是一种估计或计算两个已知数据点之间未知数据点的技术。在图像处理中，插值用于估计在变换过程中像素位置之间的像素值。

# 目标函数

                    warpAffine
                        |
                WarpAffineInvoker
               /                 \
warpAffineBlocklineNN             warpAffineBlockline

## warpAffine

处理整个图的仿射变换

矩阵 dst = 矩阵 src * M[6]

M[6]: 通过不同的值代表不同的变换
```
x' = x*M[0] + y*M[1] + M[2];
y' = x*M[3] + y*M[4] + M[5];
```
流程：
1. 计算adelta, bdelta
2. parallel_for_ 调用 invoker （CPU并行？）
3. invoker 里调用 warpAffineBlocklineNN warpAffineBlockline

## warpAffineBlocklineNN

处理单个块行的仿射变换，使用最近邻插值(NN: Nearest Neighbor Interpolation)

## warpAffineBlockline

处理单个块行的仿射变换，使用更复杂的插值方法

## WarpAffineInvoker->operator

1. 分块处理
2. 计算仿射变换
3. 插值处理
4. 并行化处理

