/*最长上升子序列（Longest Increasing Subsequence, LIS）
 *
 * ===== 问题定义 =====
 * 给定一个长度为 n 的数组 a[]，找出其中最长的严格递增子序列的长度。
 * 子序列不要求连续，但顺序必须与原序列保持一致。
 *
 * ===== 方法一：动态规划 O(n^2) =====
 * 状态定义：dp[i] 表示以 a[i] 结尾的最长上升子序列的长度。
 * 状态转移：dp[i] = max(dp[j] + 1) 其中 0 <= j < i 且 a[j] < a[i]
 * 边界条件：dp[i] = 1（每个元素自身就是一个长度为 1 的上升子序列）
 * 最终答案：max(dp[0], dp[1], ..., dp[n-1])
 *
 * 适用场景：n <= 5000，或需要输出具体的 LIS 序列时
 */
int LIS_DP(vector<int>& a) {
    int n = a.size();
    vector<int> dp(n, 1);
    int ans = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }
    return ans;
}

/* 输出具体 LIS 序列的版本（O(n^2)）
 * 通过 pre 数组记录每个位置的前驱下标，最后回溯得到序列
 */
vector<int> LIS_GetSequence(vector<int>& a) {
    int n = a.size();
    vector<int> dp(n, 1), pre(n, -1);
    int max_len = 1, end_idx = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                pre[i] = j;
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
            end_idx = i;
        }
    }
    
    // 回溯构造序列
    vector<int> seq;
    for (int i = end_idx; i != -1; i = pre[i]) {
        seq.push_back(a[i]);
    }
    reverse(seq.begin(), seq.end());
    return seq;
}

/* ===== 方法二：贪心 + 二分查找 O(n log n) =====
 * 核心思想：维护一个数组 tail，其中 tail[i] 表示长度为 i+1 的上升子序列的
 *           最小末尾元素。tail 数组一定是严格递增的。
 * 遍历每个元素 x：
 *   - 在 tail 中二分查找第一个 >= x 的位置（即 lower_bound）
 *   - 如果找到，则替换该位置的值为 x（让该长度的末尾变得更小，更有利于后续扩展）
 *   - 如果没找到（x 比所有 tail 都大），则追加到 tail 末尾（序列长度 +1）
 * 最终 tail 的长度就是 LIS 的长度。
 *
 * 注意：tail 数组本身不一定是 LIS 序列，它只保证长度正确。
 *
 * 适用场景：n 较大（n <= 10^5 甚至更大），只需要长度不需要具体序列
 */
int LIS_Greedy(vector<int>& a) {
    vector<int> tail;
    for (int x : a) {
        auto it = lower_bound(tail.begin(), tail.end(), x);
        if (it == tail.end()) {
            tail.push_back(x);      // x 比所有末尾都大，扩展序列
        } else {
            *it = x;                // 替换，让末尾变得更小
        }
    }
    return tail.size();
}

/* 非严格递增（即允许相等）的版本：最长不下降子序列（LNDS）
 * 区别仅在于将 lower_bound 改为 upper_bound
 * 因为允许相等，所以相等的元素可以接在后面，查找时要找第一个 > x 的位置
 */
int LNDS_Greedy(vector<int>& a) {
    vector<int> tail;
    for (int x : a) {
        auto it = upper_bound(tail.begin(), tail.end(), x);
        if (it == tail.end()) {
            tail.push_back(x);
        } else {
            *it = x;
        }
    }
    return tail.size();
}

/* ===== 方法三：树状数组 / 线段树优化 O(n log n) =====
 * 思路：将值域离散化后，用树状数组维护以某个值结尾的 LIS 最大长度。
 * 遍历 a[i] 时，查询值域 [1, a[i]-1] 中的最大长度，然后 +1 更新到 a[i] 位置。
 * 适用于带修改的变种题，或需要同时维护其他信息时。
 */
int LIS_BIT(vector<int>& a) {
    // 离散化
    vector<int> vals = a;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    
    int m = vals.size();
    vector<int> bit(m + 1, 0);
    
    auto query = [&](int x) -> int {
        int res = 0;
        for (; x > 0; x -= x & -x) res = max(res, bit[x]);
        return res;
    };
    auto update = [&](int x, int val) {
        for (; x <= m; x += x & -x) bit[x] = max(bit[x], val);
    };
    
    int ans = 0;
    for (int x : a) {
        int idx = lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
        int len = query(idx - 1) + 1;  // 查询比 x 小的值中的最大长度
        update(idx, len);
        ans = max(ans, len);
    }
    return ans;
}

