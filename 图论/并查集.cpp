#include<iostream>
#include<vector>

using namespace std;

#define MAX 10086
int ne[MAX];
int he[MAX];
int se[MAX];
//ne的下缀表示节点类型，ne储存的值表示其连接的根节点

int Find(int x){
    if(ne[x]==x){
        return x;
    }else{
        return (Find(ne[x]));
    }
}

void Union_high(int x,int y){//按高度合并
    int rootx=Find(x);
    int rooty=Find(y);
    if(rooty!=rootx){
        if(he[rootx]>he[rooty]) ne[rooty]=rootx;
        else if(he[rootx]<he[rooty]) ne[rootx]=rooty;
        else he[rooty]=rootx,he[rootx]++;
    }
}

void Union_size(int x,int y){
    int rootx=Find(x);
    int rooty=Find(y);
    if(rootx!=rooty){
        if(se[rootx]<=se[rooty]){
            ne[rootx]=rooty;
            se[rooty]+=se[rootx];
        }else{
            ne[rooty]=rootx;
            se[rootx]+=rooty;
        }
    }

}