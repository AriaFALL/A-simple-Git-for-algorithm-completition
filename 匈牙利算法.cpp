#include <iostream>
#include<vector>

using namespace std;

const int N = 1005; // 根据题目数据范围调整，比如 505, 100005 等

vector<int> g[N];   // 邻接表，g[u] 存左侧节点 u 指向的右侧节点
int match[N];       // match[v] = u 表示右侧节点 v 匹配了左侧节点 u
int vis[N];         // 时间戳数组，代替传统的 bool vis[N]
int timer;          // 全局时间戳

// 核心 DFS 寻找增广路
bool dfs(int u) {
    for (int v : g[u]) {
        if (vis[v] == timer) continue; // 当前轮次已经访问过
        vis[v] = timer; // 盖上本轮的时间戳
        
        // 如果 v 还没有匹配 (match[v] == 0)，或者 v 的原配 match[v] 能找到下家
        if (!match[v] || dfs(match[v])) {
            match[v] = u; // 牵手成功
            return true;
        }
    }
    return false;
}

void solve() {
    int n, m, e; 
    // n: 左侧节点数, m: 右侧节点数, e: 边数
    cin >> n >> m >> e;
    
    // 读入边
    for (int i = 1; i <= e; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v); // 只建单向边：左 -> 右
    }
    
    int ans = 0;
    // 遍历左侧节点，尝试匹配
    for (int i = 1; i <= n; i++) {
        timer++; // 开启新一轮，时间戳+1，完美替代 memset(vis, 0, sizeof(vis))
        if (dfs(i)) {
            ans++;
        }
    }
    
    cout << ans << "\n";
}

int main() {
    // 竞赛必加：解除 cin/cout 与 scanf/printf 的同步，极大地提速 I/O
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t = 1;
    // cin >> t; // 如果有多组测试数据 (Multi-testcases)
    while (t--) {
        solve();
    }
    return 0;
}