#include<bits/stdc++.h>

using namespace std;

ifstream fin("seq.in");
ofstream fout("seq.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;
const ll inf=1e18;

struct Mat{
	ll a[4];
	Mat(){}
	Mat(ll _0,ll _1,ll _2,ll _3){
		a[0]=_0,a[1]=_1,a[2]=_2,a[3]=_3;
	}
	inline ll& operator [](int i){return a[i];}
	inline Mat operator *(Mat b){
		Mat c;
		c[0]=min(a[0]+b[0],a[1]+b[2]);
		c[1]=min(a[0]+b[1],a[1]+b[3]);
		c[2]=min(a[2]+b[0],a[3]+b[2]);
		c[3]=min(a[2]+b[1],a[3]+b[3]);
		return c;
	}
}I(0,inf,inf,0);

struct Node{
	int l,r;
	Mat dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat

inline void PushUp(int x){dat(x)=dat(x<<1|1)*dat(x<<1);}
inline void Build(int x,int l,int r){
	l(x)=l,r(x)=r;
	if(l(x)==r(x)) return dat(x)=I,void();
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Modify(int x,int pos,Mat k){
	if(l(x)==r(x)) return dat(x)=k,void();
	int mid=l(x)+r(x)>>1;
	if(pos<=mid) Modify(x<<1,pos,k);
	else Modify(x<<1|1,pos,k);
	PushUp(x);
}

int a[N],b[N],d[N],n,x,y,z;
int p[N<<1],pos[N<<1],qcnt;
Mat qk[N<<1];
ll t[N<<1];

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>x>>y>>z;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) cin>>b[i];

		ll cur=0;
		for(int i=1;i<=n;i++){
			d[i]=a[i]-b[i];
			if(d[i]>0){
				ll l=cur,r=cur+d[i];
				t[++qcnt]=l,pos[qcnt]=i;
				qk[qcnt]=Mat(inf,-1ll*i*z,1ll*i*z,y);
				t[++qcnt]=r,pos[qcnt]=i;
				qk[qcnt]=I;
			}else if(d[i]<0){
				ll l=cur+d[i],r=cur;
				t[++qcnt]=l,pos[qcnt]=i;
				qk[qcnt]=Mat(inf,-1ll*i*z,1ll*i*z,x);
				t[++qcnt]=r,pos[qcnt]=i;
				qk[qcnt]=I;
			}
			cur+=d[i];
		}

		ll ans=0;
		Build(1,1,n);
		iota(p+1,p+qcnt+1,1);
		sort(p+1,p+qcnt+1,[](int i,int j){return t[i]<t[j];});
		for(int i=1;i<=qcnt;i++){
			ans+=(t[p[i]]-t[p[i-1]])*(dat(1).a[3]);
			Modify(1,pos[p[i]],qk[p[i]]);
		}

		cout<<ans<<endl;

		qcnt=0;
	}

	return 0;
}