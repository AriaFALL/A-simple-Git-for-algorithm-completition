#include <bits/stdc++.h>
using namespace std;

/* ============================================================================
 * 单调队列（Monotonic Queue / 滑动窗口）
 * ============================================================================
 * 【解决什么问题】
 *   1. 滑动窗口最值：长度为 k 的窗口在数组上滑动，
 *      O(n) 求出每个窗口的最大值 / 最小值（暴力是 O(nk)）。
 *   2. 单调队列优化 DP：把形如
 *          f[i] = max/min{ f[j] + w(i) }   (j 在某个滑动区间内)
 *      的转移，从 O(n^2) 降到 O(n)。
 *
 * 【核心思想】
 *   队列里存「下标」，对应元素从队首到队尾单调。
 *   - 队首：当前窗口的最值，也是窗口内最早进入、最靠左的候选；
 *   - 队尾：新元素入队前，把所有不可能再成为最值的元素弹掉
 *           （求最小值就弹掉所有 >= a[i] 的，求最大值就弹掉所有 <= a[i] 的）；
 *   - 队首下标超出窗口左边界就弹出（过期）。
 *   每个下标最多进队一次、出队一次，所以总复杂度 O(n)。
 *
 * 【顺序不能乱：过期 -> 弹尾 -> 入队 -> 取答案】
 *   1. 先弹掉队首过期的下标；
 *   2. 再从队尾弹掉不可能成为最值的下标；
 *   3. 当前下标入队；
 *   4. 此时队首才是当前窗口的答案（i >= k 时输出）。
 *   如果先取答案再入队，窗口会少一个元素；如果忘了过期，答案会用到窗口外的数。
 *
 * 【单调队列 vs 优先队列】
 *   优先队列（堆）也能求窗口最值，但要懒删除，复杂度 O(n log n)；
 *   单调队列是 O(n)，而且能顺便得到「最值所在下标」，DP 优化时必须用它。
 * ========================================================================== */

/* ------------------------------- 核心模板 -------------------------------
 * 数组模拟双端队列：
 *   int q[N];             // 存下标
 *   int head = 1, tail = 0;   // 队列区间 [head, tail]，head > tail 表示空
 *
 * 长度为 k 的滑动窗口最小值（洛谷 P1886 / AcWing 154）：
 *
 *   head = 1, tail = 0;
 *   for (int i = 1; i <= n; i++) {
 *       while (head <= tail && q[head] <= i - k) head++;      // 1. 队首过期
 *       while (head <= tail && a[q[tail]] >= a[i]) tail--;    // 2. 队尾弹掉 >= a[i] 的
 *       q[++tail] = i;                                        // 3. 入队
 *       if (i >= k) cout << a[q[head]] << " ";                // 4. 队首即最小值
 *   }
 *
 * 求最大值只需把第 2 步的 >= 改成 <=。
 * 下面用 deque 封装成函数，逻辑完全一致，方便直接调用。
 * ---------------------------------------------------------------------- */

// 长度为 k 的滑动窗口最大值，返回每个窗口的最大值
vector<int> windowMax(const vector<int>& a, int k) {
    deque<int> q;  // 存下标，对应值从队首到队尾递减
    vector<int> res;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!q.empty() && q.front() <= i - k) q.pop_front();   // 过期
        while (!q.empty() && a[q.back()] <= a[i]) q.pop_back();   // 不可能成为最大值
        q.push_back(i);
        if (i >= k - 1) res.push_back(a[q.front()]);
    }
    return res;
}

// 长度为 k 的滑动窗口最小值，返回每个窗口的最小值
vector<int> windowMin(const vector<int>& a, int k) {
    deque<int> q;  // 存下标，对应值从队首到队尾递增
    vector<int> res;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!q.empty() && q.front() <= i - k) q.pop_front();
        while (!q.empty() && a[q.back()] >= a[i]) q.pop_back();
        q.push_back(i);
        if (i >= k - 1) res.push_back(a[q.front()]);
    }
    return res;
}

/* ----------------------- 应用一：长度不超过 m 的最大子序和 -----------------------
 * 洛谷 P1714 切蛋糕 / AcWing 135 最大子序和。
 * 设前缀和 s[i] = a[1] + ... + a[i]，则以 j 结尾、长度不超过 m 的子段和为
 *     s[i] - min{ s[j] : i - m <= j <= i - 1 }
 * 用一个单调递增队列维护窗口 [i-m, i-1] 内 s 的最小值，O(n) 解决。
 *
 * 注意顺序：先弹过期 -> 再取答案 -> 最后把 i 入队，
 * 这样窗口恰好是 [i-m, i-1]，不会把 s[i] 自己减掉（否则答案恒为 0）。
 * ------------------------------------------------------------------------------ */
