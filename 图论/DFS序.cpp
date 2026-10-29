int timer = 0;
vector<int> tin(n+1), tout(n+1), rev(n+1);   // rev: 位置 -> 点编号

void dfs(int u, int fa) {
    tin[u] = ++timer;
    rev[timer] = u;          // 位置 timer 对应点 u
    for (int v : g[u])
        if (v != fa) dfs(v, u);
    tout[u] = timer;         // 离开时，timer 正好是子树里最后一个点
}
/*例子：
        1
       / \
      2   3
     / \   \
    4   5   6

u	tin[u]	tout[u]	子树对应的区间
1	1	6	[1,6] 全体
2	2	4	[2,4] = {2,4,5}
3	5	6	[5,6] = {3,6}
4	3	3	[3,3] = {4}
5	4	4	[4,4] = {5}
6	6	6	[6,6] = {6}
*/
//1. 判断祖先关系（O(1)）

bool isAnc(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}
//含义：v 的位置落在 u 的区间内 → v 是 u 子树里的点 → u 是 v 的祖先。

//2. 判断"y 在不在 x 子树里"（换根题常用）

if (tin[x] <= tin[y] && tin[y] <= tout[x]) {
    // y 在 x 的子树中
} else {
    // y 在 x 的父方向
}
//这题里 getSide(x, y) 的分支就靠它。

