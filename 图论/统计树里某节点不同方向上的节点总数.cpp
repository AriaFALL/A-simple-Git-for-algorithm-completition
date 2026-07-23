#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n;
vector<int> g[N];

int parent_[N];
int sz[N];

// 预处理每个节点的父亲和子树大小
void dfs(int u, int fa) {
    parent_[u] = fa;
    sz[u] = 1;

    for (int v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

// 获取删除节点 x 后，每个方向上的节点数量
vector<int> getDirections(int x) {
    vector<int> res;

    for (int y : g[x]) {
        int c;

        if (parent_[y] == x) {
            // y 是 x 的儿子
            // 这个方向上的节点数就是 y 的子树大小
            c = sz[y];
        } else {
            // y 是 x 的父亲
            // 这个方向上的节点数是除了 x 子树以外的所有节点
            c = n - sz[x];
        }

        res.push_back(c);
    }

    return res;
}