/* ===== 最长公共上升子序列（Longest Common Increasing Subsequence, LCIS）=====
 *
 * ===== 问题定义 =====
 * 给定两个数组 a[1..n] 和 b[1..m]，求它们的最长公共上升子序列的长度。
 * 即子序列既是 a 的子序列，也是 b 的子序列，且严格递增。
 *
 * ===== 方法一：朴素 DP O(n * m^2) =====
 * 状态定义：dp[i][j] 表示 a[1..i] 和 b[1..j] 中，以 b[j] 结尾的 LCIS 长度。
 * 状态转移：
 *   - 如果 a[i] != b[j]，则 dp[i][j] = dp[i-1][j]
 *     （a[i] 不参与匹配，继承前 i-1 的结果）
 *   - 如果 a[i] == b[j]，则 dp[i][j] = max(dp[i-1][k] + 1)
 *     其中 1 <= k < j 且 b[k] < b[j]（即 b[k] < a[i]）
 *     （在 b[1..j-1] 中找一个结尾小于 b[j] 的最长 LCIS 接上）
 * 边界条件：dp[0][j] = dp[i][0] = 0
 * 最终答案：max(dp[n][1], dp[n][2], ..., dp[n][m])
 *
 * 适用场景：n, m <= 500，理解 LCIS 基本思想
 */
int LCIS_DP(vector<int>& a, vector<int>& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] != b[j - 1]) {
                dp[i][j] = dp[i - 1][j];
            } else {
                // 在 b[1..j-1] 中找结尾小于 b[j] 的最长 LCIS
                int max_len = 0;
                for (int k = 1; k < j; k++) {
                    if (b[k - 1] < b[j - 1]) {
                        max_len = max(max_len, dp[i - 1][k]);
                    }
                }
                dp[i][j] = max_len + 1;
            }
        }
    }
    
    int ans = 0;
    for (int j = 1; j <= m; j++) {
        ans = max(ans, dp[n][j]);
    }
    return ans;
}

/* ===== 方法二：优化 DP O(n * m) =====
 * 优化思路：在方法一中，当 a[i] == b[j] 时，我们需要在 b[1..j-1] 中
 * 找满足 b[k] < b[j] 的 dp[i-1][k] 的最大值。注意到这个最大值可以
 * 在遍历 j 的过程中同步维护，无需每次重新枚举。
 *
 * 具体做法：
 *   - 外层循环 i 固定，内层循环 j 从 1 到 m
 *   - 维护一个变量 max_len，表示当前 i 下，满足 b[k] < a[i] 的
 *     dp[i-1][k] 的最大值（k < j）
 *   - 当 b[j] < a[i] 时，更新 max_len = max(max_len, dp[i-1][j])
 *   - 当 b[j] == a[i] 时，dp[i][j] = max_len + 1
 *   - 当 b[j] != a[i] 时，dp[i][j] = dp[i-1][j]
 *
 * 进一步优化空间：由于 dp[i][j] 只依赖 dp[i-1][*]，可以压缩为一维数组。
 * dp[j] 表示当前 i 下，以 b[j] 结尾的 LCIS 长度。
 *
 * 适用场景：n, m <= 5000，竞赛常用模板
 */
int LCIS_Optimized(vector<int>& a, vector<int>& b) {
    int n = a.size(), m = b.size();
    vector<int> dp(m + 1, 0);  // dp[j] 表示以 b[j] 结尾的 LCIS 长度
    
    for (int i = 1; i <= n; i++) {
        int max_len = 0;  // 当前 i 下，满足 b[k] < a[i] 的最大 dp[k]（k < j）
        for (int j = 1; j <= m; j++) {
            if (b[j - 1] < a[i - 1]) {
                // b[j] 可以作为 a[i] 的前驱，更新 max_len
                max_len = max(max_len, dp[j]);
            } else if (b[j - 1] == a[i - 1]) {
                // b[j] 与 a[i] 相等，可以接在 max_len 后面
                dp[j] = max(dp[j], max_len + 1);
            }
        }
    }
    
    int ans = 0;
    for (int j = 1; j <= m; j++) {
        ans = max(ans, dp[j]);
    }
    return ans;
}

