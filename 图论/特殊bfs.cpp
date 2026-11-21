//只找从1到N的最大路径，已经走过的路直接删掉不再处理
//

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    // out[v][color] = 从 v 出发、颜色为 color 的所有终点
    vector<unordered_map<int, vector<int>>> out(N + 1);
    // rem[v] = 城市 v 尚未处理过的出边颜色集合
    vector<set<int>> rem(N + 1);

    for (int i = 0; i < M; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        out[u][c].push_back(v);
        rem[u].insert(c);
    }

    // visited[v] 记录到达 v 时"上一条边颜色"有哪些已经访问过
    vector<unordered_set<int>> visited(N + 1);

    queue<tuple<int, int, int>> q; // (城市, 上一条颜色, 距离)
    q.push({1, 0, 0});
    visited[1].insert(0);

    while (!q.empty()) {
        auto [v, last_color, dist] = q.front();
        q.pop();

        if (v == N) {
            cout << dist << '\n';
            return 0;
        }

        auto &st = rem[v];
        for (auto it = st.begin(); it != st.end(); ) {
            int col = *it;
            if (col == last_color) {
                ++it; // 同色不能连续走，暂时保留
                continue;
            }

            // 可以走颜色 col 的所有出边
            for (int to : out[v][col]) {
                if (!visited[to].count(col)) {
                    visited[to].insert(col);
                    q.push({to, col, dist + 1});
                }
            }
            // 这个颜色组处理完，以后不用再处理
            it = st.erase(it);
        }
    }

    cout << -1 << '\n';
    return 0;
}