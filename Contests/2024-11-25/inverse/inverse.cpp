#include<bits/stdc++.h>

using namespace std;

namespace IO {
	const int SIZE = (1 << 25) + 1;
	char ibuf[SIZE], *iS, *iT;
	char obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[64];
	int f, qr;
	
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	
	inline void flush () {
		fwrite (obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	inline void Put (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	template <class I> inline void Read (I &x) {
		for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;
		for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); 
		x = f == -1 ? -x : x;
	}
	template <class I> inline void Write (I x) {
		if (! x) Put ('0'); if (x < 0) Put ('-'), x = -x;
		while (x) qu[ ++ qr] = x % 10 + '0',  x /= 10;
		while (qr) Put (qu[qr -- ]);
	}
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using IO :: Read;
using IO :: Put;
using IO :: Write;

const int N=1e6+9;

int a[N],p[N],q[N],n;
int pl[N],pr[N],ql[N],qr[N];
vector<array<int,3>> seg[N];

struct Node{
    int l,r,dat,tag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag

void Push(int x,int k){dat(x)+=k,tag(x)+=k;}
void PushDown(int x){Push(x<<1,tag(x)),Push(x<<1|1,tag(x)),tag(x)=0;}
void PushUp(int x){dat(x)=max(dat(x<<1),dat(x<<1|1));}
void Build(int x,int l,int r){
    l(x)=l,r(x)=r;
    if(l(x)==r(x)) return ;
    int mid=(l(x)+r(x))>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
}
void Modify(int x,int l,int r,int k){
    if(l<=l(x)&&r(x)<=r) return Push(x,k);
    int mid=(l(x)+r(x))>>1;
    PushDown(x);
    if(l<=mid) Modify(x<<1,l,r,k);
    if(r>mid) Modify(x<<1|1,l,r,k);
    PushUp(x);
}

int main(){
    freopen("inverse.in","r",stdin);
    freopen("inverse.out","w",stdout);

    Read(n);
    for(int i=1;i<=n;i++) Read(a[i]);

    p[0]=0;
    for(int i=1;i<=n;i++){
        p[i]=max(p[i-1],a[i]);
        pr[i]=i;
        pl[i]=upper_bound(p+1,p+i+1,a[i])-p;
    }
    q[n+1]=n+1;
    for(int i=n;i>=1;i--){
        q[i]=min(q[i+1],a[i]);
        ql[i]=i;
        qr[i]=lower_bound(q+i,q+n,a[i])-q-1;
    }
    // for(int i=1;i<=n;i++) cout<<p[i]<<' ';cout<<endl;
    // for(int i=1;i<=n;i++) cout<<q[i]<<' ';cout<<endl;
    // for(int i=1;i<=n;i++) cout<<pl[i]<<' '<<pr[i]<<' '<<ql[i]<<' '<<qr[i]<<endl;

    int ans=0;
    for(int i=1;i<=n;i++){
        if(pl[i]>pr[i]||ql[i]>qr[i]) continue ;
        seg[pl[i]].push_back({ql[i],qr[i],1});
        seg[pr[i]+1].push_back({ql[i],qr[i],-1});
    }
    Build(1,1,n);
    for(int i=1;i<=n;i++){
        for(auto t:seg[i]) Modify(1,t[0],t[1],t[2]);
        ans=max(ans,dat(1));
    }
    cout<<(ans<<1|1)<<endl;

    return 0;
}