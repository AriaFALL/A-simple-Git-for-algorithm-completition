#include<bits/stdc++.h>

using namespace std;

int dp[100005][100005];

int main(){
    int n;cin>>n;
    vector<int>a(n);
    int m;cin>>m;
    vector<int> b(m);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<m;i++){
        cin>>b[i];
    }
    for(int i=1;i<n;i++){
        int val=0;
        for(int j=1;j<m;j++){
            if(b[j-1]==a[i-1]){
                dp[i][j]=val+1;
            }else{
                dp[i][j]=max(dp[i-1][j],dp[i][j]);
            }

            if(b[j-1]<a[i-1]){
                val=max(dp[i-1][j],val);
            }
        }
    }
}