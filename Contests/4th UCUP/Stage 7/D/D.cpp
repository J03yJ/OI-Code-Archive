#include <bits/stdc++.h>
using namespace std;
const int N = 400010;
std::vector<int> G[N];
int T, n, u, v, md, d[N];
int f[N][19], siz[N], useful[N];
inline void dfs(int x, int fa, bool chk = true) {
    d[x] = d[fa] + 1, f[x][0] = fa;
    if (d[u] < d[x] && chk) u = x;
    for (int i = 1; (1 << i) <= d[x] + 1; i++) {
        f[x][i] = f[f[x][i - 1]][i - 1];
    }
    for (auto &y : G[x]) {
        if (y != fa) dfs(y, x, chk);
    }
}
inline void dfs1(int x, int fa) {
    siz[x] = d[x] == md, useful[x] = 0;
    for (auto &y : G[x]) {
        if (y == fa) continue;
        dfs1(y, x), siz[x] += siz[y];
        if (siz[y]) useful[x]++;
    }
}
inline void dfs2(int x, int v, int fa) {
    cout << "(" << x << ")";
    if (x <= n) cout << v << ' ';
    pair<int, int> mn{INT_MAX, 0};
    for (auto &y : G[x]) {
        if (y != fa && siz[y]) {
            mn = min(mn, {useful[y], y});
        }
    }
    if (mn.first != INT_MAX) {
        dfs2(mn.second, v + useful[x] - 1 - (x == u), x);
    }
}
inline void solve(void) {
    cin >> n;
    for (int i = 1; i < 2 * n; i++) G[i].clear();
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        G[u].push_back(i + n);
        G[v].push_back(i + n);
        G[i + n].push_back(u);
        G[i + n].push_back(v);
    }
    if (n == 2) {
        cout << "2 1\n";
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (G[i].size() == n - 1u) {
            cout << n - 1 << ' ' << n << ' ' << n - 2 << '\n';
            return;
        }
    }
    d[0] = -1, u = 1;
    dfs(1, 0), dfs(u, 0);
    const int len = d[u] / 2;
    for (int k = 18; k >= 0; k--) {
        if (len >> k & 1) u = f[u][k];
    }
    dfs(u, 0, false), md = 0;
    for (int i = 1; i < 2 * n; i++) {
        md = max(md, d[i]);
    }
    dfs1(u, 0);
    for (int i = 0; i <= len / 2; i++) {
        cout << siz[u] + i << ' ';
    }
    dfs2(u, siz[u] + len / 2 + 1, 0);
    cout << '\n';
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> T;
    while (T--) solve();
    return 0;
}