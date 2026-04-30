#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Floyd 算法模板
 * 适用场景：全源最短路，顶点数 N 通常 <= 500
 * 时间复杂度：O(N^3)
 * 空间复杂度：O(N^2)
 */

// 使用 0x3f3f3f3f 是竞赛界的惯例：
// 1. 足够大，两倍相加也不会溢出 int (约 1e9)
// 2. 可以使用 memset(d, 0x3f, sizeof(d)) 快速初始化
const int INF = 0x3f3f3f3f;

void floyd() {
    int n, m; // n: 点数, m: 边数
    if (!(cin >> n >> m)) return;

    // 1. 初始化距离矩阵
    // 使用 vector 或静态数组均可，注意点编号通常从 1 开始
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));

    for (int i = 1; i <= n; ++i) dist[i][i] = 0;

    // 2. 读入边
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        // 如果是无向图，则 dist[u][v] = dist[v][u] = min(...)
        // 处理重边：只保留权值最小的那条
        dist[u][v] = min(dist[u][v], w);
    }

    // 3. 核心三重循环 (k 必须在最外层)
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            // 优化：如果起点到中间点不可达，直接跳过
            if (dist[i][k] == INF) continue; 
            
            for (int j = 1; j <= n; ++j) {
                // 只有当中间点到终点也可达时，尝试更新
                if (dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // 4. 输出结果或处理查询
    // 示例：输出点 1 到点 n 的最短路
    if (dist[1][n] == INF) cout << "impossible" << endl;
    else cout << dist[1][n] << endl;

    /* 
    // 附：负环检测逻辑
    for (int i = 1; i <= n; ++i) {
        if (dist[i][i] < 0) {
            // 存在负环
        }
    }
    */
}

int main() {
    // 优化 IO 效率，OJ 必备
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    floyd();

    return 0;
}