// =====================================================================
// 完全背包问题（背包 DP 系列之二）
//
// 【问题】有 n 种物品，第 i 种的重量 w[i]、价值 v[i]，每种物品都有
//        【无限件】。背包容积为 V，求能带走的最大总价值。
// 【状态】dp[j]：容积恰好为 j 时的最大价值
// 【转移】dp[j] = max(dp[j], dp[j - w[i]] + v[i])
// 【重点】与 01 背包的唯一差别：容积 j 改为【正序】枚举。正序时
//        dp[j-w[i]] 可能已经被本轮第 i 种物品更新过，相当于同一种物品
//        可以反复加入背包，从而表达“无限次使用”的语义。
// 【复杂度】时间 O(n*V)，空间 O(V)
//
//  ---- 输入样例 ----
//  3 10
//  2 3
//  3 4
//  4 7
//  ---- 输出（correct 指按完全背包写的正序版本，wrong 指错写成 01 的倒序版本）----
//  correct (complete knapsack, j asc)  : 17   拿 4+4+2，价值 7+7+3
//  wrong   (treated as 0-1, j desc)    : 14   每种最多 1 件只能拿 4+3+2
// =====================================================================
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, V;
    cin >> n >> V;
    vector<int> w(n + 1), v(n + 1);
    for (int i = 1; i <= n; ++i) cin >> w[i] >> v[i];

    // correct[]：完全背包，容积正序枚举，允许同种物品无限取
    vector<int> correct(V + 1, 0);
    for (int i = 1; i <= n; ++i)
        for (int j = w[i]; j <= V; ++j)          // ★ 正序
            correct[j] = max(correct[j], correct[j - w[i]] + v[i]);

    // wrong[]：故意把容积倒序枚举（这是 01 背包的写法）
    // —— 用来对照，证明“枚举顺序”决定了背包的种类
    vector<int> wrong(V + 1, 0);
    for (int i = 1; i <= n; ++i)
        for (int j = V; j >= w[i]; --j)          // ★ 倒序
            wrong[j] = max(wrong[j], wrong[j - w[i]] + v[i]);

    cout << "correct (complete knapsack, j asc)  : " << correct[V] << '\n';
    cout << "wrong   (treated as 0-1, j desc)    : " << wrong[V] << "\n\n";

    cout << "correct dp[0..V]:\n";
    for (int j = 0; j <= V; ++j) cout << correct[j] << ' ';
    cout << '\n';
    return 0;
}
