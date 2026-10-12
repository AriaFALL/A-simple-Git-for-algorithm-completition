#include<bits/stdc++.h>
#define int long long
#define endl "\n" /*交互题不可用\n，需要删除此行*/
#define vt vector
#define pb push_back
#define pii pair<int,int>
using namespace std;

const int INF = 4e18;/*适应大多数情况，防止卡常*/
/*求子树大小*/
vt<vt<int>> adj;/*树*/
vt<int> cnt;/*节点计数*/
vt<int> a; /*初始数组*/
int dfs(int u,int fa){
    cnt[u]=1;
    for(int i:adj[u]){
        if(i==fa) continue;
        cnt[u]+=dfs(i,u);
    }
    return cnt[u];
}
/*求前缀和*/

void dfs_p(int u,int fa){
    cnt[u]=cnt[fa]+a[u];
    for(int i:adj[u]){
        if(i==fa) continue;
        dfs(i,u);
    }
}