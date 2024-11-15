# TableGen

## Introduction

TableGen 是 DSL(Domain Specific Language)语言, 提供关键字, 标识符, 特殊运算符等信息

## 词法

数值字面量

字符串字面量

关键字: assert bit bits class code dag def dump else false foreach defm defset defvar field if include int let list multiclass string then true

标识符

特殊运算符

基本分隔符

## 语法

Type: bit int string dag bits<n> list<type>

Value: Simple Value, Simple ValueSuffix, Value "#" [Value]

记录: 记录可以被看作是有名字, 有类型, 具有特定属性的结构体

def直接定义一个记录,类似C的结构体

```
def record_example {
    int a = 1;
    string b = "hello";
}
```

class定义一个记录类, 类似Cpp中的class
```
class Inst {
    string asmname;
    bits<32> encoding;
}
def ADD: Inst{
    let asmname = "add";
    let encoding[31-26] = 1;
}
def MUL: Inst{
    let asmname = "mul";
    let encoding[31-26] = 2;
}
```

multiclass 一次定义多个class(多个class非常相似, 仅少数信息不同)
```
class Inst<bits<4> op, string desc> {
    bits<4> opcode = op;
    string name = desc;
}
multiclass RegInst {
    def rr: Inst<0b1111, "rr">;
    def rm: Inst<0b0000, "rm">;
}
defm MyBackend_:RegInst;
```

## TableGen 工具链

1. td -> record, 工具链前端
```
llvm-tblgen-Iyour_dir/llvm-project/llvm/include/-Iyour_dir/llvm-project/llvm/lib/Target/BPF--print-recordsyour_dir/llvm-project/llvm/lib/Target/BPF/BPF.td

```
2. 对记录中的信息进行抓取,分析,组合生成inc头文件
```
// 加入参数
-gen-dag-isel
```

MLIR是基于TD文件设计方言(Dialect), 算子(Operator)