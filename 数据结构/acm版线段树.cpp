#include<bits/stdc++.h>   // 万能头：竞赛里一次性包含所有标准库，省去逐个 include

using namespace std;
#define ll long long       // 把 long long 缩写为 ll，防止数值溢出（区间最值/和可能很大）

const int N = 200000 + 5;  // 最大数据规模，+5 是给「下标从 1 开始」留的冗余

/* ---------- 线段树数组说明 ----------
   a[i]  原数组，下标从 1 开始，[1, n]
   mx[p] 节点 p 所管辖区间内的最大值（线段树本体）
   编号规则（堆式存储，不用指针）：
       节点 p 的左儿子 = p << 1   （即 p * 2）
       节点 p 的右儿子 = p << 1 | 1（即 p * 2 + 1，"<<" 优先级高于 "|"）
       根节点固定为 1，管辖整个区间 [1, n]
   线段树深度约 log2(n)，最后一层可能不满，最坏用到 < 4n 个节点，
   所以开 N << 2（4 倍）空间一定不会越界。 */
ll a[N], mx[N << 2];

/* 由左右儿子推出父亲节点的值（向上合并信息）
   前提：左右儿子的值都已经算正确。
   调用时机：build 递归回溯时、update 递归回溯时。 */
void pushup(int p) {
    mx[p] = max(mx[p << 1], mx[p << 1 | 1]);   // 父亲管辖区间的最大值 = 两个儿子最大值的较大者
}

/* 建树：对节点 p 所管辖的区间 [l, r] 建立线段树
   参数 p     ：节点编号
   参数 l, r  ：该节点管辖的闭区间 [l, r]
   首次调用   ：build(1, 1, n)，时间复杂度 O(n) */
void build(int p, int l, int r) {
    if (l == r) {      // 区间长度为一，就是叶子节点
        mx[p] = a[l];  // 叶子直接对应原数组中的单个元素
        return;
    }

    int mid = (l + r) >> 1;         // 取中点划分区间（>>1 等价于 /2 向下取整，比除法快）
    build(p << 1, l, mid);          // 递归建左子树，区间 [l, mid]
    build(p << 1 | 1, mid + 1, r);  // 递归建右子树，区间 [mid + 1, r]
    pushup(p);                      // 两个儿子建好后回填自己，保证 mx[p] 正确
}

/* 单点修改：把位置 x 上的值改成 v（是「赋值覆盖」，不是累加）
   只有 x 到根的一条链会变化，所以每次只需要 O(log n)
   参数 p     ：节点编号
   参数 l, r  ：当前节点管辖的区间 [l, r]
   参数 x, v  ：把 a[x] 改为 v */
void update(int p, int l, int r, int x, ll v) {
    if (l == r) {     // 递归到叶子，此时必有 l == r == x
        mx[p] = v;    // 直接覆盖成新值
        return;
    }

    int mid = (l + r) >> 1;

    // 只往 x 所在的那一侧递归，另一侧完全不动
    if (x <= mid) update(p << 1, l, mid, x, v);        // x 在左半区间
    else update(p << 1 | 1, mid + 1, r, x, v);         // x 在右半区间

    pushup(p);        // 回溯时重新计算沿途每个父亲的 mx 值
}

/* 区间查询：求 [ql, qr] 内的最大值，时间复杂度 O(log n)
   核心思想：把询问区间拆成若干个「完全的节点区间的并」。
            一旦当前区间被询问区间完全包含，就直接用 mx[p] 回答；
            否则继续往下递归，只递归与 [ql, qr] 有交集的一侧。
   参数 p     ：节点编号
   参数 l, r  ：当前节点管辖的区间 [l, r]
   参数 ql, qr：询问区间，注意必须满足 ql <= qr，否则取 max 的结果无意义 */
ll query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {   // 当前区间被询问区间完整覆盖 → 整段信息可直接使用
        return mx[p];
    }

    int mid = (l + r) >> 1;
    ll ans = LLONG_MIN;         // 初值取 long long 的负无穷，保证第一次 max 一定被替换

    // 左半区间 [l, mid] 与询问区间有交集才递归（区间查询没有 if 判断就会多递归，且可能答案错误）
    if (ql <= mid) ans = max(ans, query(p << 1, l, mid, ql, qr));
    // 右半区间 [mid + 1, r] 与询问区间有交集才递归
    if (qr > mid) ans = max(ans, query(p << 1 | 1, mid + 1, r, ql, qr));

    return ans;                 // 两边答案取最大
}

/* 使用说明（本题 main 里留空，按题目要求自行补全输入输出）：
   int n;  cin >> n;
   for (int i = 1; i <= n; i++) cin >> a[i];
   build(1, 1, n);                 // 建树
   update(1, 1, n, x, v);          // 单点改：a[x] = v
   cout << query(1, 1, n, l, r);   // 区间查：[l, r] 的最大值

   补充：本模板是「单点修改 + 区间查最值」的无懒标记线段树；
        如果要区间修改（区间加/区间赋值），需要带 lazy 标记 + pushdown 下传，
        只把 pushup 里的 max 换成「加法」或「min」，就能变成区间和/区间最小值线段树。 */
int main(){



}
