# 仿射变换

二维坐标的线性变换

图像翻转(Flip)，旋转(Rotations)，平移(Translations)，缩放(Scale)等

# 目标函数

## warpAffine

处理整个图的仿射变换

M[6]
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