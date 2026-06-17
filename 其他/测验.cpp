#include<bits/stdc++.h>
#define int long long
#define endl "\n"
#define vt vector
#define pb push_back
using namespace std;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;
    vt<int> x(n+5);
    vt<int> y(n+5);
    int cnt=0;
    for(int i=0;i<n;i++){
      cin>>x[i]>>y[i];
      int res=0;
      for(int j=0;j<i;j++){
        int ret=(y[i]>y[j])+(x[i]>x[j]);
        if(ret==2){
          res=1;
          break;
        }
      }
      if(!res){
        cnt++;
      }
    }
    cout<<cnt;
}