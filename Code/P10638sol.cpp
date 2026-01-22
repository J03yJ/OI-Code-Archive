#include <bits/stdc++.h>

using namespace std;

#define int long long 
constexpr int inf=1ll<<62;

__attribute__((always_inline)) inline void chmax(int &a, int b) { a=max(a,b); }
__attribute__((always_inline)) inline void chmin(int &a, int b) { a=min(a,b); }

constexpr int MAXN=6e5+10;

struct SG {
    #define ls(p) (p<<1)
    #define rs(p) (p<<1|1)
    #define mn(p) tr[p].mn
    #define se(p) tr[p].se
    #define add(p) tr[p].add
    #define cov(p) tr[p].cov
    #define ll(p) tr[p].l
    #define rr(p) tr[p].r
    #define len(p) (rr(p)-ll(p)+1)
    #define cnt(p) tr[p].cnt
    struct {
        int l, r;
        int add, cov;
        int mn, se; int cnt;
    } tr[MAXN<<2];
    void pushup(int p) {
        mn(p)=min(mn(ls(p)),mn(rs(p)));
        if (mn(ls(p))==mn(rs(p))) {
            se(p)=min(se(ls(p)),se(rs(p)));
            cnt(p)=cnt(ls(p))+cnt(rs(p));
        }
        else if (mn(ls(p))<mn(rs(p))) {
            se(p)=min(se(ls(p)),mn(rs(p)));
            cnt(p)=cnt(ls(p));
        }
        else {
            se(p)=min(se(rs(p)),mn(ls(p)));
            cnt(p)=cnt(rs(p));
        }
    }
    void build(int l, int r, int a[], int p=1) {
        ll(p)=l, rr(p)=r; cov(p)=-1;
        if (l==r) return mn(p)=a[l], se(p)=inf, cnt(p)=1, void();
        int mid=(l+r)>>1;
        build(l,mid,a,ls(p)); build(mid+1,r,a,rs(p));
        pushup(p);
    }

    void push_cover(int c, int p) {
        cov(p)=mn(p)=c; se(p)=inf; cnt(p)=len(p); add(p)=0;
    }
    
    void push_add(int add, int p) {
        mn(p)+=add; se(p)+=add; add(p)+=add;
    }
    
    void pushdown(int p) {
        if (~cov(p)) {
            push_cover(cov(p),ls(p)); push_cover(cov(p),rs(p));
            cov(p)=-1;
        }
        if (add(p)) {
            push_add(add(p),ls(p)); push_add(add(p),rs(p)); 
            add(p)=0;
        }
        ::chmax(mn(ls(p)),mn(p)); ::chmax(mn(rs(p)),mn(p));
    }

    void cover(int l, int r, int v, int p=1) {
        int cl=ll(p), cr=rr(p);
        if (l<=cl&&cr<=r) return push_cover(v,p);
        int mid=(cl+cr)>>1; pushdown(p);
        if (l<=mid) cover(l,r,v,ls(p));
        if (r>mid) cover(l,r,v,rs(p));
        pushup(p);
    }

    void addv(int l, int r, int v, int p=1) {
        int cl=ll(p), cr=rr(p);
        if (l<=cl&&cr<=r) return push_add(v,p);
        int mid=(cl+cr)>>1; pushdown(p);
        if (l<=mid) addv(l,r,v,ls(p));
        if (r>mid) addv(l,r,v,rs(p));
        pushup(p);
    }

    void chmax(int l, int r, int v, int p=1) {
        int cl=ll(p), cr=rr(p);
        if (mn(p)>=v) return;
        if (l<=cl&&cr<=r&&v<se(p)) {
            return mn(p)=v, void();
        }
        int mid=(cl+cr)>>1; pushdown(p);
        if (l<=mid) chmax(l,r,v,ls(p));
        if (r>mid) chmax(l,r,v,rs(p));
        pushup(p);
    }
    
    int ask(int l, int r, int p=1) {
        int cl=ll(p), cr=rr(p);
        if (l<=cl&&cr<=r) return cnt(p)*(mn(p)==0);
        int mid=(cl+cr)>>1, res=0; pushdown(p);
        if (l<=mid) res+=ask(l,r,ls(p));
        if (r>mid) res+=ask(l,r,rs(p));
        return res;
    }
} sg;

int n, m, a[MAXN];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin>>n>>m; for (int i=1; i<=n; ++i) cin>>a[i];
    sg.build(1,n,a);
    int op, l, r, z;
    while (m--) {
        cin>>op>>l>>r;
        if (op==1) {
            cin>>z; 
            sg.cover(l,r,z);
        }
        else if (op==2) {
            cin>>z; 
            sg.addv(l,r,z);
            sg.chmax(l,r,0);
        }
        else cout<<sg.ask(l,r)<<'\n';
    }
    
}