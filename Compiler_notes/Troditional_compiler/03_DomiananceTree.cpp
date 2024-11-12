#include <iostream>
#include <list>
#define MAX 11
#define N 16
using namespace std;
// 邻接表索引表 0原图 1反图 2半支配树
int Index[3][MAX];
// 邻接表边
struct Edge {
    int y, next;
}edge[N*2];
// 邻接表插入
int count;
void insert(int lable, int x, int y) {
    edge[++count].y = y;
    edge[count].next = Index[lable][x];
    Index[lable][x] = count;
}

// ind 个数, edge 条数
int n, m;
void read() {
    cin >> n >> m;
    for(int i=0; i<m; i++) {
        int x, y;
        cin >> x >> y;
        insert(0, x, y);
        insert(1, y, x);
    } 
}
// dfsnum 为第几个被遍历到, desord为dfs遍历顺序, dfsfar为dfs遍历的父节点
int dfsnum[MAX], dfsord[MAX], dfsfar[MAX];
int cont;
void DFS(int i) {
    dfsnum[i] = ++cont;
    dfsord[cont] = i;
    // 每个后继节点
    for(int ind = Index[0][i]; ind; ind = edge[ind].next) {
        int node = edge[ind].y;
        if(dfsnum[node] == 0) {
            dfsfar[node] = i;
            DFS(node);
        }
    }
}

int idom[MAX], sdom[MAX];
// set 为有同一个sdom的并查集, minus_num 为集合中dfs序最小的sdom节点
int set[MAX], minus_num[MAX];

int find_set(int x) {
    if(x==set[x]) return x;
    int res = find_set(set[x]);
    if(dfsnum[sdom[minus_num[set[x]]]] < dfsnum[sdom[minus_num[x]]])
        minus_num[x] = minus_num[set[x]];
    return set[x] = res;
}
void domiananceTree() {
    DFS(1);
    // 均初始化为本身
    for(int i=1; i<=n; i++) sdom[i]=set[i]=minus_num[i]=i;
    // 逆 前序DFS序, 保证当前遍历节点的子孙一定被遍历过了
    for(int i=cont; i>=2; i--) {
        int node = dfsord[i];
        for(int pre = Index[1][node]; pre; pre = edge[pre].next) {
            int pre_node = edge[pre].y;
            // 剪枝？
            if(dfsnum[pre_node] == 0) continue;
            
            // 对当前节点做变换
            find_set(pre_node);
            if(dfsnum[sdom[minus_num[pre_node]]]<dfsnum[sdom[minus_num[node]]])
                sdom[node] = sdom[minus_num[pre_node]];
        }
        set[node] = dfsfar[node];

        insert(2, sdom[node], node);
        node = dfsfar[node];
        for(int i=Index[2][node]; i; i=edge[i].next) {
            int next = edge[i].y;
            find_set(next);
            idom[next] = node==sdom[minus_num[next]]?node:minus_num[next];
        }

        Index[2][node] = 0;
    }
    for(int i=2; i<=n; i++) {
        int node = dfsord[i];
        if(idom[node]^sdom[node])
            idom[node] = idom[idom[node]]; 
    }
}
int ans[MAX];
void print_ans() {
    for(int i=cont; i>=2; i--) {
        ans[idom[dfsord[i]]] +=  ++ans[dfsord[i]];
    }
    ++ans[1];

    for(int i=1; i<=n; i++) {
        cout << ans[i] << " ";
    }
    cout << " ";
}
int main () {
    read();
    domiananceTree();
    print_ans();
    return 0;
}