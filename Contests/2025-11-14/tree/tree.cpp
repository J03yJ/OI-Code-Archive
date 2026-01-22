#include<bits/stdc++.h>

using namespace std;

namespace IO{
    const int SIZE=1<<21;
    static char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=oS+SIZE-1;
    int qr;
    char qu[55],c;
    bool f;
    #define getchar() (IO::iS==IO::iT?(IO::iT=(IO::iS=IO::ibuf)+fread(IO::ibuf,1,IO::SIZE,stdin),(IO::iS==IO::iT?EOF:*IO::iS++)):*IO::iS++)
    #define putchar(x) *IO::oS++=x,IO::oS==IO::oT?flush():0
    #define flush() fwrite(IO::obuf,1,IO::oS-IO::obuf,stdout),IO::oS=IO::obuf
    #define puts(x) IO::Puts(x)
    template<typename T>
    inline void read(T&x){
        for(f=1,c=getchar();c<48||c>57;c=getchar())f^=c=='-';
        for(x=0;c<=57&&c>=48;c=getchar()) x=(x<<1)+(x<<3)+(c&15); 
        x=f?x:-x;
    }
    template<typename T>
    inline void write(T x){
        if(!x) putchar(48); if(x<0) putchar('-'),x=-x;
        while(x) qu[++qr]=x%10^48,x/=10;
        while(qr) putchar(qu[qr--]);
    }
    inline void Puts(const char*s){
        for(int i=0;s[i];++i)
            putchar(s[i]);
        putchar('\n');
    }
    struct Flusher_{~Flusher_(){flush();}}io_flusher_;
}
using IO::read;
using IO::write;

using ll=long long;
using bint=__int128;
const int N=2e6+9;

int lim;
ll tr[N];
inline void Add(int x,ll k){while(x<=lim) tr[x]+=k,x+=x&-x;}
inline ll Ask(int x){ll sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}
inline ll Ask(int l,int r){return Ask(r)-Ask(l-1);}

int a[N],lc[N],rc[N],fa[N],dfn[N],siz[N],n,q,root,dcnt;
inline void DFS(int x){
	dfn[x]=++dcnt;
	if(lc[x]) DFS(lc[x]),DFS(rc[x]),siz[x]=siz[lc[x]]+siz[rc[x]]+1;
	else siz[x]=1;
}
inline bint SS(ll x){return bint(x)*(x+1)*(2*x+1)/6;}
inline bint F(int x,ll l,ll r){return (SS(r)-SS(l))-2*(bint(Ask(dfn[x],dfn[x]+siz[x]-1))*(l+1));}

signed main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);

	read(n),read(q);
	for(int i=1;i<=(n<<1)-1;i++) read(lc[i]),read(rc[i]),fa[lc[i]]=fa[rc[i]]=i;
	for(int i=1;i<=(n<<1)-1;i++) if(!fa[i]) root=i;
	lim=n<<1;

	DFS(root);
	while(q--){
		int u,y,v,l1,r1,l2,r2;
		read(u),read(y),read(v),read(l1),read(r1),read(l2),read(r2);
		Add(dfn[u],y-a[u]);
		a[u]=y;
		write(F(v,l1,r1)-F(v,l2,r2)),IO::Puts("");
	}

	return 0;
}