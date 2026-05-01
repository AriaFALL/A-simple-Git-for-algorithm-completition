#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 定义无穷大，防止溢出，通常用 0x3f3f3f3f
const int INF = 0x3f3f3f3f;

/**
 * Prim算法求最小生成树 (堆优化版)
 * @param n 节点总数 (假设节点编号从 1 到 n)
 * @param adj 邻接表，adj[u] 存储 {v, weight} 表示 u 到 v 有一条权重为 weight 的边
 * @return 最小生成树的总权重。如果图不连通，返回 -1
 */
long long prim(int n, const vector<vector<pair<int, int>>>& adj) {
    // 记录最小生成树的总权重，注意使用 long long 防止累加溢出
    long long mst_weight = 0; 
    
    // 记录已经加入最小生成树的节点数
    int node_count = 0;       
    
    // visited[i] 表示节点 i 是否已经加入到最小生成树中
    vector<bool> visited(n + 1, false); 
    
    // 优先队列（小根堆），存储 {距离/权重, 节点编号}
    // C++ 中 priority_queue 默认是大根堆，使用 greater 变成小根堆
    // 必须把权重放在 pair 的第一个位置，因为 pair 默认按第一个元素排序
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    // 从节点 1 开始构建 MST（也可以是任意存在的节点）
    // 初始状态：到节点 1 的距离为 0
    pq.push({0, 1});
    
    while (!pq.empty()) {
        // 取出当前距离 MST 最近的节点
        auto [weight, u] = pq.top();
        pq.pop();
        
        // 【核心操作：懒惰删除 (Lazy Deletion)】
        // 因为同一个节点可能多次被放入堆中（每次发现更短的边时），
        // 如果该节点已经被处理过，直接跳过，这比在堆中查找并更新它的值要高效得多。
        if (visited[u]) continue;
        
        // 将该节点标记为已加入 MST
        visited[u] = true;
        
        // 累加权重，并增加已加入的节点计数
        mst_weight += weight;
        node_count++;
        
        // 遍历当前节点的所有邻居
        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            
            // 如果邻居还没加入 MST，则将其加入候选队列
            if (!visited[v]) {
                pq.push({w, v});
            }
        }
    }
    
    // 连通性检查：如果加入 MST 的节点数等于总节点数，说明图是连通的，成功构建 MST
    if (node_count == n) {
        return mst_weight;
    } else {
        return -1; // 图不连通，无法构成包含所有节点的生成树
    }
}

// --- OJ 测试样例骨架 ---
int main() {
    // 优化 I/O 速度，OJ 必备
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; // n 个点, m 条边
    if (cin >> n >> m) {
        vector<vector<pair<int, int>>> adj(n + 1);
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            // 无向图，双向建边
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        long long ans = prim(n, adj);
        if (ans == -1) cout << "orz" << "\n"; // 不连通时的输出（依据具体题目而定）
        else cout << ans << "\n";
    }
    return 0;
}