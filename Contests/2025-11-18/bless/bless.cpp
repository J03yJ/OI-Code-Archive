#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fstrict-aliasing")

#include<bits/stdc++.h>

using namespace std;

class FastIO {
private:
    static const int chunk = 1 << 21;
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
    static char c = __buf.nc();
    while (c < '0' || c > '9') {
        c = __buf.nc();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48), c = __buf.nc();
    }
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

using ull=unsigned long long;
const int N=1e6+9;

int t[N],n,q;
ull a[N],G[N],g[N],d[N];
vector<int> imp;
vector<ull> coef;

signed main(){
	freopen("bless.in","r",stdin);
	freopen("bless.out","w",stdout);

	fast_read(n,q);
	for(int i=1;i<=n;i++) fast_read(a[i]),a[i]+=a[i-1];
	for(int i=1;i<=n;i++) g[i]=1,G[i]=i;

	for(int l=1,r;l<=n;l=r+1) r=n/(n/l),imp.push_back(n/l),coef.push_back(a[r]-a[l-1]);
	reverse(imp.begin(),imp.end());
	reverse(coef.begin(),coef.end());
	
	while(q--){
		int op;
		fast_read(op);
		if(op==1){
			ull x;
			int p,k,pk=1;
			fast_read(p,k,x);
			for(int i=1;i<=k;i++) pk*=p;
			vector<int> pr;
			for(ull _p=p;_p<=n;_p*=p) pr.push_back(_p);
			int m1=pr.size(),m2=imp.size();
			memset(t,0,m1<<2);
			memset(d,0,m2<<3);
			for(int i=1;i<imp.size();i++){
				for(int j=0;j<pr.size();j++){
					int cur=imp[i]/pr[j];
					if(cur==t[j]) break ;
					d[i]-=(G[cur]-G[t[j]])*g[pr[j]],t[j]=cur;
				}
				d[i]+=d[i-1];
				G[imp[i]]+=d[i];
			}
			g[pk]=x;
			memset(t,0,m1<<2);
			memset(d,0,m2<<3);
			for(int i=1;i<imp.size();i++){
				for(int j=0;j<pr.size();j++){
					int cur=imp[i]/pr[j];
					if(cur==t[j]) break ;
					d[i]+=(G[cur]-G[t[j]])*g[pr[j]],t[j]=cur;
				}
				d[i]+=d[i-1];
			}
			for(int i=0;i<imp.size();i++) G[imp[i]]+=d[i];
		}else{
			ull ans=0;
			for(int i=0;i<imp.size();i++) ans+=G[imp[i]]*coef[i];
			writeln(ans);
		}
	}

	return 0;
}