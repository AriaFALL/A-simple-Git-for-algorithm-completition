#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
//蒙德里安的梦想
// 预处理数组：记录某个状态（二进制数）中，连续的 0 是否全为偶数个
bool isValid[2048]; 
long long dp[12][2048]; // dp[i][S]：前 i-1 行已填满，第 i 行状态为 S 的方案数
int main() {
    int h, w;
    // 循环读取输入，直到 h 和 w 均为 0
    while (cin >> h >> w && (h != 0 || w != 0)) {        
        // 优化：如果总格子数是奇数，永远不可能用 1x2 的矩形填满
        if ((h * w) % 2 != 0) {
            cout << 0 << endl;
            continue;
        }
        int max_state = 1 << w; // 状态总数：2的w次方
        // 1. 预处理：判断每个状态的二进制中，连续的 0 是否为偶数个
        for (int i = 0; i < max_state; i++) {
            bool valid = true;
            int zero_count = 0;            
            for (int j = 0; j < w; j++) {
                if ((i >> j) & 1) { // 如果当前位是 1
                    if (zero_count % 2 == 1) { // 遇到 1 时，结算之前的连续 0 个数
                        valid = false;
                        break;
                    }
                    zero_count = 0; // 清零，重新计数
                } else {
                    zero_count++; // 遇到 0，计数+1
                }
            }
            // 检查最后一段连续的 0
            if (zero_count % 2 == 1) {
                valid = false;
            }
            isValid[i] = valid;
        }
        // 2. 初始化 DP 数组
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1; // 边界条件：第 0 行状态为 0 的方案数为 1
        // 3. 开始 DP 状态转移
        for (int i = 1; i <= h; i++) { // 遍历每一行
            for (int curr = 0; curr < max_state; curr++) { // 枚举当前行状态
                for (int prev = 0; prev < max_state; prev++) { // 枚举上一行状态                    
                    // 条件 1：不能有同一列都为 1 （即上一行捅下来的，和当前行准备往下捅的不能重叠）
                    if ((curr & prev) == 0) {
                        // 条件 2：除掉竖着放的，剩下的空位必须能用横着的矩形填满（连续 0 为偶数）
                        if (isValid[curr | prev]) {
                            dp[i][curr] += dp[i-1][prev];
                        }
                    }
                }
            }
        }
        // 4. 输出结果：前 h 行填满，且没有向第 h+1 行捅出矩形（状态为0）的方案数
        cout << dp[h][0] << endl;
    }
    return 0;
}
/*旅行商问题
// 假设 n 是城市数量，1<<n 就是总状态数
int MAX_STATE = 1 << n; 

// 外层循环：从小到大枚举所有二进制状态 S
for (int S = 1; S < MAX_STATE; S++) {
    
    // 中层循环：枚举当前最后到达的城市 u
    for (int u = 0; u < n; u++) {
        // 如果城市 u 根本不在状态 S 里，说明这个状态不合法，跳过
        if (!(S & (1 << u))) continue;
        
        // 内层循环：枚举上一步所在的城市 v
        for (int v = 0; v < n; v++) {
            // 如果 v 不在状态 S 里，或者 v 等于 u，跳过
            if (!(S & (1 << v)) || v == u) continue;
            
            // 核心状态转移！
            dp[S][u] = min(dp[S][u], dp[S ^ (1 << u)][v] + dist[v][u]);
        }
    }
}*/