//1）子树加、单点查
// 操作：subtree(u) += v
tag[u] += v;

// 查询点 x：自顶向下累加（父 -> 子）
// 遍历序 order 满足「父先于子」（BFS 序即可）
for (int u : order)
    for (int v : g[u]) if (v != par[u])
        tag[v] += tag[u];

// 现在 tag[x] 就是 x 被加的总量
//为什么对？ tag[u] 表示"整个 u 子树加 v"，它会沿所有后代传下去，正好让子树每个点都 +v。✓

//2）补集加 comp(u) += v（即 V \ subtree(u) 加 v）
globalAdd += v;      // 全树加
tag[u]   -= v;       // 子树减回去

// 查询：tag[x] + globalAdd
自顶向下合并后，subtree(u) 里的点 tag 累计 -v，加 globalAdd 得 0；外面得 v。✓

//3）路径点加 u→v 上每个点 +1
tag[u]++, tag[v]++, tag[lca]--, tag[par[lca]]--;

// 自底向上合并（子 -> 父），order 逆序即可
for (int i = n-1; i >= 0; i--) {
    int u = order[i];
    if (par[u]) tag[par[u]] += tag[u];
}
// 现在 tag[x] 就是点 x 被路径覆盖的次数
//4）路径边加 u→v 上每条边 +1
tag[u]++, tag[v]++, tag[lca] -= 2;
// 同样自底向上合并，tag[x] = 边 (par[x], x) 被覆盖次数
//注意：3、4 的自底向上合并完全没用到 tin/tout，只用了"子先于父"的顺序。