/* ===== 方法三：输出具体 LCIS 序列的版本 O(n * m) =====
 * 在优化 DP 的基础上，记录前驱信息以回溯构造序列。
 * pre[j] 记录以 b[j] 结尾的 LCIS 中，前一个元素在 b 中的下标（1-based）
 */
vector<int> LCIS_GetSequence(vector<int>& a, vector<int>& b) {
    int n = a.size(), m = b.size();
    vector<int> dp(m + 1, 0);
    vector<int> pre(m + 1, -1);  // 前驱下标（1-based）
    
    for (int i = 1; i <= n; i++) {
        int max_len = 0;
        int last_idx = -1;  // 当前最优前驱在 b 中的下标
        for (int j = 1; j <= m; j++) {
            if (b[j - 1] < a[i - 1]) {
                if (dp[j] > max_len) {
                    max_len = dp[j];
                    last_idx = j;  // 记录当前最优前驱
                }
            } else if (b[j - 1] == a[i - 1]) {
                if (max_len + 1 > dp[j]) {
                    dp[j] = max_len + 1;
                    pre[j] = last_idx;  // 记录前驱
                }
            }
        }
    }
    
    // 找到最优的结尾位置
    int end_idx = 0;
    for (int j = 1; j <= m; j++) {
        if (dp[j] > dp[end_idx]) {
            end_idx = j;
        }
    }
    
    // 回溯构造序列
    vector<int> seq;
    for (int i = end_idx; i != -1; i = pre[i]) {
        seq.push_back(b[i - 1]);
    }
    reverse(seq.begin(), seq.end());
    return seq;
}

/* ===== 相关经典题目 =====
 * 1. 最长上升子序列（模板题）：LeetCode 300
 * 2. 最长不下降子序列（允许相等）：将 lower_bound 改为 upper_bound
 * 3. 最长下降子序列 / 最长不上升子序列：将数组取反或反转后求 LIS
 * 4. 最长公共子序列（LCS）转 LIS：当其中一个序列无重复元素时，可映射后求 LIS
 * 5. 俄罗斯套娃信封问题（LeetCode 354）：二维 LIS，先按一维排序，再对另一维求 LIS
 * 6. 合唱队形（Luogu P1091）：正反各求一次 LIS，枚举最高点
 * 7. 拦截导弹（Luogu P1020）：LIS + Dilworth 定理（最少下降子序列覆盖数 = 最长上升子序列长度）
 * 8. 最长上升子序列的个数（LeetCode 673）：DP 时同时维护方案数
 * 9. 最长公共上升子序列（LCIS 模板题）：HDU 1423 / Codeforces 10D
 */

/* ===== 使用示例 =====
int main() {
    // ---- LIS 测试 ----
    vector<int> a = {10, 9, 2, 5, 3, 7, 101, 18};
    
    cout << "LIS (DP O(n^2)): " << LIS_DP(a) << endl;           // 输出 4
    cout << "LIS (Greedy O(n log n)): " << LIS_Greedy(a) << endl; // 输出 4
    cout << "LIS (BIT O(n log n)): " << LIS_BIT(a) << endl;      // 输出 4
    
    vector<int> seq = LIS_GetSequence(a);
    cout << "LIS Sequence: ";
    for (int x : seq) cout << x << " ";  // 输出 2 3 7 101
    cout << endl;
    
    vector<int> b = {1, 2, 2, 3, 1};
    cout << "LNDS (允许相等): " << LNDS_Greedy(b) << endl;       // 输出 4 (1,2,2,3)
    
    // ---- LCIS 测试 ----
    vector<int> c = {2, 3, 1, 4, 5};
    vector<int> d = {1, 2, 3, 4, 5};
    
    cout << "\nLCIS (DP O(n*m^2)): " << LCIS_DP(c, d) << endl;       // 输出 3 (2,3,4 或 2,3,5)
    cout << "LCIS (Optimized O(n*m)): " << LCIS_Optimized(c, d) << endl; // 输出 3
    
    vector<int> lcis_seq = LCIS_GetSequence(c, d);
    cout << "LCIS Sequence: ";
    for (int x : lcis_seq) cout << x << " ";  // 输出 2 3 4 或 2 3 5
    cout << endl;
    
    return 0;
}
*/
