// =====================================================================
// 多重背包问题（背包 DP 系列之三）
//
// 【问题】有 n 种物品，第 i 种的重量 w[i]、价值 v[i]，最多可用 c[i] 件。
//        背包容积为 V，求能带走的最大总价值。
// 【核心技巧：二进制拆分】
//   把“可用 c 件”按 1, 2, 4, 8, ... 打包：任意 0~c 件的取法都能由这
//   几个“二进制组”的组合表示。每组打包成一件 01 背包物品后，问题就
//   变成了普通的 0-1 背包，时间复杂度从 O(n*V*c) 降到 O(n*V*log c)。
//
//  ---- 输入样例 ----
//  3 10
//  3 4 2
//  4 5 2
//  2 3 3
//  ---- 输出（naive 指朴素三层循环，binary 指二进制拆分，两者互相验证）----
//  naive  (triple loop)  : 14
//  binary (bit-splitting): 14
// =====================================================================
#include <bits/stdc++.h>
using namespace std;

struct Item { int w, v, c; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, V;
    cin >> n >> V;
    vector<Item> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i].w >> a[i].v >> a[i].c;

    // ---------- 方法 1：朴素三层循环（不优化，便于验证） ----------
    // dp2[i][j]：前 i 种物品、容积 j 的最大价值；枚举第 i 种拿 k 件
    vector<vector<int>> dp2(n + 1, vector<int>(V + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= V; ++j) {
            dp2[i][j] = dp2[i - 1][j];          // 第 i 种一件都不拿
            for (int k = 1; k <= a[i].c; ++k)   // 拿 k 件第 i 种
                if (j >= k * a[i].w)
                    dp2[i][j] = max(dp2[i][j],
                                    dp2[i - 1][j - k * a[i].w] + k * a[i].v);
        }
    }

    // ---------- 方法 2：二进制拆分 → 转换成 01 背包 ----------
    vector<pair<int, int>> goods;               // (打包后单组重量, 单组价值)
    for (int i = 1; i <= n; ++i) {
        int num = a[i].c;
        for (int k = 1; k <= num; k <<= 1) {    // 1, 2, 4, ... 打包
            num -= k;
            goods.push_back({a[i].w * k, a[i].v * k});
        }
        if (num > 0)                            // 剩下的零头单独成组
            goods.push_back({a[i].w * num, a[i].v * num});
    }

    vector<int> dp(V + 1, 0);                   // 对打包后的物品跑 01 背包
    for (auto &g : goods)
        for (int j = V; j >= g.first; --j)
            dp[j] = max(dp[j], dp[j - g.first] + g.second);

    cout << "naive  (triple loop)  : " << dp2[n][V] << '\n';
    cout << "binary (bit-splitting): " << dp[V] << "\n\n";

    cout << "after bit-splitting, got " << goods.size() << " zero-one items:\n";
    for (auto &g : goods) cout << "  (w=" << g.first << ", v=" << g.second << ")\n";
    return 0;
}
