#include <vector>
#include <queue>

class Solution {
public:
    bool isBipartite(std::vector<std::vector<int>>& graph) {
        int n = graph.size();
        // 颜色数组：0 表示未染色，1 表示红色，-1 表示蓝色
        std::vector<int> colors(n, 0);
        
        // 遍历所有节点，处理非连通图
        for (int i = 0; i < n; ++i) {
            if (colors[i] == 0) {
                std::queue<int> q;
                q.push(i);
                colors[i] = 1; // 起点染成红色
                
                while (!q.empty()) {
                    int node = q.front();
                    q.pop();
                    
                    // 遍历当前节点的所有邻居
                    for (int neighbor : graph[node]) {
                        if (colors[neighbor] == colors[node]) {
                            // 发现同色相邻，不是二分图
                            return false; 
                        }
                        if (colors[neighbor] == 0) {
                            // 未染色则染成相反颜色，并入队
                            colors[neighbor] = -colors[node];
                            q.push(neighbor);
                        }
                    }
                }
            }
        }
        return true;
    }
};