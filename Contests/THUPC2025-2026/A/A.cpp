#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N = 5e5 + 9;

vector<int> e[N], pos[N];
int a[N], ql[N], qr[N], qu[N], n, m, q;

int fa[N], siz[N], dep[N], hson[N];
inline void GetHSon(int x) {
    siz[x] = 1;
    for (int y : e[x]) {
        if (y == fa[x]) continue;
        fa[y] = x;
        dep[y] = dep[x] + 1;
        GetHSon(y);
        siz[x] += siz[y];
        if (!hson[x] || siz[hson[x]] < siz[y]) hson[x] = y;
    }
}
int dfn[N], idfn[N], top[N], dcnt;
inline void GetTop(int x, int t) {
    top[x] = t;
    dfn[x] = ++dcnt;
    idfn[dcnt] = x;
    if (hson[x]) GetTop(hson[x], t);
    for (int y : e[x]) {
        if (y == fa[x]) continue;
        if (y == hson[x]) continue;
        GetTop(y, y);
    }
}

vector<array<int, 2>> qry[N];
inline void InsQ(int x, int id) {
    int lst = 0;
    while (x) {
        qry[x].push_back({lst, id});
        lst = top[x];
        x = fa[top[x]];
    }
}

struct Node {
    int l, r, dat;
} tr[N << 2];

int p[N];
inline void ChMax(int &x,int y){if(y>x) x=y;}
inline void PushUp(int x) { tr[x].dat = max(tr[x << 1].dat, tr[x << 1 | 1].dat); }
inline void Build(int x, int l, int r) {
    tr[x].l = l, tr[x].r = r;
    if (tr[x].l == tr[x].r) return tr[x].dat = 0,p[l]=x, void();
    int mid = tr[x].l + tr[x].r >> 1;
    Build(x << 1, l, mid), Build(x << 1 | 1, mid + 1, r);
    PushUp(x);
}
inline void Set(int x,int pos,int k){
	x=p[pos],tr[x].dat=k;
	x>>=1;
	while(x) PushUp(x),x>>=1;
}
inline int Query(int x, int l, int r) {
    if (l <= tr[x].l && tr[x].r <= r) return tr[x].dat;
    int mid = tr[x].l + tr[x].r >> 1,ans=0;
    if (l <= mid) ChMax(ans,Query(x << 1, l, r));
    if (r > mid) ChMax(ans,Query(x << 1 | 1, l, r));
	return ans;
}


struct BIT{
	int tr[N];
	inline void Add(int x,int k){while(x<=n) tr[x]+=k,x+=x&-x;}
	inline int Ask(int x){int sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}
	inline int Ask(int l,int r){return Ask(r)-Ask(l-1);}
}T;

int ans[N];
vector<int> tmp[N];
inline void Ins(int x, int k) {for(int i:pos[x]) Set(1,i,k); };
inline void Ers(int x) {for(int i:pos[x]) Set(1,i,0); };
inline void F(int x, int k) {for(int i:pos[x]) T.Add(i,k); };
inline void Calc() {
    for (int x = 1; x <= n; x++) {
        if (x != top[x]) continue;
        int low = 0;
        for (int y = x; y; y = hson[y]) {
            Ins(y, y);
            for (int z : e[y]) {
                if (z == fa[y]) continue;
                if (z == hson[y]) continue;
                for (int i = dfn[z]; i < dfn[z] + siz[z]; i++) Ins(idfn[i], y);
            }
            for (auto p : qry[y]) tmp[p[0]].push_back(p[1]);
            for (int i : tmp[0]) ChMax(ans[i], Query(1, ql[i], qr[i]));
            tmp[0].clear();
            for (int z : e[y]) {
                if (z == fa[y]) continue;
                if (z == hson[y]) continue;
                for (int i = dfn[z]; i < dfn[z] + siz[z]; i++) Ers(idfn[i]);
                for (int i : tmp[z]) ChMax(ans[i], Query(1, ql[i], qr[i]));
                for (int i = dfn[z]; i < dfn[z] + siz[z]; i++) Ins(idfn[i], y);
                tmp[z].clear();
            }
			low = y;
        }
        for (int y = x; y; y = hson[y]) {
            Ers(y);
            for (int z : e[y]) {
                if (z == fa[y]) continue;
                if (z == hson[y]) continue;
                for (int i = dfn[z]; i < dfn[z] + siz[z]; i++) Ers(idfn[i]);
            }
        }
        for (int y = low; y; y = fa[y]) {
            for (auto p : qry[y]) {
                int i = p[1];
                if (T.Ask(ql[i], qr[i])) ChMax(ans[i], y);
            }
            F(y, 1);
            for (int z : e[y]) {
                if (z == fa[y]) continue;
                if (z == hson[y]) continue;
                for (int i = dfn[z]; i < dfn[z] + siz[z]; i++) F(idfn[i], 1);
            }
            if (y == x) break;
        }
        for (int y = x; y; y = hson[y]) {
            F(y, -1);
            for (int z : e[y]) {
                if (z == fa[y]) continue;
                if (z == hson[y]) continue;
                for (int i = dfn[z]; i < dfn[z] + siz[z]; i++) F(idfn[i], -1);
            }
        }
    }
}

