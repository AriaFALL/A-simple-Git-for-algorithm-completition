#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 定义无穷大
const int INF = 1e9;
// 这样优先队列默认就会按照距离从小到大排序
#define PII pair<int,int>

int main() {
    // 优化标准 I/O 操作速度 (OJ 必备)
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, start;
    // 读取：节点数 n，边数 m，起点 start
    // 假设输入格式按照 OJ 惯例先给出图的规模
    if (!(cin >> n >> m >> start)) return 0;

    // 邻接表存图：adj[u] 存储与节点 u 相连的所有边 {v, weight}
    vector<vector<PII>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        // 因为是无向图，所以要存双向边
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // dist 数组记录起点到各个节点的最短距离，初始化为 INF
    vector<int> dist(n, INF);
    // st 数组记录节点是否已经确定了最短路 (OJ 中常用的常数优化)
    vector<bool> st(n, false);

    // 定义最小堆优先队列
    //queue里的PII,first为路径，second为编号
    priority_queue <PII,vector<PII>,greater<PII>> heap;

    // 1. 初始化起点
    dist[start] = 0;
    heap.push({0, start});

    // 2. Dijkstra 核心循环
    while (!heap.empty()) {
        // 取出当前距离最近的节点
        auto [d, u] = heap.top();
        heap.pop();

        // 如果该节点的最短路已经确定，直接跳过 (等价于 d > dist[u])
        if (st[u]) continue;
        st[u] = true; // 标记为已确定
        //dist里的pii,first为编号，second为路径
        // 3. 遍历所有出边，进行松弛操作
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                heap.push({dist[v], v}); // 将更新后的距离压入堆中
            }
        }
    }

    // 4. 输出结果 (OJ 标准输出格式，通常是空格分隔)
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INF) {
            cout << -1 << " "; // 如果不可达，输出 -1
        } else {
            cout << dist[i] << " ";
        }
    }
    cout << "\n";

    return 0;
}