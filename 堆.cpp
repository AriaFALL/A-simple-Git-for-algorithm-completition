#include<iostream>
#include<algorithm>
using namespace std;

//以小根堆为例，有关堆排序请参考BILIBILI视频

int h[10000],size;

void down(int u){
    int t=u;
    if(u*2<=size && h[u*2]<h[t]) t=u*2;
    if(u*2+1<=size && h[u*2+1]<h[t]) t=u*2;
    if(t!=u){
        swap(h[u],h[t]);
        down(t);
    }
}

void up(int u){
    while(u/2 && h[u/2]>h[u]){
        swap(h[u/2],h[u]);
        u/=2;
    }
}

int main(){

}
//插入一个数：h[++size]=x;up[x];
//求最小值：h[1]
//删除任意值：h[k]=h[size];size--;down(k);up[k];
//修改任意值：h[k]=x;down(k);up(k);