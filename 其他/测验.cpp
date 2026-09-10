#include<bits/stdc++.h>
#define int long long
#define endl "\n" /*交互题不可用\n，需要删除此行*/
#define vt vector
#define pb push_back
#define pii pair<int,int>
using namespace std;

const int INF = 4e18;/*适应大多数情况，防止卡常*/
vt<pii> a;
int n,t;
int erfd(int g){
    int l=0,r=n-1;
    int res;
    while(l<=r){
          int mid=(l+r+1)/2;
        if(a[mid].first<g){
            l=mid+1;
        }else{
            r=mid-1;
            res=r;
        }
    }
    return res;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t=1;
    //cin>>t;
    while(t--){
        
        cin>>n>>t;
        
        for(int i=0;i<n;i++){
            int l,r;
            cin>>l>>r;
            a.pb({l,r});
        }
        sort(a.begin(),a.end());
        int res=0;
        for(int i=n-1;i>=0;i--){
            pii f=a[i];
            int l=f.first,r=f.second;
            int  fd=r-t;
            int g=erfd(fd);
            while(a[g].first==fd){
                res++;
                g++;
            }
        }
        cout<<res;
    }


    return 0;
}