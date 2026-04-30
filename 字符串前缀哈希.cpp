#include <iostream>
#include <string>

using namespace std;

// 技巧1：使用 unsigned long long (简称 ULL)
// ULL 的最大值是 2^64 - 1。
// 当数字超过这个值时，C++ 会自动让它溢出，这等价于对 2^64 取模！
// 这样我们不仅省去了极其耗时的 % 操作，还能获得一个巨大的模数，几乎不可能产生哈希冲突。
typedef unsigned long long ULL;

const int N = 100010;
// 技巧2：P 的取值。经验表明，P 取 131 或 13331 时，冲突率最低。
const int P = 131; 

ULL h[N]; // 存放前缀哈希值
ULL p[N]; // 存放 P 的多少次方

// 求任意子串 [l, r] 的哈希值 (下标从 1 开始)
ULL get_hash(int l, int r) {
    // 核心公式：h[r] - h[l-1] * P^(r-l+1)
    return h[r] - h[l - 1] * p[r - l + 1];
}

int main() {
    int n, m;
    string str;
    
    // 输入字符串长度和查询次数
    cin >> n >> m >> str;
    
    // 技巧3：为了方便计算前缀和，字符串下标最好从 1 开始。
    // 我们在原字符串前面拼一个空格（或者任何字符），让有效字符从 1 开始。
    str = " " + str; 

    // 初始化 p[0]
    p[0] = 1; 

    // 预处理 h 数组和 p 数组
    for (int i = 1; i <= n; i++) {
        // 技巧4：字符不能映射为 0！如果 'a'=0，那么 "a", "aa", "aaa" 的哈希值都是 0，就全乱了。
        // 直接用 ASCII 码即可，因为 ASCII 码都不为 0。
        h[i] = h[i - 1] * P + str[i]; 
        p[i] = p[i - 1] * P;          
    }

    // 处理查询
    while (m--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;

        // 只需要 O(1) 的时间比较哈希值即可！
        if (get_hash(l1, r1) == get_hash(l2, r2)) {
            puts("Yes");
        } else {
            puts("No");
        }
    }

    return 0;
}