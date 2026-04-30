#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
=============================================================================
【SPFA 算法核心思想】
全称：Shortest Path Faster Algorithm (基于队列优化的 Bellman-Ford)
核心：只有距离刚刚被更新过的点，才有可能去更新它的邻居。
数据结构：
  1. dist[]: 距离数组
  2. queue:  存储“距离变短了，需要去通知邻居”的点
  3. st[]:   布尔数组，记录某个点当前是否已经在队列中（防止同一个点在队列里堆积）
=============================================================================
*/

// 邻接表的边结构体（只需要存终点和权重，因为起点就是数组的索引）
struct Edge {
    int v; // 终点
    int w; // 权重
};

const int INF = 0x3f3f3f3f;
const int MAXN = 100005; // 假设最多 10万 个点

vector<Edge> adj[MAXN];  // 邻接表存图：adj[u] 里面存着从 u 出发的所有边
int dist[MAXN];          // 最短距离数组
bool st[MAXN];           // 状态数组：点是否在队列中 (st = state)

void spfa(int start, int n) {
    // 1. 初始化距离
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        st[i] = false;
    }
    
    // 2. 初始化队列
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    st[start] = true; // start 进入了队列，打上标记
    
    // 3. 核心队列循环
    while (!q.empty()) {
        int u = q.front(); // 取出队头元素 u
        q.pop();
        
        // 【关键点】：u 被取出了，所以它现在不在队列里了，标记为 false！
        // 这样以后如果 u 的距离再次变短，它还能重新进队。
        st[u] = false; 
        
        // 遍历从 u 出发的所有邻居 v
        for (auto edge : adj[u]) {
            int v = edge.v;
            int w = edge.w;
            
            // 松弛操作：如果通过 u 走到 v 更近
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w; // 更新 v 的最短距离
                
                // 如果 v 被更新了，说明 v 拿到了更短的距离，它有资格去更新别人了！
                // 检查 v 现在是否在队列里，如果不在，就把它塞进去
                if (!st[v]) {
                    q.push(v);
                    st[v] = true; // 标记 v 已经进队
                }
            }
        }
    }
}

// 扩展：如何判断负权回路？
// 开一个数组 cnt[MAXN] 记录每个点进队的次数。
// 如果某个点进队次数 >= n，说明存在负权回路！