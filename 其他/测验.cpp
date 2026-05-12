#include<iostream>
#include<vector>
#include<string>
#include<algorithm>


#define int long long
#define endl "\n"
#define vt vector
#define pb push_back
using namespace std;

signed main(){
    int t;cin>>t;
    while(t--){
        int n,k;cin>>n>>k;
        vt<int> op;
        for(int i=0;i<n;i++){
            cin>>op[i];
        }
        sort(op.begin(),op.end());
        int res=0;
        int las=0;
        for(int i=1;i<n;i++){
            if(op[i]==op[i-1]+1){
                las++;
            }else{
                while(las>0){
                    res+=las/2;
                    las=las/2;
                }
            }
        }
        while(las>0){
                    res+=las/2;
                    las=las/2;
                }
        cout<<res<<endl;
    }   
}