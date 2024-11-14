
# 创建DAG

llvm-IR -> DAG

一个Selection DAG表示一个basic block

SDNode是DAG的基本单位，包含了结点的编号、操作数信息（包括操作数序列、操作数个数）、该结点的使用者序列、该结点对应的源码在源文件中的位置等信息

chain用于表示多个结点之间的顺序执行关系

glue则用于表示两个结点之间不能穿插其他的结点

为什么引入CopyFromReg：调用约定通常会要求参数使用物理寄存器，CopyFromReg意思是从物理寄存器复制到虚拟寄存器