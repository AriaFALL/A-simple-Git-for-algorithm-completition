#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;   // 最大顶点数，按题目调整
const int LOG = 20;        // 2^20 > 2e5，按 N 调整：LOG = ceil(log2(N)) + 1

vector<int> adj[MAXN];
int up[MAXN][LOG];         // up[u][k]：u 向上跳 2^k 步到达的祖先
int depth[MAXN];           // 深度，根为 1
int N;

// BFS 预处理
void bfs(int root) {
    queue<int> q;
    q.push(root);
    depth[root] = 1;
    up[root][0] = root;    // 根的父节点设为自己，防止越界
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (v == up[u][0]) continue;  // 跳过父节点
            depth[v] = depth[u] + 1;
            up[v][0] = u;
            for (int k = 1; k < LOG; k++) {
                up[v][k] = up[ up[v][k - 1] ][k - 1];
            }
            q.push(v);
        }
    }
}

// 查询 LCA
int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    // 将 u 跳到与 v 同深度
    int diff = depth[u] - depth[v];
    for (int k = 0; k < LOG; k++) {
        if (diff >> k & 1) {
            u = up[u][k];
        }
    }
    if (u == v) return u;
    // 一起向上跳，直到 LCA 的子节点
    for (int k = LOG - 1; k >= 0; k--) {
        if (up[u][k] != up[v][k]) {
            u = up[u][k];
            v = up[v][k];
        }
    }
    return up[u][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    bfs(1);  // 以 1 为根

    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }
    return 0;
}