long long maxSubarraySumWithLimit(const vector<int>& a, int m) {
    int n = a.size();
    vector<long long> s(n + 1, 0);
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i - 1];

    deque<int> q;  // 存前缀和下标 j，s[j] 从队首到队尾递增
    q.push_back(0);
    long long ans = LLONG_MIN;
    for (int i = 1; i <= n; i++) {
        while (!q.empty() && q.front() < i - m) q.pop_front();  // 窗口左端 i-m
        ans = max(ans, s[i] - s[q.front()]);                    // 队首即最小前缀和
        while (!q.empty() && s[q.back()] >= s[i]) q.pop_back();
        q.push_back(i);
    }
    return ans;
}

/* ------------------------ 应用二：单调队列优化多重背包 ------------------------
 * 多重背包：物品体积 v、价值 w、数量 c，容量 V，求最大价值。
 * 朴素转移：f[j] = max{ f[j - k*v] + k*w }，0 <= k <= c（对每件物品）。
 * 按 j mod v 的余数 r 分组，令 j = r + k*v，则
 *     f[r + k*v] = max{ f[r + k'*v] - k'*w } + k*w,  k-c <= k' <= k-1
 * 括号里是一个长度为 c+1 的滑动窗口最大值，用单调队列维护即可 O(V) 处理一件物品。
 *
 * 细节：入队的是「上一轮」的 f 值 f_old[j] - k*w，
 * 所以必须先保存 base = f[j]，再更新 f[j]，最后用 base 入队。
 * ---------------------------------------------------------------------------- */
long long multipleKnapsack(int V, const vector<array<int, 3>>& items) {
    vector<long long> f(V + 1, 0);
    for (auto& it : items) {
        int v = it[0], w = it[1], c = it[2];
        for (int r = 0; r < v && r <= V; r++) {
            deque<pair<int, long long>> q;  // (k, f_old[r+k*v] - k*w)，值递减
            for (int k = 0; r + k * v <= V; k++) {
                int j = r + k * v;
                while (!q.empty() && q.front().first < k - c) q.pop_front();  // 超过 c 件
                long long base = f[j];                                        // 上一件物品的旧值
                if (!q.empty()) f[j] = max(f[j], q.front().second + 1LL * k * w);
                long long val = base - 1LL * k * w;
                while (!q.empty() && q.back().second <= val) q.pop_back();
                q.push_back({k, val});
            }
        }
    }
    return f[V];
}

// 朴素版多重背包（拆成 0/1 物品），只用来在 main 里对拍验证
long long naiveKnapsack(int V, const vector<array<int, 3>>& items) {
    vector<long long> f(V + 1, 0);
    for (auto& it : items) {
        int v = it[0], w = it[1], c = it[2];
        for (int t = 0; t < c; t++) {
            for (int j = V; j >= v; j--) {
                f[j] = max(f[j], f[j - v] + w);
            }
        }
    }
    return f[V];
}

/* ------------------------------ 输出辅助 ------------------------------ */
void printVec(const vector<int>& v) {
    for (int i = 0; i < (int)v.size(); i++) cout << v[i] << " \n"[i + 1 == (int)v.size()];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> a = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    cout << "数组: ";
    printVec(a);
    cout << "窗口大小 k = " << k << "\n\n";

    cout << "每个窗口最大值: ";
    printVec(windowMax(a, k));   // 3 3 5 5 6 7
    cout << "每个窗口最小值: ";
    printVec(windowMin(a, k));   // -1 -3 -3 -3 3 3

    // 长度不超过 4 的最大子序和：选 5 1 -2 3，和为 7
    cout << "\n长度不超过 4 的最大子序和: "
         << maxSubarraySumWithLimit({1, -3, 5, 1, -2, 3}, 4) << " (预期 7)\n";

    // 多重背包：容量 10，物品 (v,w,c) = (2,3,3)、(3,4,2)
    vector<array<int, 3>> items = {{2, 3, 3}, {3, 4, 2}};
    long long fast = multipleKnapsack(10, items);
    long long slow = naiveKnapsack(10, items);
    cout << "\n多重背包（单调队列）: " << fast << "\n";
    cout << "多重背包（朴素对拍）: " << slow << (fast == slow ? "  [一致]" : "  [不一致!]") << "\n";

    return 0;
}
