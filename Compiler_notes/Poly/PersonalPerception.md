语句实例 与 执行顺序

执行顺序是时间表

依赖关系 指向改变（前/后）是违法的

```
for i in [1,4]
    S: A[i] = A[i-1]

for i in [4,1]
    S: A[i] = A[i-1]
```

S语句集合：  { S[i] | 1<=i<=4 }
            { S[i] | 1<=i<=4 }

schedule:   { S[i] -> i}
            { S[i] -> 5-i}
            字典序比较

data dependency:    { S[i], S[i+1] | 1<=i<=3 }