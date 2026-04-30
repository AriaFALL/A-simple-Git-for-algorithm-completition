#include<iostream>
#include<string>
using namespace std;

const int N=10010;

int son[N][26],cnt[N],idx=0;
//p->父节点的idx，son[p][u]->代号，cnt->对应长度bool值
void insert(string op){
    int p=0;
    for(int i=0;i<op.size();i++){
        int u=op[i]-'a';
        if(!son[p][u]) son[p][u]=++idx;
        p=son[p][u];
    }
    cnt[p]++;
}

//例题，最大异或对

int cn[31][2];
int idx_=0;
void insert_(int x){
    int p=0;
    for(int i=30;i>=0;i--){
        int j=x>>i&1;
        if(!cn[p][j]) cn[p][j]=++idx_;
        p=cn[p][j];
    }
}

int query(int x){
    int p=0;
    int res=0;
    for(int i=30;i>=0;i--){
        int j=x>>i&1;
        if(cn[p][!j]){
            res+=1<<i;//左移的是1，不是i；
            p=cn[p][!j];
        }else{
            p=cn[p][j];
        }
    }
    return res;
}