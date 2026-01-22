#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=2e5+9;
const ll inf=1e9;

struct Node{
	int lc,rc;
	ll tag,dat;
}tr[N<<5];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define tag(x) tr[x].tag
#define dat(x) tr[x].dat

int cnt;
inline int Allc(){return dat(++cnt)=inf,cnt;}
inline void PushUp(int x){if(lc(x)) dat(x)=min(dat(lc(x)),dat(rc(x)));}
inline void Push(int &x,ll k){
	if(!x) x=Allc();
	tag(x)+=k,dat(x)+=k;
}
inline void PushDown(int x){
	if(!tag(x)) return ;
	Push(lc(x),tag(x));
	Push(rc(x),tag(x));
	tag(x)=0;
}

inline void ChMin(int &x,int L,int R,int pos,ll k){
	if(!x) x=Allc();
	if(L==R) return dat(x)=min(dat(x),k),void();
	int mid=L+R>>1;
	PushDown(x);
	if(pos<=mid) ChMin(lc(x),L,mid,pos,k);
	if(pos>mid) ChMin(rc(x),mid+1,R,pos,k);
	PushUp(x);
}
inline void Modify(int &x,int L,int R,int l,int r,ll k){
	if(!x) x=Allc();
	if(l<=L&&R<=r) return Push(x,k);
	int mid=L+R>>1;
	PushDown(x);
	if(l<=mid) Modify(lc(x),L,mid,l,r,k);
	if(r>mid) Modify(rc(x),mid+1,R,l,r,k);
	PushUp(x);
}

ll mow(int n,int c,int b,vector<int> &a,vector<int> &v){
	int root=Allc(),dlt=0;
	auto ChM=[&](int p,ll k){ChMin(root,0,c-1,(p-dlt+c)%c,k);};
	auto Upd=[&](int l,int r,ll k){
		if(l>r||r>=c||l<0) return ;
		l=(l-dlt+c)%c;
		r=(r-dlt+c)%c;
		if(l<=r) Modify(root,0,c-1,l,r,k);
		else Modify(root,0,c-1,l,c-1,k),Modify(root,0,c-1,0,r,k);
	};
	ChM(0,0);
	for(int i=0;i<n;i++){
		int t=(c-v[i]%c)%c,k=(v[i]-1)/c;
		Upd(0,t-1,1ll*k*(a[i]+b)+a[i]);
		Upd(t,t,1ll*(k+1)*(a[i]+b));
		Upd(t+1,c-1,1ll*(k+1)*(a[i]+b)+a[i]);
		dlt=(dlt+v[i])%c;
		ChM(0,dat(root)+b);
	}
	Upd(1,c-1,b);
	return dat(root);
}

signed main(){
	int n,c,b;
	cin>>n>>c>>b;
	vector<int> a(n),v(n);
	for(int &x:a) cin>>x;
	for(int &x:v) cin>>x;

	cout<<mow(n,c,b,a,v)<<endl;

	return 0;
}