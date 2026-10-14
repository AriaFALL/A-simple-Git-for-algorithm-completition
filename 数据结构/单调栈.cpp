#include <bits/stdc++.h>
using namespace std;

/* ============================================================================
 * 单调栈（Monotonic Stack）
 * ============================================================================
 * 【解决什么问题】
 *   给定数组 a，求每个位置：
 *     - 左边第一个比它小 / 大的数
 *     - 右边第一个比它小 / 大的数
 *   朴素两重循环是 O(n^2)，单调栈可以做到 O(n)。
 *
 * 【核心思想】
 *   以「每个数右边第一个更大的数」为例：从右往左扫描，栈里存下标，
 *   对应元素从栈底到栈顶单调递减。栈里保存的是 i 右边「还有可能成为答案」
 *   的元素，并且越靠近栈顶、离 i 越近。
 *   扫到 a[i] 时：
 *     - 栈顶元素 <= a[i]：它不可能是 a[i] 的答案；而且对更左边的元素来说，
 *       a[i] 比它大、离得又更近，它以后也永远当不了答案，直接弹掉；
 *     - 弹到栈顶 > a[i]（或栈空）为止，此时栈顶就是 i 右边第一个比 a[i] 大的数。
 *   每个下标最多进栈一次、出栈一次，所以总复杂度 O(n)。
 *
 * 【四种组合怎么记】
 *   求「更大」=> 栈从底到顶单调递减，遇到更大的就弹栈顶
 *   求「更小」=> 栈从底到顶单调递增，遇到更小的就弹栈顶
 *   从右往左扫 => 得到右边的答案；从左往右扫 => 得到左边的答案
 *
 * 【严格 / 非严格（最容易 WA 的地方）】
 *   「第一个严格小于」：while (a[stk.top()] >= a[i]) pop   // 相等的也弹掉
 *   「第一个小于等于」：while (a[stk.top()] >  a[i]) pop   // 相等的保留
 *   等号写在哪一边，决定了答案是否允许相等，做题时先想清楚再写。
 *
 * 【常见应用】
 *   - 柱状图中最大的矩形（LeetCode 84）：对每根柱子找左右第一个更矮的
 *   - 接雨水（LeetCode 42）：按层计算，栈内维护递减的柱子高度
 *   - 子数组的最小值之和（LeetCode 907）：统计每个数作为最小值的区间数
 *   - 每日温度 / 下一个更大元素（LeetCode 739 / 496 / 503）
 *   - 去除重复字母、拼接最大数（LeetCode 316 / 321）
 * ========================================================================== */

/* ------------------------------- 核心模板 -------------------------------
 * 数组模拟栈：stk[1..tt] 存下标，tt == 0 表示栈空。
 * 以「每个数右边第一个比它大的数的下标」为例（洛谷 P5788）：
 *
 *   tt = 0;
 *   for (int i = n; i >= 1; i--) {
 *       while (tt && a[stk[tt]] <= a[i]) tt--;   // 不可能成为答案的弹掉
 *       ans[i] = tt ? stk[tt] : 0;               // 栈顶就是答案，0 表示没有
 *       stk[++tt] = i;                           // 当前下标入栈
 *   }
 *
 * 求另外三种只改两处：扫描方向、while 里的比较符。
 * 下面四个函数用 vector 写，逻辑与上面完全一致，方便直接调用。
 * ---------------------------------------------------------------------- */

// 左边第一个严格小于 a[i] 的下标，不存在返回 -1
vector<int> leftSmaller(const vector<int>& a) {
    int n = a.size();
    vector<int> res(n, -1), st;  // st 存下标，对应值从底到顶递增
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        res[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }
    return res;
}

// 左边第一个严格大于 a[i] 的下标，不存在返回 -1
vector<int> leftGreater(const vector<int>& a) {
    int n = a.size();
    vector<int> res(n, -1), st;  // st 对应值从底到顶递减
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] <= a[i]) st.pop_back();
        res[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }
    return res;
}

// 右边第一个严格小于 a[i] 的下标，不存在返回 -1
vector<int> rightSmaller(const vector<int>& a) {
    int n = a.size();
    vector<int> res(n, -1), st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        res[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }
    return res;
}

// 右边第一个严格大于 a[i] 的下标，不存在返回 -1
vector<int> rightGreater(const vector<int>& a) {
    int n = a.size();
    vector<int> res(n, -1), st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.back()] <= a[i]) st.pop_back();
        res[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }
    return res;
}

