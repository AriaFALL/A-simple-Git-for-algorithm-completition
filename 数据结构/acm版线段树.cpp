#include<bits/stdc++.h>

using namespace std;
#define ll long long 

const int N = 200000 + 5;

ll a[N], mx[N << 2];

void pushup(int p) {
    mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
}

void build(int p, int l, int r) {
    if (l == r) {
        mx[p] = a[l];
        return;
    }

    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void update(int p, int l, int r, int x, ll v) {
    if (l == r) {
        mx[p] = v;
        return;
    }

    int mid = (l + r) >> 1;

    if (x <= mid) update(p << 1, l, mid, x, v);
    else update(p << 1 | 1, mid + 1, r, x, v);

    pushup(p);
}

ll query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return mx[p];
    }

    int mid = (l + r) >> 1;
    ll ans = LLONG_MIN;

    if (ql <= mid) ans = max(ans, query(p << 1, l, mid, ql, qr));
    if (qr > mid) ans = max(ans, query(p << 1 | 1, mid + 1, r, ql, qr));

    return ans;
}


int main(){



}