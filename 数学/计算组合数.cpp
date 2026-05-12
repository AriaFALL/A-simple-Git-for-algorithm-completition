void solve() {
    int n, x;
    cin >> n >> x;                     // 输入 n 和 x

    // 1. 计算 m = floor(sqrt(x))
    int m = (int)sqrt((double)x);      // 先得到一个近似值

    // 由于浮点误差，可能偏小，向上调整直到 (m+1)^2 > x
    while ((ll)(m + 1) * (m + 1) <= x)
        ++m;

    // 此时可能 m 偏大（因为上一个循环多加了），向下调整直到 m^2 <= x
    while ((ll)m * m > x)
        --m;

    // 现在 m 满足：m^2 <= x < (m+1)^2，即 m = floor(sqrt(x))

    // 如果 m < n，组合数 C(m,n) = 0（因为无法从 m 个元素中选 n 个）
    if (m < n) {
        cout << 0 << endl;
        return;
    }

    // 2. 预计算阶乘 f[i] = i! % MOD，范围 [0, m]
    vll f(m + 1);
    f[0] = 1;
    for (int i = 1; i <= m; ++i) {
        f[i] = f[i - 1] * i % MOD;
    }

    // 3. 预计算阶乘的模逆元 inv[i] = (i!)^{-1} % MOD
    vll inv(m + 1);
    inv[m] = qpow(f[m], MOD - 2);     // 费马小定理求逆元
    for (int i = m; i > 0; --i) {
        inv[i - 1] = inv[i] * i % MOD; // 递推：(i-1)! 的逆元 = i! 的逆元 * i
    }

    // 4. 计算组合数 C(m, n) = m! / (n! * (m-n)!) % MOD
    ll ans = f[m] * inv[n] % MOD * inv[m - n] % MOD;

    cout << ans << endl;               // 输出结果
}