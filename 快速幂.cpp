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
long long int quick_mi_digui (long long a,int op){
    if(op==1) return a;
    long long int git =quick_mi_digui (a, op/2);
    if(op%2==1) return git*git*a;
    else return git*git;
}