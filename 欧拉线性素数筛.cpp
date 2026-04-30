#include <iostream>
#include<vector>
using namespace std;

using ll=long long;
#define pb push_back


vector <int> op;
int main() {
    int n;
    cin>>n;
    vector <int> vbs(n+1,0);
    ll count=0;
    for(int i=2;i<=n;i++){
        if(vbs[i]==0){
            op.pb(i);
            vbs[i]=i;
            count+=i;
        }
        for(int p:op){
            if(p>vbs[i] || 1ll*i*p>n){/** 乘法分配率问题，比如12=2*2*3，此举可以保证不会出现12=3*2*2
                等浪费时间的问题 ，
                也就是i*p=p(<vbs[i])*i(分解为包含vbs[i]的质数乘积，且每一项都大于p)    **/
                break;
            }
            vbs[i*p]=p;
            count+=p;
        }
    }
    cout<<count;
}
// 64 位输出请用 printf("%lld")
