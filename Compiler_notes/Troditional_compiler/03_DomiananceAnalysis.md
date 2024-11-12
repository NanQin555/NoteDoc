# Domianance analysis

## Introduction

中端优化如ADCE(Aggressive Dead Code Elimination), SimplifyCFG, BasicAliasAnalysis, LoopPass 都会使用到支配关系。

## Conception

有向图G=<V,E,r>: V为顶点集合, E为边集合, r为根/入口节点集合

可达(Reachable)和不可达(Unreachable): 在G中存在一条从r到结点v的路径,则v是可达;反之,如果不存在任何一条从r到v的路径,则称v是不可达

以可达结点w为例: 

支配(Dominance):如果从r出发到达结点 w 的每一条路径都经过结点v, 则称结点 v 支配(Dominate)结点 w

无价值支配结点(TrivialDominators): 支配结点r和w一般称为无价值支配节点

完美支配节点/严格支配节点: Dom(w) - w

直接支配节点(Immediate Dominator): IDom, v为w的支配节点且被{Dom(w) - w}支配, 则v为w 的直接支配节点

支配树: 使用直接支配节点构造的树

支配边界(Dominance Frontier): y是x的一个支配边界, 当且仅当X支配Y的一个前驱节点,且x不严格支配y。x的支配边界包括多个节点,是集合。

后支配(Post-Dominance): 如果从结点w出发到达每一个CFG出口(CFG可能有多个出口)的每一条路径都经过结点v,则称结点v后支配(Post-Dominate)结点w

## Interpretation

代码下/上移: 采用支配/逆支配关系得到一个较好基本块的位置

插入Phi: 根据支配信息计算支配边界,支配边界是汇聚点。

控制依赖: 通过逆支配信息计算逆支配边界,逆支配边界是分叉点

## LLVM 支配树实现

采用Semi-NCA(SemiDominator-Nearest Common Ancestor)算法

增量构建DT(Domainance tree)基于两个特性父特性,兄弟特性; 而只有同时满足父特性和兄弟特性的树是DT。(参考论文:Dominator tree certification and divergent spanning trees)

父特性: DT中所有从一个可达顶点v出发的边记为(v，w), 有t(w)是v的祖先, 其中t(w)是指w的父结点

兄弟特性: 结点v不支配结点w, 如果v和w是兄弟

边插入只会影响父特性的变化, 边删除只会影响兄弟特性的变化

### 半支配

CFG图采用DFS遍历,构成一个DFST,遍历每一个节点时记录DFS遍历节点的序号，记为dfnum

前向边(Forwarding Edge): DFS中有一条根结点出发的路径,且路径包含从结点v到达结点w,如果dfnum(v) < dfnum(w)，并且结点w是v的后继结点，则称v到w有一个前向边

后向边(BackEdge): 在DFS中有一条根结点出发的路径,且路径包含从结点v到达结点w,如果dfnum(v)>dfnum(w),并且结点w是v的祖先,则称v到w有一个后向边

树枝或交叉边(CrossEdge): 在DFS中有一条从结点v到结点w的路径,如果dfnum(v)>dfnum(w),并且w既不是v的后继也不是v的祖先,则称v到w有一个树杈(此时v和w位于DFS不同的子树中)

半支配: CFG的DFS遍历中, 有边(t, w), 且 dfnum(t) > dfnum(w); 说明(t, w)不是前向边, w是汇聚点; 同时也说明在之前一定有一个分叉点u, 称u为w的半支配节点, 需要注意半支配节点不一定支配w。

```
CFG:
     ---
    /   \
1->2->3->4
 \   /
  ---
DFST: 
1->2  3->4
 \   /
  ---
or
     ---
    /   \
1->2  3  4
 \   /
  ---
```

## 支配边界实现

采用《A linear time algorithm for placing φ-nodes》的算法

在支配树的基础上构建DJ-Graph, 添加 Join-edge, 基于DJ-Graph 直接计算支配边界

Join 边定义: 假设x到y有一条CFG上的直接边, 如果x不是y的IDom, 则称这条边是一条Join-edge

通过DJ-Graph可以得到信息:
1. 对join-edge边x到y来说, y属于x的支配边界集合, y也属于x的祖先的支配边界集合
2. 如果y属于x的支配边界, y在支配树的层次小于等于x的层次
3. 如果y属于x的支配边界, 当且仅当x存在一个子树记为z, 有z到y是join-edge, 且y的层次小于等于x的层次

## 支配树构造算法比较

### 定义法
从图中删除节点v, 如果s节点不能到达w, 则v支配w
1. 依次删除图中顶点
2. 遍历更新后的图,记录支配关系
3. 构造支配树

### 数据流分析法
根据CFG建立数据流方程,迭代求解每个节点的支配节点

IN[B]为基本块B入口的支配节点集合, OUT[B]为出口处的支配节点集合
1. OUT[Entry] = {Entry}
2. OUT[B] = IN[B] ∪ {B}, B != Entry
3. IN[B] = for any P in Pred[B]: ∪ OUT[P], B!= Entry

### SLT 
Simple Lengauer-Tarjan
1. 初始化, 遍历得到DFS树和标号
2. 从DFS标号大到小求sdom
3. 求出所有能确定的idom, 剩下的点记录和哪个点的idom相同
4. 从DFS标号小到大求所有点idom

```

```

### Semi-NCA


## 判断支配关系

### 遍历支配树
由于已知支配树，所以可以通过遍历支配树进行判断

1. 计算结点x和y的高度, 高度小的结点可能会支配另一个结点, 假设x的高度小, 且高度记为hx, 结点y的高度大;
2. 对于结点y从DT中遍历其IDom,直到IDom的高度小于等于hx;
3. 判断IDom和x是否相等, 如果相等说明x支配y, 否则x不支配y;

### 高效
对DT树进行DFS遍历,增加两个属性: DFSNUMIn, DFSNUMOut

DFSNUMIn 为第一次访问节点的序号; DFSNUMOut 为最后一个访问节点的序号

有如下特性:
1. 父结点的DFSNumIn一定小于子结点的DFSNumIn
2. 左边兄弟结点的DFSNumIn一定小于右边兄弟结点的DFSNumIn
3. 子结点的DFSNumOut一定小于父结点的DFSNumOut
4. 左边兄弟结点的DFSNumOut一定小于右边兄弟结点的DFSNumOut

如果同时有:
1. x.DFSNumIn小于等于y.DFSNumIn
2. x.DFSNumOut大于等于y.DFSNumOut
则x支配y

