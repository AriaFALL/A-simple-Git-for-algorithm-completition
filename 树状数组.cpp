#include <iostream>
using namespace std;

const int N = 100005;
int n;
int tree[N];

int lowbit(int x){
    return x & -x;
}

void add(int x, int v){
    for(int i = x; i <= n; i += lowbit(i)){
        tree[i] += v;
    }
}

int sum(int x){
    int res = 0;
    for(int i = x; i > 0; i -= lowbit(i)){
        res += tree[i];
    }
    return res;
}

int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        int x;
        cin >> x;
        add(i, x); // 建树
    }

    cout << sum(5) << '\n'; // 查询前5个数和
}
/*tree[i] 存的是什么
树状数组里：tree[i] tree[i]存的是一段长度为 lowbit(i) 的区间和，即：[i−lowbit(i)+1,i]
比如 n=8时：tree[1] 管 [1,1]，tree[2] 管 [1,2]，tree[3] 管 [3,3]，tree[4] 管 [1,4]，tree[5] 管 [5,5]，tree[6] 管 [5,6]，tree[7] 管 [7,7]，tree[8] 管 [1,8]
怎么查询前缀和
要求：a1+a2+⋯+ax 
代码：
int sum(int x){
    int res = 0;
    while(x > 0){
        res += tree[x];
        x -= lowbit(x);
    }
    return res;
}
为什么这样能行
比如查询 sum(7)：
先加 tree[7]，它管 [7,7]
再到 7-lowbit(7)=6，加 tree[6]，它管 [5,6]
再到 6-lowbit(6)=4，加 tree[4]，它管 [1,4]
再到 0 结束
合起来正好是：[7,7]+[5,6]+[1,4]=[1,7]
怎么单点修改
如果把位置 x加上 v：
void add(int x, int v){
    while(x <= n){
        tree[x] += v;
        x += lowbit(x);
    }
}
为什么这样更新
因为位置 x 的值被哪些 tree[i] 管着，就要把这些 tree[i] 都加上 v。
比如修改 a[3]：
tree[3] 管 [3,3]，包含 3
tree[4] 管 [1,4]，包含 3
tree[8] 管 [1,8]，包含 3
所以要更新这些地方。
而 x += lowbit(x) 正好就是跳到下一个包含它的节点。
*/