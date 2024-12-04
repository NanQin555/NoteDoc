# JD

## 岗位介绍
该岗位旨在优化 OpenCV 在 RISC-V 向量扩展 (RISC-V Vector, RVV) 平台上的性能表现。 OpenCV 是世界上规模最大、应用最为广泛的开源计算机视觉算法库，包含 2500 多种算法。 为了优化算法库在 CPU 上的性能，OpenCV 支持多种 SIMD 或向量架构，包括SSE2-SSE4.2, AVX2, AVX512 (x86); NEON (ARM); RVV (RISC-V)。而为了避免编写和维护同一优化算法面向多个平台的副本, 社区在平台特定的 Intrinsic 函数之上封装了 Universal Intrinsic。 然而，某些内核函数对性能非常关键，并且可以使用其他平台上不存在的一些特定于硬件的指令来最有效地实现它们。在这种情况下，Universal Intrinsic 方法将不起作用。相反，应该为此类性能关键型内核引入平台特定的优化。 RVV 的向量特性让我们有机会去进一步优化这些关键函数的性能，这就是我们想做的事情。 具体来说，需要使用 RVV 的平台特定 Intrinsic 函数为 OpenCV 中的核心函数实现特定优化。并在不同硬件设备上开展性能分析，据此进一步采用循环展开、寄存器分组等方法深入调优。

## 实习内容
参考现有的 ARM Neon (opencv/3rdparty/carotene) 优化实现，补充和完善 RVV (opencv/3rdparty/halrvv/halrvv_1p0) 优化。

使用 RISC-V 开发板评估性能优化效果。

使用 ARM 开发板对比优化效果。

## 参考资料 
OpenCV 代码仓库: https://github.com/opencv/opencv

RVV Intrinsic: https://github.com/riscv-non-isa/rvv-intrinsic-doc

OpenCV 中 ARM Neon 特定优化实现：https://github.com/opencv/opencv/tree/4.x/3rdparty/carotene

OpenCV 中 RVV 特定优化实现：https://github.com/opencv/opencv/tree/4.x/3rdparty/hal_rvv

用于开展性能评估的开发板： CanMV-k230 (RVV, VLEN=128), SpacemiT Muse Pi (RVV, VLEN=256) 和 ATOMPI-CA1 (ARM A55), 以上设备均由此岗位的 mentor 提供远程访问。

## 岗位要求
学习过 C++ 编程，了解使用 Intrinsic 编写向量优化代码的方法。

熟悉 RISC-V 指令集架构，能够部署和使用 RISC-V GNU 工具链和 QEMU 模拟器。

具备较强的代码分析和问题解决能力，能够使用 GDB 等工具调试 RISC-V 程序。

加分项：拥有使用 OpenCV 进行项目开发的经历，熟悉计算机视觉算法。

加分项：具备任意架构的 SIMD intrinsics 开发经验。

加分项：对开源贡献有较高热情，能够使用英文在开源社区中沟通交流。

# 远程上机编程测试
所有技术门类实习生默认都需要上机考试，登陆进入远程Linux主机做3题C/C++编程基础。无法进入考试环境的同学直接fail。

远程上机考试要求是ssh远程登录考试的VM，进入tmux进行测试。

面试官和学生可以共享同一个 tmux 屏幕（不过现在基本上都是考生自己solo了）。

# E-mail

`吴伟 wuwei2016@iscas.ac.cn`

`岗位编号 - 姓名 - 手机号码 - 学校`

标题：J146-王南钦-18080438862-电子科技大学

正文：

  吴老师您好，我是来自电子科技大学的大三学生王南钦。我主要的学习方向为编译器，曾组队参加过华为毕昇杯（实现一个简单的riscv编译器），我负责编译器后端部分内容（指令选择指令调度等），对于rv64gc较为熟悉；同时因为项目多人合作性质，我对于团队合作流程熟悉。
  了解到PLCT招聘“OpenCV RISC-V 向量扩展移植与优化” 实习生，我对该项目很感兴趣，最近在了解rvv以及opencv基础知识。在阅读《我们如何对实习生进行能力分级评定》后自认为能达到LV2能力，希望能够提供实习机会，万分感谢！

  如有叨扰，还望海涵！

`附上简历`

