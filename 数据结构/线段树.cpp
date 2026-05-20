#include<iostream>
#include<vector>
using namespace std;

struct node{
    int data,lazy=0;
};

void build(const vector<int> &data,vector<node> &tree,int rt,int left,int right){
    if(left == right){
        tree[rt].data=data[left];
        return ;
    }
    int mid=(left+right)/2;
    build(data,tree,rt*2,left,mid);build(data,tree,rt*2+1,mid+1,right);
    tree[rt].data=max(tree[rt*2].data,tree[rt*2+1].data);
}

void pushdown(vector<node> &tree,int rt){
    if(tree[rt].lazy!=0){
        int &a=tree[rt].lazy;
        tree[2*rt].data+=a;        tree[2*rt].lazy+=a;        tree[2*rt+1].lazy+=a;        tree[2*rt+1].data+=a;
        a=0;
    }
}/*pushdown在所有除建树外的操作都要使用*/
/*函数传的left、right代表rt节点对应的区间为[left,right]*/
int query(const vector<int> &data,vector<node> &tree,int rt,int left,int right,int ql,int qr){
    if(ql>right || qr<left ){ /*出于保护原则，防止外围数据污染，这里采用||*/
        return INT_MIN;
    }
    if(ql<=left && qr>=right){
        return tree[rt].data;
    }
    int mid=(left+right)/2;
    pushdown(tree,rt);
    return max(query(data,tree,2*rt,left,mid,ql,qr),query(data,tree,2*rt+1,mid+1,right,ql,qr));
}

void updata(const vector<int> &data,vector<node> &tree,int rt,int left,int right,int idx,int value){
    if(left==right){
        tree[rt].data=value;
        tree[rt].lazy=0;
        return ;
    }
    pushdown(tree,rt);
    int mid=(left+right)/2;
    if(idx<=mid){
        updata(data,tree,rt,left,mid,idx,value);
    }else{
        updata(data,tree,rt*2+1,mid+1,right,idx,value);
    }
    tree[rt].data=max(tree[rt*2].data,tree[rt*2+1].data);
}
void updatarange(const vector<int> &data,vector<node> &tree,int rt,int left,int right,int ul,int ur,int value){
    if(ur<left || ul>right ){
        return ;
    }
    if(ul<=left && ur>=right){
        tree[rt].data+=value;
        tree[rt].lazy+=value;
        return ;
    }
    pushdown(tree,rt);
    int mid=(left+right)/2;
    updatarange(data,tree,rt*2,left,mid,ul,ur,value);
    updatarange(data,tree,rt*2+1,mid+1,right,ul,ur,value);
    tree[rt].data=max(tree[rt*2].data,tree[rt*2+1].data);/*回溯时重新计算节点值，防止错误更新不该更新的值*/
}