/* --------------------------- 应用一：柱状图最大矩形 ---------------------------
 * LeetCode 84 经典题。
 * 枚举「以某根柱子为高度」的矩形：左右各找到第一个比它矮的柱子，
 * 中间的部分就是它能扩展的最大宽度，面积 = 高度 * 宽度。
 * 技巧：在数组首尾各加一个高度 0 的哨兵。
 *   - 左哨兵保证栈永远不为空，省掉边界判断；
 *   - 右哨兵保证最后所有柱子都会被弹出结算，省掉收尾清栈。
 * -------------------------------------------------------------------------- */
int largestRectangleArea(const vector<int>& h) {
    vector<int> H;
    H.push_back(0);                       // 左哨兵
    for (int x : h) H.push_back(x);
    H.push_back(0);                       // 右哨兵
    vector<int> st;                       // 存下标，对应高度从底到顶递增
    int ans = 0;
    for (int i = 0; i < (int)H.size(); i++) {
        while (!st.empty() && H[st.back()] > H[i]) {
            int height = H[st.back()];
            st.pop_back();
            int left = st.back();         // 左边第一个比 height 矮的位置
            ans = max(ans, height * (i - left - 1));
        }
        st.push_back(i);
    }
    return ans;
}

/* ----------------------------- 应用二：接雨水 -----------------------------
 * LeetCode 42。栈内维护一个从底到顶递减的柱子高度序列。
 * 当遇到比栈顶高的柱子时，栈顶就是「凹槽的底部」：
 *   水的高度 = min(左边界高度, 右边界高度) - 底部高度
 *   水的宽度 = 右边界下标 - 左边界下标 - 1
 * 按层把水加起来即可。注意弹出底部后如果栈空，说明左边没有挡板，无法接水。
 * ------------------------------------------------------------------------ */
int trap(const vector<int>& h) {
    vector<int> st;
    int ans = 0;
    for (int i = 0; i < (int)h.size(); i++) {
        while (!st.empty() && h[st.back()] < h[i]) {
            int bottom = h[st.back()];
            st.pop_back();
            if (st.empty()) break;        // 左边没有挡板，接不住水
            int width = i - st.back() - 1;
            ans += (min(h[st.back()], h[i]) - bottom) * width;
        }
        st.push_back(i);
    }
    return ans;
}

/* -------------------------- 应用三：子数组最小值之和 --------------------------
 * LeetCode 907。换一个角度：统计每个 a[i] 是多少个子数组的最小值。
 *   left[i]  = 左边第一个比 a[i] 小的位置（严格小，相等的弹掉）
 *   right[i] = 右边第一个比 a[i] 小的位置（严格小）
 * 为了让「相等元素只被算一次」，一般规定：左边找严格小（弹 >=），
 * 右边找严格小或相等（弹 >），这样每个子数组的最小值归属唯一。
 * 以 i 为最小值的子数组个数 = (i - left[i]) * (right[i] - i)。
 * -------------------------------------------------------------------------- */
int sumSubarrayMins(const vector<int>& arr) {
    const int MOD = 1'000'000'007;
    int n = arr.size();
    vector<int> left(n), right(n), st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.back()] >= arr[i]) st.pop_back();
        left[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }
    st.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && arr[st.back()] > arr[i]) st.pop_back();
        right[i] = st.empty() ? n : st.back();
        st.push_back(i);
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans = (ans + (long long)arr[i] * (i - left[i]) * (right[i] - i)) % MOD;
    }
    return (int)ans;
}

/* ------------------------------ 输出辅助 ------------------------------ */
void printVec(const vector<int>& v) {
    for (int i = 0; i < (int)v.size(); i++) cout << v[i] << " \n"[i + 1 == (int)v.size()];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> a = {3, 4, 2, 7, 5};
    cout << "数组: ";
    printVec(a);
    cout << "下标: 0 1 2 3 4\n\n";

    cout << "左边第一个更小: ";
    printVec(leftSmaller(a));    // -1 0 -1 2 2
    cout << "左边第一个更大: ";
    printVec(leftGreater(a));    // -1 -1 1 -1 3
    cout << "右边第一个更小: ";
    printVec(rightSmaller(a));   // 2 2 -1 4 -1
    cout << "右边第一个更大: ";
    printVec(rightGreater(a));   // 1 3 3 -1 -1

    // 柱状图最大矩形：选高度 5 和 6 的两根，宽 2，面积 10
    cout << "\n柱状图最大矩形: " << largestRectangleArea({2, 1, 5, 6, 2, 3}) << " (预期 10)\n";

    // 接雨水：经典样例，答案是 6
    cout << "接雨水: " << trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}) << " (预期 6)\n";

    // 子数组最小值之和：[3] [3,1] [3,1,2] [3,1,2,4] [1] ... 合计 17
    cout << "子数组最小值之和: " << sumSubarrayMins({3, 1, 2, 4}) << " (预期 17)\n";

    return 0;
}
