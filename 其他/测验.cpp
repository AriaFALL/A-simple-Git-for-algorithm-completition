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
    int t;
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        int res=0;
        int n=s.size();
        vt<int> sh(n,0);
        vt<int> xi(n,0);
        for(int i=0;i<s.size();i++){
            if(res==0){
                if(s[i]=='1' || s[i]=='3') res=1;
            }else{
                if(s[i]=='2') sh[i]=sh[i-1]+1;
                else if(s[i]=='1' ||s[i]=='3')sh[i]=sh[i-1];
            }
        }
        res=0;
        for(int i=n-1;i>=0;i--){
            if(res==0){
                if(s[i]=='2') res=1;
            }else{
                 if(s[i]=='1' || s[i]=='3') xi[i]=xi[i+1]+1;
                else if(s[i]=='2')xi[i]=xi[i+1];
            }
        }
        res=0;
        for(char c:s){
            if(c=='4') res++;
        }
        int result=1e9+5;
        for(int i=0;i<n-1;i++){
            result=min(result,sh[i]+xi[i+1]);
        }
        cout<<res<<" "<<result;
        if(result=1e9+5) cout<<0+res<<endl;
        else cout<<result+res<<endl;
    }
}