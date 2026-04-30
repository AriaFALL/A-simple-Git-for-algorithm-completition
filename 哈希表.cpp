#include<iostream>

using namespace std;

//拉链法：
const int N = 100003; 
// 2. 数据结构定义
// h[k] 存储的是哈希值为 k 的链表的栈顶节点的下标,例如 o=h[i]，哈希值i映射e[o]的值
//e[i] 存储第 i 个节点的值
// ne[i] ：得到o=h[i]时，e[o]指为栈顶数值，通过ne[o]可以访问e[o]的上一个元素指标;
// idx 是内存池的当前指针，表示当前用到了第几个节点
int h[N], e[N], ne[N], idx;
// 3. 初始化函数
void init() {
    // 将 h 数组初始化为 -1，表示所有槽位初始时都是空的（链表头为 -1）
    memset(h, -1, sizeof h);
    idx = 0;
}
// 4. 插入操作
void insert(int x) {
    // 计算哈希值
    // (x % N + N) % N 是为了处理 x 为负数的情况，确保结果在 [0, N-1] 之间
    int k = (x % N + N) % N;
    
    // 标准的链表头插法：
    e[idx] = x;      // 1. 创建新节点，存值
    ne[idx] = h[k];  // 2. 新节点的 next 指向原本的头节点
    h[k] = idx++;    // 3. 头指针更新为新节点，idx 自增
}
// 5. 查询操作
bool find(int x) {
    int k = (x % N + N) % N;
    
    // 遍历哈希值为 k 的链表
    // i = h[k] 开始，只要 i != -1 就继续，每次 i = ne[i]
    for (int i = h[k]; i != -1; i = ne[i]) {
        if (e[i] == x) {
            return true; // 找到了
        }
    }
    return false; // 没找到
}
int main() {
    // 优化 I/O 速度
    ios::sync_with_stdio(false);
    cin.tie(0);
    init(); // 别忘了初始化！
    int n;
    cin >> n; // 假设有 n 个操作
    while (n--) {
        string op;
        int x;
        cin >> op >> x;
        if (op == "I") {
            insert(x);
        } else if (op == "Q") {
            if (find(x)) puts("Yes");
            else puts("No");
        }
    }
    return 0;
}
//开放寻址法（需数值密度<=哈希密度的1/3）：
const int null_val = 0x3f3f3f3f; 
int h[N];
// 3. 核心：统一的 find 函数
// 如果 x 存在，返回 x 所在的下标；
// 如果 x 不存在，返回 x "应该被插入"的空槽位下标。
int find_open(int x) {
    int k = (x % N + N) % N;
    
    // 只要当前槽位不为空，且当前槽位的值不是 x，就继续往下找（线性探测）
    while (h[k] != null_val && h[k] != x) {
        k++;            // 往后找下一个坑位
        if (k == N) {   // 如果走到数组尽头，循环回到开头
            k = 0;
        }
    }
    return k; 
}