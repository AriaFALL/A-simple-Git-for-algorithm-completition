#include<iostream>
#include<algorithm>
using namespace std;

// 以小根堆为例
// 堆是一棵完全二叉树，每个父节点 <= 子节点

const int N = 100010;
int h[N], sz;  // h[1] 为堆顶（最小值），sz 为当前堆大小

// 向下调整：将 u 节点下沉到正确位置
void down(int u){
    int t = u;                     // t 记录最小值节点的下标
    if(u*2 <= sz && h[u*2] < h[t]) t = u*2;      // 左子节点更小
    if(u*2+1 <= sz && h[u*2+1] < h[t]) t = u*2+1; // 右子节点更小
    if(t != u){
        swap(h[u], h[t]);
        down(t);                   // 递归继续下沉
    }
}

// 向上调整：将 u 节点上浮到正确位置
void up(int u){
    while(u/2 && h[u/2] > h[u]){
        swap(h[u/2], h[u]);
        u /= 2;
    }
}

// 建堆：O(n) 复杂度
void build(int a[], int n){
    sz = n;
    for(int i = 1; i <= n; i++) h[i] = a[i];
    for(int i = n/2; i; i--) down(i);  // 从最后一个非叶子节点开始 down
}

// 插入一个数
void push(int x){
    h[++sz] = x;
    up(sz);
}

// 返回堆顶（最小值）
int top(){
    return h[1];
}

// 弹出堆顶
void pop(){
    h[1] = h[sz--];
    down(1);
}

// 删除任意位置 k 的元素
void remove(int k){
    h[k] = h[sz--];
    down(k);
    up(k);  // down 和 up 只会执行一个，这样写不用判断方向
}

// 修改任意位置 k 的值为 x
void modify(int k, int x){
    h[k] = x;
    down(k);
    up(k);
}

// 堆排序（升序）：每次取堆顶，然后 pop
void heap_sort(int a[], int n){
    build(a, n);
    for(int i = 1; i <= n; i++){
        a[i] = top();
        pop();
    }
}

// 判断堆是否为空
bool empty(){
    return sz == 0;
}

// 返回堆的大小
int size(){
    return sz;
}

int main(){
    // 示例：堆排序
    int a[] = {0, 3, 5, 1, 4, 2};  // a[0] 不用，从 a[1] 开始
    int n = 5;

    heap_sort(a, n);

    cout << "堆排序结果：";
    for(int i = 1; i <= n; i++) cout << a[i] << " \n"[i==n];

    // 示例：堆的基本操作
    build(a, n);  // 重新建堆
    cout << "堆顶最小值：" << top() << endl;

    push(0);
    cout << "插入 0 后堆顶：" << top() << endl;

    pop();
    cout << "弹出堆顶后新堆顶：" << top() << endl;

    return 0;
}
