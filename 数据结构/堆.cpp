#include<iostream>
#include<vector>
#include<algorithm>
/*以小根堆举例*/
const int N=1*5+5;
int h[N],size;
using namespace std;
void down(int u){
    int t=u;
    if(u*2<=size && h[u*2]<h[t]) t=u*2;
    if(u*2+1<=size && h[u*2+1]<h[t]) t=u*2+1;
    if(h[t]<h[u]){
        swap(h[t],h[u]);
        down(t);
    }
}

void up(int u){
    while(u/2!=0 && h[u/2]>h[u]){
        swap(h[u],h[u/2]);
        u=u/2;
    }
}


/*
1.加入新元素，h[++size]=x,up(size);
2.删除元素,h[k]=h[size],size--,down(k),up(k)
3.修改元素,h[k]=x,down(k),up(k);

*/