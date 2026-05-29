#include<iostream>
#include<vector>
#include<string>
#include<algorithm>


#define int long long
#define endl "\n"
#define vt vector
#define pb push_back
using namespace std;

int dfs(int i,vt<vt<int>> &rt,vt<bool> &vst,int len){
    vst[i]=true;
    int maxs=0;
    for(int j:rt[i]){
            if(!vst[j]){
                vst[j]=true;
                maxs=max(maxs,dfs(j,rt,vst,len+1));
            }
    }
    return maxs+1;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vt<vt<int>> rt(n,vt<int>(n));
    vt<int> ne(n,0);
    int m = n - 1;          
    while (m--) {
        int a, b; cin >> a >> b;
        ne[a]++,ne[b]++;
        rt[a].pb(b);
        rt[b].pb(a);
    }
    int maxs=0;
    for(int i=1;i<n;i++){
        if(ne[i]==1){
            vt<bool> vst(n,false);
            maxs=max(maxs,dfs(i,rt,vst,0));
        }
    }
    cout<<maxs;
}