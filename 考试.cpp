#include<iostream>

using namespace std;
using ll= long long;
#define endl "\n"

ll quick_mi(int n,ll x){
    ll o=quick_mi(n/2,x);
    if(n%2==0) return o*o;
    else return o*o*x;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        if(n==k){
            cout<<0<<endl;
        }
        int m=0;
        int ret=0;
        int o=2;
        ll l=0;
        ll r=0;
        while( ret==0 && l<n){
             l=o*k-(o-1);
             r=o*k+(o-1);
            if(n>=l && n<=r) ret=1;
            o=o*2;
            m++;
        }
        cout<<m<<endl;
    }
}