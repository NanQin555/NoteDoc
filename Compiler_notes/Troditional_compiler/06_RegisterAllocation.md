# Register Allocation

## Introduction

将MIR中使用的虚拟寄存器映射到物理寄存器

主要工作:
1. 存在可用的物理寄存器,变量映射到物理寄存器
2. 没有可用的物理寄存器,将已经分配寄存器的变量重新放回内存,从而得到一个新的空闲寄存器,该过程称为溢出(spill)

主要问题: 选择合适的寄存器进行spill, RA衡量的目标之一就是整体spill成本最低

LLVM RA策略: Fast, Basic, Greedy, PBQP

Fast: 分配时不考虑变量的活跃区间

Basic: 基于活跃变量区间进行

Greedy: 默认分配器, 与Basic区别在于寄存器溢出更复杂

PBQP(Partitioned Boolean Quadratic Problem): 基于PBQP分配器

## 概述

执行寄存器分配(RA)之前, 需要依赖一些Pass

Fast: 依赖 Phi Elimination, Two Address Instruction

其他:
1. RA 前依赖: Detect Dead Lane, Proocess Implicit Defs, Unreachable Machien Block Elim, Live Variables Analsis, Machine Natural Loop Analysis, PHI Elimination, Two Address Instruction, Simple Registger Coalescer, Rename Disconnected Independent Subregs, Machine Scheduler
2. 不同分配算法额外的依赖, Basic RA额外依赖: Debug Variable Analysis, Slot Index Analysis, Live Interval Analysis, Simple Register Coalescer, Live Stack Slot Analysis, AA Result Wrapper, Machine Dominator Tree, Machine Natural Loop Analysis, Virtual Register Map, Live Register Matrix, Basic Register Allocator, Hook point for PreRewirte, Virtual Register Rewitter, Registor Allocation Scroing
3. RA 后依赖: Stack Slot Coloring, Hook point for PostRewrite, Machine Copy Propagation, Machine LICM

## 分析

Detect Dead Lane(死亡和未定义寄存器检测): 分析死亡, 未定义子寄存器; 死亡的寄存器不再分配物理寄存器, 未定义则可以使用任意一个寄存器

Process Implicit Def(隐式定义指令处理): 隐式定义寄存器指的是MIR中未定义的指令, 寄存器分配时需要将隐式定义指令删除, 但又需要对def-use链进行处理

1. 隐式定义指令定义的为虚拟寄存器, 将def-use的use设置为Undef, 对于COPY类指令进行传播, 然后删除指令
2. 隐式定义指令定义为物理寄存器, 如果def-use链中Use的寄存器是Def的寄存器或子寄存器, 将Use设置为Undef, 然后删除指令
3. MI中所有MO(machine operator)都是 Undef时, 删除指令


Unreachable Machine Block Elim(不可达基本块消除): 不可达的MBB属于死代码, 需要删除, 虽然中端会进行死代码消除但后端优化可能引入不可达的MBB

Live Variables(活跃变量分析): 需要计算一条指令结束后立即无效的寄存器(Dead)集合, 还需计算当前指令使用过但之后不再使用的寄存器(Killed)集合。采用了不动点算法, 使用前向数据流分析。

Machine LoopInfo(Loop信息分析)

Phi Elimination(Phi消除)

Live Intervals(活跃变量区间分析)

Two Address Instruction(二地址指令变换)

Register Coalescer(寄存器合并)

Rename Disconnected Independent SubReg(无关子寄存器重命名)

Machine Scheduler(指令调度)

-----

Live Debug Variables(调试信息分析)

Slot Index(指令编号)

Live Intervals(活跃变量区间分析)

RegisterCoalescer(寄存器合并)

MachineScheduler(指令调度)

LiveStacks（活跃栈变量分析）

AAResultWrap（别名分析结果使用）

MachineDominatorTree（支配树分析）

MachineLoopInfo（Loop信息分析）

VirtualRegisterMap（虚拟寄存器映射）

LiveRegisterMatrix（活跃寄存器组合信息）

BasicRegisterAllocator（Basic寄存器分配算法）

PreRewrite（寄存器重写预处理）

VirtualRegisterRewriter（寄存器映射）

RegisterAllocationScoring（寄存器分配评价）

-----

StackSlotColoring（栈槽分配）

PostRewriter（寄存器重写后处理）

MachineCopyPropagation（赋值传播）

MachineLICM（循环不变量外提）

## 图着色算法

