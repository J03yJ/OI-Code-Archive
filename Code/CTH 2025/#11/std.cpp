#include<bits/stdc++.h>
using namespace std;
#define i128 __int128
#define ull unsigned long long
#define int long long
#define fo(i,l,r) for(int i=l;i<=r;i++)
#define fd(i,r,l) for(int i=r;i>=l;i--)
#define sqrt __builtin_sqrt
#define pii pair<int,int>
#define pll pair<long long,long long>
#define pdd pair<double,double>
#define tiii tuple<int,int,int>
#define fi first
#define se second
#define mem(a,b) memset(a,b,sizeof a)
#define Gc() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,__SIZE,stdin),(iS==iT?EOF:*iS++)):*iS++)
namespace io{const int __SIZE=(1<<21)+1;char ibuf[__SIZE],*iS,*iT,obuf[__SIZE],*oS=obuf,*oT=oS+__SIZE-1,__c,qu[55];int __f,qr,_eof;inline void flush(){fwrite(obuf,1,oS-obuf,stdout),oS=obuf;}inline void gc(char&x){x=Gc();}inline void pc(char x){*oS++=x;if(oS==oT)flush();}inline void pstr(const char*s){int __len=strlen(s);for(__f=0;__f<__len;++__f)pc(s[__f]);}inline void gstr(char *s){for(__c=Gc();__c<32||__c>126||__c==' ';)__c=Gc();for(;__c>31&&__c<127&&__c!=' '&&__c!='\n'&&__c!='\r';++s,__c=Gc())*s=__c;*s=0;}template<class I>inline bool gi(I&x){_eof=0;for(__f=1,__c=Gc();(__c<'0'||__c>'9')&&!_eof;__c=Gc()){if(__c=='-')__f=-1;_eof|=__c==EOF;}for(x=0;__c<='9'&&__c>='0'&&!_eof;__c=Gc())x=x*10+(__c&15),_eof|=__c==EOF;x*=__f;return!_eof;}template<class I>inline void print(I x){if(!x)pc('0');if(x<0)pc('-'),x=-x;while(x)qu[++qr]=x%10+'0',x/=10;while(qr)pc(qu[qr--]);}struct Flusher_{~Flusher_(){flush();}}io_flusher_;}using io::pc;using io::gc;using io::pstr;using io::gstr;using io::gi;using io::print;
const int mod=998244353;
template<typename T>inline void cmax(T&x,T y){x=max(x,y);}
template<typename T>inline void cmin(T&x,T y){x=min(x,y);}
template<typename T>inline T fplus(T x,T y){return x+y-(x+y>=mod?mod:0);}
template<typename T>inline T fminus(T x,T y){return x-y+(x-y<0?mod:0);}
template<typename T>inline void cplus(T&x,T y){x=fplus(x,y);}
template<typename T>inline void cminus(T&x,T y){x=fminus(x,y);}
template<typename T>inline T qp(T x,T y){T ans=1;while(y){if(y&1)ans=ans*x%mod;x=x*x%mod,y>>=1;}return ans;}
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
inline int rdint(int l,int r){return uniform_int_distribution<>(l,r)(rnd);}
inline double rddbl(double l,double r){return uniform_real_distribution<>(l,r)(rnd);}
int n,m,rt[100005],a[100005],st[19][100005],sk[100005],tp,l,r,k;
struct sustainable_segment_tree{
	#define mid (l+r>>1)
	int cnt,tr[10000005],ls[10000005],rs[10000005];
	void update(int x,int&y,int l,int r,int k,int p){
//		if(r==2e9)cout<<k<<' '<<p<<'\n';
		tr[y=++cnt]=tr[x]+p;
		if(l==r)return;
		if(k<=mid)update(ls[x],ls[y],l,mid,k,p),rs[y]=rs[x];
		else update(rs[x],rs[y],mid+1,r,k,p),ls[y]=ls[x];
	}
	int query(int x,int y,int l,int r,int k){
		if(l==r)return tr[y]-tr[x];
		if(k<=mid)return query(ls[x],ls[y],l,mid,k);
		return tr[ls[y]]-tr[ls[x]]+query(rs[x],rs[y],mid+1,r,k);
	}
	#undef mid
}seg;
int query(int l,int r){
	if(l>r)return 2e9;
	int k=__lg(r-l+1);
	return min(st[k][l],st[k][r-(1<<k)+1]);
}
bool check(int w,int l,int r,int k){
	if(query(l,r)>w/2)return 0;
	int L=l,R=r,mid,lx,rx;
	while(L<=R){
		mid=L+R>>1;
		if(query(l,mid)<=w/2)lx=mid,R=mid-1;
		else L=mid+1;
	}
	L=l,R=r;
	while(L<=R){
		mid=L+R>>1;
		if(query(mid,r)<=w/2)rx=mid,L=mid+1;
		else R=mid-1;
	}
	// debug(w,l,r,k,lx,rx,seg.query(rt[lx-1],rt[rx],0,2e9,w));
//	int tmp=seg.query(rt[lx-1],rt[rx],0,2e9,w);
	int tmp=seg.query(rt[lx],rt[rx],0,2e9,w)+1;
//	int tmp=seg.query(rt[rx],0,2e9,w)-seg.query(rt[lx],0,2e9,w)+1;
//	cout<<w<<' '<<tmp<<' '<<lx<<' '<<rx<<' '<<seg.tr[rt[lx-1]]<<' '<<seg.tr[rt[rx]]<<"\n";
	return tmp+(max(a[lx],a[rx])+min(query(l,lx-1),query(rx+1,r))<=w)>=k;
}
void solve(){
	cin>>n>>m;
	fo(i,1,n){
//		cout<<i<<'\n';
		cin>>a[i],st[0][i]=a[i],seg.update(rt[i-1],rt[i],0,2e9,a[i]*2,1);
		while(tp&&a[sk[tp]]>=a[i]){
			if(tp^1)
				seg.update(rt[i],rt[i],0,2e9,a[sk[tp]]+max(a[sk[tp-1]],a[i]),1),
				seg.update(rt[i],rt[i],0,2e9,a[sk[tp]]*2,-1);
			tp--;
		}
		sk[++tp]=i;
	}
	fo(j,1,18)fo(i,1,n-(1<<j)+1)st[j][i]=min(st[j-1][i],st[j-1][i+(1<<(j-1))]);
	while(m--){
		cin>>l>>r>>k;
		int L=0,R=2e9,mid,ans;
		while(L<=R){
			mid=L+R>>1;
//			cout<<mid<<' '<<l<<' '<<r<<' '<<k<<' '<<check(mid,l,r,k)<<'\n';
			if(check(mid,l,r,k))ans=mid,R=mid-1;
			else L=mid+1;
		}
		cout<<ans<<'\n';
//		cout<<check(92,l,r,k)<<'\n';
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T=1;
	// cin>>T;
	while(T--)solve();
	return 0;
}
/*
5 3
2 6 1 5 4
1 5 4
1 3 2
1 5 3

10 1
29 63 79 82 20 76 95 67 38 99
4 5 2

102
*/ 