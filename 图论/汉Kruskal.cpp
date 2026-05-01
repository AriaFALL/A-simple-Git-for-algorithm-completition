#include <vector>
#include<iostream>
#include<algorithm>
using namespace std;

// 根据题目数据范围修改
// 假设点数最大 2e5，边数最大 2e5
const int N = 200005;
const int M = 200005;

// 定义边结构体
struct Edge {
    int u, v, w;  // 边的两个端点、边权

    // 重载 < 运算符，供 sort 排序使用
    // 按边权从小到大排序
    bool operator < (const Edge& other) const {
        return w < other.w;
    }
};

int n, m;          // n个点，m条边
Edge edges[M];     // 存储所有边
int fa[N];         // 并查集父节点数组

// 并查集查找函数：查找x所在集合的代表元（根）
// 使用路径压缩优化，提高效率
int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

// Kruskal 算法
// 返回值：
//   如果图连通，返回最小生成树总权值
//   如果图不连通，返回 -1
long long kruskal() {
    // 第一步：边按权值从小到大排序
    sort(edges + 1, edges + m + 1);

    // 第二步：初始化并查集
    // 一开始每个点自成一个集合
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }

    long long res = 0;  // 最小生成树总权值
    int cnt = 0;        // 当前已经选了多少条边

    // 第三步：依次枚举排序后的每条边
    for (int i = 1; i <= m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        // 找到u和v所在集合的根
        int fu = find(u);
        int fv = find(v);

        // 如果u和v不在同一个连通块中
        // 说明加这条边不会形成环，可以加入最小生成树
        if (fu != fv) {
            fa[fu] = fv;   // 合并两个集合
            res += w;      // 累加边权
            cnt++;         // 已选边数+1

            // 最小生成树恰好需要 n-1 条边
            // 达到后可以提前结束
            if (cnt == n - 1) break;
        }
    }

    // 如果最终选出的边数不足 n-1
    // 说明图不连通，无法形成最小生成树
    if (cnt != n - 1) return -1;

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    // 读入m条无向边
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    long long ans = kruskal();

    if (ans == -1) cout << "impossible\n";
    else cout << ans << '\n';

    return 0;
}
