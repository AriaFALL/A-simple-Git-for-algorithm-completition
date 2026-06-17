#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#define ull unsigned long long
#define int long long
#define endl "\n"
#define vt vector
#define pb push_back
using namespace std;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;cin>>t;
    string fd1="awdec";
    string fd2="Fantasy_Blue";
    while(t--){
        int n,ui;cin>>n>>ui;
        string s;cin>>s;
        if(s.size()<fd1.size()+fd2.size()){
            cout<<"No"<<endl;
            continue;
        }
         vt<int> op(s.size());
        vt<int> ed(s.size());
        vt<int> fop(s.size());
        vt<int> fed(s.size());
        vt<int> bop(s.size());
        vt<int> bed(s.size());
        for(int i=0;i<=s.size()-fd1.size();i++){
            int l=i,r=0;
            int res=0;
            while(l<s.size() && r<fd1.size()){
                if(s[l]!=fd1[r]) res++;
                r++,l++;
            }
            ed[i]=res;
        }
        for(int i=0;i<=s.size()-fd2.size();i++){
            int l=i,r=0;
            int res=0;
            while(l<s.size() && r<fd2.size()){
                if(s[l]!=fd2[r]) res++;
                r++,l++;
            }
            op[i]=res;
        }
        int ret=0;
        int mins1=5e5+5,int mins2=5e5+5;
        for(int i=0;i<=s.size()-fd1.size() || i<=s.size()-fd2.size();i++){
            if(i<=s.size()-fd1.size()){
                mins1=min(mins1,ed[i]);
                fed[i]=mins1;
            }
            if(i<=s.size()-fd2.size()){
                mins2=min(mins2,op[i]);
                fop[i]=mins2;
            }
        }
        mins1=5e5+5,mins2=5e5+5;
        for(int i=max(s.size()-fd1.size(),s.size()-fd2.size());i>=0;i--){
             if(i<=s.size()-fd1.size()){
                mins1=min(mins1,ed[i]);
                bed[i]=mins1;
            }
            if(i<=s.size()-fd2.size()){
                mins2=min(mins2,op[i]);
                bop[i]=mins2;
            }
        }
        for(int i=0;i<=min(s.size()-fd1.size(),s.size()-fd2.size());i++){
            if(fop[i]+bed[i]<=ui){
                cout<<"Yes"<<endl;
                ret=1;
                break;
            }
        }
        if(!ret) cout<<"No"<<endl;
    }
}