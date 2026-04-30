#include<iostream>
#include<string>
#include<queue>
#include<map>
#include<vector>
#include<algorithm>

using namespace std;
#define vt vector
#define endl "\n"

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vt <int> a(n);
        vt <int> res(n+1);
        vt <int> rem;
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        int ret=200005;
        int mint=200005;
        for(int i:a){
            if(mint>i){
                if(mint!=200005){
                    ret=min(i,ret);
                    rem.push_back(i);
                }else{
                    mint = i;
                    res[i]=0;
                }
            }else{
                if(ret!=200005){
                    mint = ret;
                    ret=200005;
                    for(int j:rem){
                        res[j]=i;
                    }
                    rem.clear();
                }
                res[i]=mint;
            }
        }
        if(ret==200005){
            cout<<"Yes"<<endl;
            for(int i=1;i<=n;i++){
                if(res[i]==0){
                    continue;
                }
                cout<<res[i]<<" "<<i<<endl;
            }
        }else{
            cout<<"No"<<endl;
        }
    }
}