#include <cstdio>
#define long long long
const int N = 1e5 + 10, B = 40;
int n, m, h[N * 4];
long a[N], qk[N], ans[N];
struct Qes {
    int nex, id, l, r;
} q[N];
void push(int x, int id) {
    q[id].nex = h[x]; 
    h[x] = id;
}
inline int bit(long x, int i) { return (x >> i) & 1; }
struct Basis {
    long b[B];
    bool zero;
    void copy(Basis &T) {
        for (int i = 0; i < B; i++) b[i] = T.b[i];
        zero = T.zero;
    }
    void clear() {
        for (int i = 0; i < B; i++) b[i] = 0;
        zero = 0;
    }
    void ins(long x) {
        for (int i = B - 1; x && i >= 0; i--) {
            if (!bit(x, i))
                continue;
            x ^= b[i];
            if (!b[i] && x) {
                b[i] = x;
                return;
            }
        }
        zero = 1;
    }
    void simple() {
        for (int i = 0; i < B; i++)
            for (int j = i + 1; j < B; j++)
                if (bit(b[j], i))
                    b[j] ^= b[i];
    }
    void merge(Basis &T) {
        zero = zero || T.zero;
        for (int i = 0; i < B; i++)
            if (T.b[i])
                ins(T.b[i]);
    }
    long get_kth(long k) {
        if (zero)
            k--;
        if (!k)
            return 0;
        long res = 0;
        for (int c = 0, i = 0; i < B; i++) {
            if (!b[i])
                continue;
            if (bit(k, c++))
                res ^= b[i];
        }
        return res;
    }
} per[N], suf[N], mL[N], mR[N], T;
void solve(int x, int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1, x1 = x * 2, x2 = x * 2 + 1;
    h[x1] = h[x2] = 0;
    mL[mid + 1].clear();
    mR[mid].clear();
    for (int i = mid; i >= l; i--) {
        mL[i].copy(mL[i + 1]);
        mL[i].ins(a[i]);
    }
    for (int i = mid + 1; i <= r; i++) {
        mR[i].copy(mR[i - 1]);
        mR[i].ins(a[i]);
    }
    for (int nex, i = h[x]; i; i = nex) {
        nex = q[i].nex;
        if (q[i].r <= mid) {
            push(x1, i);
            continue;
        }
        if (q[i].l > mid) {
            push(x2, i);
            continue;
        }
        T.copy(per[q[i].l - 1]);
        T.merge(suf[q[i].r + 1]);
        T.merge(mL[q[i].l + 1]);
        T.merge(mR[q[i].r - 1]);
        T.simple();
        ans[q[i].id] = T.get_kth(qk[q[i].id]);
    }
    solve(x1, l, mid);
    solve(x2, mid + 1, r);
}
int main() {
    freopen("xorcat.in","r",stdin);
    freopen("xorcat.out","w",stdout);
    int tt;
    scanf("%d", &tt);
    while (tt--) {
        scanf("%d%d", &n, &m);
        per[0].clear();
        suf[n + 1].clear();
        for (int i = 1; i <= n; i++) scanf("%lld", a + i);
        for (int i = 1; i <= n; i++) {
            per[i].copy(per[i - 1]);
            per[i].ins(a[i]);
        }
        for (int i = n; i >= 1; i--) {
            suf[i].copy(suf[i + 1]);
            suf[i].ins(a[i]);
        }
        per[n].simple();
        h[1] = 0;
        for (int l, r, i = 1; i <= m; i++) {
            scanf("%d%d%lld", &l, &r, qk + i);
            if (!l && !r) {
                ans[i] = per[n].get_kth(qk[i]);
            }
            if (!l || !r) {
                l += r;
                T.copy(per[l - 1]);
                T.merge(suf[l + 1]);
                T.simple();
                ans[i] = T.get_kth(qk[i]);
            } else {
                if (l < r)
                    q[i] = (Qes){ 0, i, l, r };
                else
                    q[i] = (Qes){ 0, i, r, l };
                push(1, i);
            }
        }
        solve(1, 1, n);
        for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
    }
    return 0;
}
