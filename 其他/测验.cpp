#include<bits/stdc++.h>
#define int long long
#define endl "\n"
#define vt vector
#define pb push_back
using namespace std;

const int INF = 4e18;/*适应大多数情况，防止卡常*/

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t=1;
    cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        map<int,int>op;
        int a;
        for(int i=0;i<n;i++){
            cin>>a;
            op[a]++;
        }
        int res=0;
        for(int i=0;i<k;i++){
            if(op.find(i)==op.end()){
                res++;
            }
        }
        if(op.find(k)==op.end()){

        }else{
            if(op[k]>res) res=op[k];
        }
        cout<<res<<endl;

    }


    return 0;
}