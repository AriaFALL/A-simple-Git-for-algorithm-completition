#include <iostream>
#include <vector>
#include <queue>
#include<functional>
using namespace std;
#define int long long
const int INF = 1e9+5;
#define vt vector
#define PII pair<int,int>

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, y;
    int start=1;
    if (!(cin >> n >> m >> y)) return 0;

    vector<vector<PII>> adj(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    vt<int> x(n+1);
    for(int i=1;i<=n;i++){
      cin>>x[i];
      adj[i].push_back({0,x[i]});
      adj[0].push_back({i,x[i]+y});
    }
    vector<int> dist(n+1, INF);
  
    vector<bool> st(n+1, false);

    priority_queue <PII,vector<PII>,greater<PII>> heap;

    dist[start] = 0;
    heap.push({0, start});

    while (!heap.empty()) {
        auto [d, u] = heap.top();
        heap.pop();

        if (st[u]) continue;
        st[u] = true;
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                heap.push({dist[v], v}); 
            }
        }
    }

    for (int i = 2; i <= n; ++i) {
        if (dist[i] == INF) {
            cout <<x[1]+y+x[i]<< " ";
        } else {
            cout <<min(x[1]+x[i]+y,dist[i])<< " ";
        }
    }


    return 0;
}