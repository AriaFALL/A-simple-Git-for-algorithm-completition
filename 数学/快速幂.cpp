#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

long long int quick_mi(int b,int op,long long M){
    long long int result=1;
    while(op>0){
        if(op&1){
            result=result*b % M;
        }
        b=b*b % M;
        op>>=1;
    }
    return result % M;
}
long long int quick_mi_digui (long long a,int op,int mod){
    if(op==1) return a;
    long long int git =quick_mi_digui (a, op/2,mod)%mod;
    if(op%2==1) return ((git*git)%mod*a)%mod;
    else return (git*git)%mod;
}