// =====================================================================
// 分组背包问题（背包 DP 系列之四）
//
// 【问题】物品被分成若干组，同一组内的物品【最多只能选一件】（也可以
//        整组都不选）。背包容积为 V，求能带走的最大总价值。
// 【状态】dp[j]：容积恰好为 j 时的最大价值
// 【转移】对每一组，dp[j] = max( 不选本组, 选本组内某件物品 )
// 【重点】一维写法中三重循环的顺序必须是：组 → 容量(倒序) → 组内物品，
//        这样保证每组最多只会被选中一件物品。
// 【复杂度】时间 O(组数 * V * 每组物品数)，空间 O(V)
//
//  ---- 输入样例 ----
//  8          <- 背包容积 V
//  3          <- 组数
//  2          <- 第 1 组有 2 件
//  3 4
//  2 3
//  2          <- 第 2 组有 2 件
//  1 2
//  4 6
//  2          <- 第 3 组有 2 件
//  2 4
//  3 5
//  ---- 输出 ----
//  answer: 13   选 组1的(2,3) + 组2的(4,6) + 组3的(2,4)
// =====================================================================
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, g;
    cin >> V >> g;
    // groups[i] 保存第 i 组内所有物品的 (重量, 价值)
    vector<vector<pair<int, int>>> groups(g);
    for (int i = 0; i < g; ++i) {
        int m;
        cin >> m;
        groups[i].resize(m);
        for (int j = 0; j < m; ++j)
            cin >> groups[i][j].first >> groups[i][j].second;
    }

    // ---------- 写法 1：一维 dp ----------
    vector<int> dp(V + 1, 0);
    for (int i = 0; i < g; ++i) {                       // 1. 先枚举组
        for (int j = V; j >= 0; --j) {                  // 2. 容量倒序
            for (auto &it : groups[i]) {                // 3. 组内物品
                if (j >= it.first)
                    dp[j] = max(dp[j], dp[j - it.first] + it.second);
            }
        }
    }

    // ---------- 写法 2：二维 dp（便于对照理解） ----------
    // dp2[i][j]：前 i 组、容积 j 的最大价值
    vector<vector<int>> dp2(g + 1, vector<int>(V + 1, 0));
    for (int i = 1; i <= g; ++i) {
        for (int j = 0; j <= V; ++j) {
            dp2[i][j] = dp2[i - 1][j];                  // 整组不选
            for (auto &it : groups[i - 1])
                if (j >= it.first)
                    dp2[i][j] = max(dp2[i][j],
                                    dp2[i - 1][j - it.first] + it.second);
        }
    }

    cout << "1D answer: " << dp[V] << '\n';
    cout << "2D answer: " << dp2[g][V] << "\n\n";

    cout << "final dp[0..V]:\n";
    for (int j = 0; j <= V; ++j) cout << dp[j] << ' ';
    cout << '\n';
    return 0;
}
