#include <iostream>
using namespace std;

const int N = 100010;

// 全局变量，自动初始化为 0
int e[N], ne[N], head, idx;

void init() {
    head = -1;
    idx = 0;
}

void add_to_head(int x) {
    e[idx] = x;
    ne[idx] = head;
    head = idx;
    idx++;
}

void add_to_back(int x){
    e[idx]=x;
    if(idx==0){
        ne[idx]=-1;
        idx++;
        return ;
    }else{
        int op=idx-1;
        ne[op]=idx;
        ne[idx]=-1;
        idx++;
        return ;
    }
}

void add(int k, int x) {
    e[idx] = x;
    ne[idx] = ne[k];
    ne[k] = idx;
    idx++;
}

void remove(int k) {
    ne[k] = ne[ne[k]];
}

int main() {
    // 优化 cin
    ios::sync_with_stdio(false);
    cin.tie(0);

    init();

    add_to_head(10); // 链表: 10
    add_to_head(20); // 链表: 20 -> 10
    add_to_head(30); // 链表: 30 -> 20 -> 10
    
    // 注意：第 1 个插入的节点是 10 (它的 idx 是 0)
    // 第 2 个插入的节点是 20 (它的 idx 是 1)
    
    // 在第 2 个插入的节点(idx=1)后插入 15
    add(1, 15);      // 链表: 30 -> 20 -> 15 -> 10

    // 删除第 3 个插入的节点(idx=2，即30)后面的节点(20)
    // 等等，30 是头节点，如果要删除头节点，需要特判 head = ne[head];
    // 这里演示删除 idx=1 (即20) 后面的节点(15)
    remove(1);       // 链表: 30 -> 20 -> 10

    // 【核心】如何遍历链表？
    // 类似于 for(Node* p = head; p != nullptr; p = p->next)
    for (int i = head; i != -1; i = ne[i]) {
        cout << e[i] << " ";
    }
    cout << endl;

    return 0;
}