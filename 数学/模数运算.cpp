#include<bits/stdc++.h>

using namespace std;

template<const int M = 1000000007>
struct MInt {
    using LL = long long;
    int x;
    
    // 构造函数
    MInt(int x = 0) : x(norm(x)) {}
    MInt(LL x) : x(norm(x % M)) {}
    
    // 规范化函数，将值调整到[0, M)范围内
    inline int norm(LL x) const {
        if (x < 0) x += M; 
        if (x >= M) x -= M; 
        return x;
    }
    
    // 快速幂函数（重载^运算符实现）
    inline MInt ksm(MInt x, LL y) const {return x ^= y;}
    inline int val() const {return x;}  // 获取值
    
    // 重载负号运算符
    inline MInt operator - () const {return MInt(norm(M - x));}
    inline MInt inv() const {assert(x != 0); return *this ^ (M - 2);}  // 求逆元
    
    // 重载复合赋值运算符
    inline MInt& operator *= (const MInt& rhs) {x = LL(x) * rhs.x % M; return *this;}
    inline MInt& operator += (const MInt& rhs) {x = norm(x + rhs.x); return *this;}
    inline MInt& operator -= (const MInt& rhs) {x = norm(x - rhs.x); return *this;}
    inline MInt& operator /= (const MInt& rhs) {return *this *= rhs.inv();}
    
    // 重载^为快速幂运算符
    inline MInt& operator ^= (LL y){
        LL ans = 1;
        while(y){
            if(y & 1) ans = ans * x % M;
            x = LL(x) * x % M;
            y >>= 1;
        }
        x = ans;
        return *this;
    }
    
    // 友元函数：重载算术运算符
    inline friend MInt operator * (const MInt& lhs, const MInt& rhs) {MInt res = lhs; res *= rhs; return res;}
    inline friend MInt operator + (const MInt& lhs, const MInt& rhs) {MInt res = lhs; res += rhs; return res;}
    inline friend MInt operator - (const MInt& lhs, const MInt& rhs) {MInt res = lhs; res -= rhs; return res;}
    inline friend MInt operator / (const MInt& lhs, const MInt& rhs) {MInt res = lhs; res /= rhs; return res;}
    inline friend MInt operator ^ (const MInt& lhs, LL y) {MInt res = lhs; res ^= y; return res;}
    
    // 输入输出流重载
    inline friend istream& operator >> (istream& is, MInt& a) {LL v; is >> v; a = MInt(v); return is;}
    inline friend ostream& operator << (ostream& os, const MInt& a) {return os << a.val();}
};
///using Z = MInt<(模运算的数)>