#include<bits/stdc++.h>
#define int long long
#define endl "\n"
#define vt vector
#define pb push_back
using namespace std;

const int mod=998244353;
 
bool match(string &s,char c,char d){ 
   if(c=='?' && d=='?'){
       return true;
   }else if(c=='?' && d!='?'){
       return d==s[1];
   }else if(d=='?' && c!='?'){
       return c==s[0];
   }else{
       string s1=c+d;
       return s1==s;
   }
}


signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    //int t;cin>>t;while(t--){
    //
    int n;cin>>n;
    vt<char> a(n+5);
    vt<char> b(n+5);
    
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    
    vt<int> dp(4);
    vt<int> ndp(4);
    
    for(int j=0;j<4;j++){
        char c=j%2+'0';
        char d=j%1+'0';
        string s=a[1]+b[1];
        if(match(s,a[1],b[1])){
            dp[j]=1;
        }
    }
    
    for(int i=2;i<=n;i++){
        string s=a[i-1]+b[i-1];
        for(int j=0;j<4;j++){
            char c=j%2+'0';
            char d=j%1+'0';
            ndp[j]=0;
            string s1=c+d;
            if(match(s,a[i],b[i])){
                for(int k=0;k<4;k++){
                    if(k!=j) ndp[j]=(dp[k]%mod+ndp[j])%mod;
                }
            }
        }
        dp[0]=ndp[0];dp[1]=ndp[1];dp[2]=ndp[2];dp[3]=ndp[3];
        
    }
    
    cout<<ndp[0]+ndp[1]+ndp[2]+ndp[3];
    return 0;
}