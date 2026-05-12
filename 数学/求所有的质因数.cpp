#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "请输入 n：";
    cin >> n;

    // spf[i] 存储 i 的最小质因子，初始化为 0
    vector<int> spf(n + 1, 0);
    vector<int> primes;          // 存储素数

    // 欧拉线性筛，同时记录最小质因子
    for (int i = 2; i <= n; ++i) {
        if (spf[i] == 0) {       // i 是素数
            spf[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (i * p > n) break;
            spf[i * p] = p;      // 合数的最小质因子就是 p
            if (i % p == 0) break; // 保证每个数只被最小质因子筛一次
        }
    }

    // 输出每个数的不同质因数
    cout << "\n每个数的不同质因数如下：\n";
    for (int i = 1; i <= n; ++i) {
        cout << i << ": ";
        if (i == 1) {            // 1 没有质因数
            cout << endl;
            continue;
        }
        int x = i;
        int last_p = 0;
        // 利用 spf 不断分解，跳过重复的质因子
        while (x > 1) {
            int p = spf[x];
            if (p != last_p) {
                cout << p << " ";
                last_p = p;
            }
            x /= p;
        }
        cout << endl;
    }

    return 0;
}