class FastIO {
private:
    static const int chunk = 1 << 18;
    char *ibuf, *p1, *p2, *obuf, *op, *oe;

    inline void flush_output(int len = chunk) {
        fwrite(obuf, 1, len, stdout), op = obuf;
    }

public:
    inline char nc(void) {
        if (p1 == p2) {
            p2 = (p1 = ibuf) + fread(ibuf, 1, chunk, stdin);
            if (p1 == p2) return EOF;
        }
        return *p1++;
    }
    inline void pc(char c) {
        if (op == oe) flush_output();
        *op++ = c;
    }
    FastIO(void) {
        p1 = p2 = ibuf = (char *)(malloc(chunk));
        op = obuf = (char *)(malloc(chunk)), oe = obuf + chunk;
    }
    ~FastIO(void) {
        flush_output(op - obuf);
        free(ibuf), free(obuf);
    }
    inline void flush(void) {
        flush_output(op - obuf);
    }
} __buf;

#define getchar()  __buf.nc()
#define putchar(x) __buf.pc(x)

template <class T>
inline void fast_read(T &x) {
    x = 0;
    static bool neg = false;
    static char c = __buf.nc();
    while (c < '0' || c > '9') {
        c = __buf.nc();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48), c = __buf.nc();
    }
    if (neg) x = -x;
}
template <class T>
inline void write(T x) {
    if (x > 9) write(x / 10);
    __buf.pc((x % 10) ^ 48);
}
template <typename T, typename... V>
inline void write(T x, V... v) {
    write(x), __buf.pc(' '), write(v...);
}
template <class T>
inline void writeln(T x) {
    write(x), __buf.pc('\n');
}
template <typename T, typename... V>
inline void writeln(T x, V... v) {
    write(x), __buf.pc(' '), writeln(v...);
}
template <typename T, typename... V>
inline void fast_read(T &t, V &...v) {
    fast_read(t), fast_read(v...);
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    fast_read(n, m, q);
    for (int i = 1, u, v; i < n; i++) {
        fast_read(u, v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for (int i = 1; i <= m; i++) fast_read(a[i]), pos[a[i]].push_back(i);
    for (int i = 1; i <= q; i++) fast_read(ql[i], qr[i], qu[i]);

	// cin>>n>>m>>q;
    // for(int i=1,u,v;i<n;i++){
    //     cin>>u>>v;
    //     e[u].push_back(v);
    //     e[v].push_back(u);
    // }
    // for(int i=1;i<=m;i++) cin>>a[i],pos[a[i]].push_back(i);
    // for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i]>>qu[i];

    GetHSon(1), GetTop(1, 1);
    for (int i = 1; i <= q; i++) InsQ(qu[i], i);
    Build(1, 1, m);
    Calc();

    for (int i = 1; i <= q; i++) writeln(ans[i]);

    return 0;
}
