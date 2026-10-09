#include<bits/stdc++.h>
#define int long long
#define endl "\n" /*交互题不可用\n，需要删除此行*/
#define vt vector
#define pb push_back
#define pii pair<int,int>
using namespace std;

const int INF = 4e18;/*适应大多数情况，防止卡常*/
vt<vt<int>> rt;/*邻接表：rt[u] 存 u 的所有出边终点（有向图，不是树）*/
vt<bool> in_stack;/*是否还在栈中；*/
stack<int> stk;
vt<int> dfn,low;
vt<vt<int>> res;
int timer=0;

void tarjan(int u){
    dfn[u]=low[u]=++timer;
    stk.push(u);in_stack[u]=true;
    for(int v:rt[u]){
        if(!dfn[v]){/*v 没访问过：树边，先递归，回来再用 low[v] 更新,不能用!in_stack[v]，否则已弹出的点又会遍历*/
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }else if(in_stack[v]){/*v 访问过且在栈里：回边/横叉边，只能用 dfn[v] 更新*/
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(low[u]==dfn[u]){
        vt<int> ans;
        int v;
        do{
            v=stk.top();stk.pop();
            in_stack[v]=false;
            ans.pb(v);
        }while(v!=u);
        res.pb(ans);
    }
}
