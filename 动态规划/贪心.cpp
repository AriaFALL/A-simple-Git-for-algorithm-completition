#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;
/*找出最高位的01之差，当成C1来做
原题链接：cf 1065 C2 Renako Amaori and XOR Game (hard version)
*/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) cin >> b[i];
        
        int C = 0;
        for (int i = 0; i < n; ++i) {
            C ^= (a[i] ^ b[i]);
        }
        
        if (C == 0) {
            cout << "Tie\n";
            continue;
        }
        
        int k = 31 - __builtin_clz(C); // C > 0 的最高位
        
        int last = -1;
        for (int i = n - 1; i >= 0; --i) {
            if (((a[i] ^ b[i]) >> k) & 1) {
                last = i + 1; // 1-indexed
                break;
            }
        }
        
        if (last % 2 == 1) {
            cout << "Ajisai\n";
        } else {
            cout << "Mai\n";
        }
    }
    return 0;
}