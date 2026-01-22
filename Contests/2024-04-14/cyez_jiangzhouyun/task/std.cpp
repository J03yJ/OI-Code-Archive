#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD = 1e9 + 7;
int n, b[200005];
LL tr[2000005], sz[2000005], ans, sum = 1, s[200005], a[200005];
LL Pow(LL a, LL b) {
    LL s = 1;
    while (b) {
        if (b & 1)
            s = s * a % MOD;
        a = a * a % MOD, b = b >> 1;
    }
    return s;
}
bool cmp(int i, int j) { return a[i] < a[j]; }
void change(int x, int l, int r, int s, LL val) {
    if (r < s || s < l)
        return ;
    if (l == r) {
        tr[x] = val, sz[x] = 1;
        return ;
    }
    int mid = l + r >> 1;
    change(x * 2, l, mid, s, val), change(x * 2 + 1, mid + 1, r, s, val);
    tr[x] = (tr[x * 2] + tr[x * 2 + 1]) % MOD, sz[x] = sz[x * 2] + sz[x * 2 + 1];
}
LL find(int x, int l, int r, int sl, int sr) {//维护的区间和
    if (sr < l || r < sl)
        return 0;
    if (sl <= l && r <= sr)
        return tr[x];
    int mid = l + r >> 1;
    return (find(x * 2, l, mid, sl, sr) + find(x * 2 + 1, mid + 1, r, sl, sr)) % MOD;
}
LL find_sz(int x, int l, int r, int sl, int sr) {//区间中出现的个数
    if (sr < l || r < sl)
        return 0;
    if (sl <= l && r <= sr)
        return sz[x];
    int mid = l + r >> 1;
    return find_sz(x * 2, l, mid, sl, sr) + find_sz(x * 2 + 1, mid + 1, r, sl, sr);
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]), b[i] = i;
    sort(b + 1, b + 1 + n, cmp);
    sort(a + 1, a + 1 + n);
    s[0] = 1;
    for (int i = 1; i <= n; i++) {//s 即上文中的 pre
        sum = sum * (a[i] - i + 1) % MOD;
        if (a[i] != i)
            s[i] = s[i - 1] * (a[i] - i) % MOD * Pow(a[i] - i + 1, MOD - 2) % MOD;
        else
            s[i] = 1;//这时等于 0，直接设为 1
        cout<<s[i]<<endl;
    }
    for (int i = n, last = n; i; i--) {
    	cout<<find(1, 1, n, b[i] + 1, n)<<' '<<find(1, 1, n, 1, b[i] - 1)<<' '<< find_sz(1, 1, n, 1, b[i] - 1)<<' '<<sum<<endl;
        ans = (ans + sum * (a[i] - i) % MOD * Pow(2 * s[i], MOD - 2) % MOD * find(1, 1, n, b[i] + 1, n)) % MOD;//这部分是 $b_i < b_j$ 的答案 
        ans = ((ans + sum * find_sz(1, 1, n, 1, b[i] - 1) - sum * (a[i] - i) % MOD * Pow(2 * s[i], MOD - 2) % MOD * find(1, 1, n, 1, b[i] - 1)) % MOD + MOD) % MOD;//这部分是 $b_i>b_j$ 的答案
        change(1, 1, n, b[i], s[i - 1] * Pow(a[i] - i + 1, MOD - 2) % MOD);//单点修改
        if (a[i] == i)//将区间和等于0的全部清零
            while (last > i)
                change(1, 1, n, b[last], 0), last--;
    }
    printf("%lld\n", ans);
    return 0;
}
