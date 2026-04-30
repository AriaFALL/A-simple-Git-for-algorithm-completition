#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
/*/第一步：图的存储（邻接表）
在图论算法中，最常用的存储方式是邻接表（Adjacency List）。
题目中说顶点编号是 $1$ 到 $n$，并且 $n$ 最大可以达到 $200,000$。
错误做法：二维数组（邻接矩阵）
如果你用 int graph[200000][200000]，这会消耗巨大的内存（约 150GB），程序会直接崩溃（Memory Limit Exceeded）。
正确做法：vector 数组（邻接表）
既然是“树”（一种特殊的无向图），每个节点只会连接少量的其他节点。我们可以用 C++ 的 vector<int> 数组来存。
<CPP>// n 最大是 200000，为了防止越界，一般把数组开大一点，比如 200005vector<int> adj[200005]; // 如果有一条边连接 x 和 y (无向图，双向连接)adj[x].push_back(y);adj[y].push_back(x);
理解： adj[x] 里面装的就是所有和节点 x 直接相连的“邻居”。
/*/
vector <int> op[1005];
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        op[x].push_back(y);
        op[y].push_back(x);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if (find(op[i].begin(), op[i].end(), j) != op[i].end()){
                cout<<1<<' ';
            }else{
                cout<<0<<' ';
            }
        }
        cout<<"\n";
    }
    for(int i=1;i<=n;i++){
        sort(op[i].begin(),op[i].end());
        cout<<op[i].size()<<' ';
        for(int k:op[i]){
            cout<<k<<' ';
        }
        cout<<'\n';
    }
}