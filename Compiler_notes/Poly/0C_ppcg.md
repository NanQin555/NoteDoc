
ppcg_scop: SCOP的表示供PPCG内部使用

```
struct ppcg_scop {
	struct ppcg_options *options;

    // 相应程序文本的文件偏移
	unsigned start;
	unsigned end;          

    // 对参数的约束
	isl_set *context;
    // 所有迭代域的结合
	isl_union_set *domain;
    // 包含带有调用表达式语句的迭代域
	isl_union_set *call;
    // 包含所有潜在的读取访问
	isl_union_map *tagged_reads;
	isl_union_map *reads;
    // 包含潜在的读取访问
	isl_union_map *live_in;
    // 包含所有潜在的写入访问
	isl_union_map *tagged_may_writes;
	isl_union_map *may_writes;
	isl_union_map *tagged_must_writes;
    // 包含所有确定的写入访问
	isl_union_map *must_writes;
    // 包含潜在的潜在写入访问没有被任何杀人或其他写入杀死
	isl_union_map *live_out;
    // 包含所有确定的杀戮访问
	isl_union_map *tagged_must_kills;
	isl_union_map *must_kills;

    // 映射标记为相应未标记的迭代域
	isl_union_pw_multi_aff *tagger;

    // 是所有独立过滤器的结合
	isl_union_map *independence;

    // 表示潜在的流依赖性
	isl_union_map *dep_flow;
	isl_union_map *tagged_dep_flow;
    // 表示潜在的错误（反和输出）依赖性
	isl_union_map *dep_false;
    // 表示应强制执行的有效性约束
	isl_union_map *dep_forced;
    // 表示顺序依赖关系
	isl_union_map *dep_order;
	isl_union_map *tagged_dep_order;
    // 代表原始调度顺序
	isl_schedule *schedule;

    // 包含SCOP使用的所有变量名称
	isl_id_to_ast_expr *names;
    // 原始的pet_scop
	struct pet_scop *pet;
};
```