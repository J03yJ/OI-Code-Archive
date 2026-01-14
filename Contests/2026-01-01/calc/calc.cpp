#include<bits/stdc++.h>

using namespace std;

ifstream fin("calc.in");
ofstream fout("calc.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e5+9;
const int mod=1e9+7;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
	int res=1;
	while(y){
		if(y&1) MulAs(res,x);
		MulAs(x,x);
		y>>=1;
	}
	return res;
}
inline int Inv(int x){return QPow(x,mod-2);}

struct Data{
	int l0,a1,a2,b1,b2,ans;
	Data(){}
	Data(int _l0,int _a1,int _a2,int _b1,int _b2,int _ans){
		l0=_l0,a1=_a1,a2=_a2,b1=_b1,b2=_b2,ans=_ans;
	}
	friend inline Data operator +(Data x,Data y){
		return Data(Add(x.l0,y.l0),Add(x.a1,y.a1),
		Add(x.a2,y.a2),Add(x.b1,y.b1),Add(x.b2,y.b2),
		Add(Add(x.ans,y.ans),Add(Add(Mul(x.b2,y.l0),Mul(y.a2,x.l0)),Mul(mod-2,Mul(x.b1,y.a1)))));
	}
};
struct Node{
	int l,r,atag,btag;
	Data dat;
}tr[N<<2];

inline void PushUp(int x){tr[x].dat=tr[x<<1].dat+tr[x<<1|1].dat;}
inline void Push(int x,int at,int bt){
	AddAs(tr[x].atag,at);
	AddAs(tr[x].btag,bt);
	AddAs(tr[x].dat.a2,Mul(tr[x].dat.l0,Mul(at,at)));
	AddAs(tr[x].dat.a2,Mul(2,Mul(tr[x].dat.a1,at)));
	AddAs(tr[x].dat.b2,Mul(tr[x].dat.l0,Mul(bt,bt)));
	AddAs(tr[x].dat.b2,Mul(2,Mul(tr[x].dat.b1,bt)));
	AddAs(tr[x].dat.a1,Mul(tr[x].dat.l0,at));
	AddAs(tr[x].dat.b1,Mul(tr[x].dat.l0,bt));
}
inline void PushDown(int x){
	if(tr[x].atag||tr[x].btag){
		Push(x<<1,tr[x].atag,tr[x].btag);
		Push(x<<1|1,tr[x].atag,tr[x].btag);
		tr[x].atag=tr[x].btag=0;
	}
}

inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(tr[x].l==tr[x].r) return tr[x].dat=Data(1,0,0,0,0,0),void();
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Modify(int x,int l,int r,int at,int bt){
	if(l>r) return ;
	if(l<=tr[x].l&&tr[x].r<=r) return Push(x,at,bt);
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) Modify(x<<1,l,r,at,bt);
	if(r>mid) Modify(x<<1|1,l,r,at,bt);
	PushUp(x);
}
inline Data Query(int x,int l,int r){
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].dat;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return Query(x<<1,l,r);
	else if(l>mid) return Query(x<<1|1,l,r);
	else return Query(x<<1,l,r)+Query(x<<1|1,l,r);
}

int a[N],ql[N],qr[N],qx[N],ans[N],n,q;
vector<int> qry[N],pos[N];

signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i]>>qx[i];

	vector<int> val;
	val.push_back(0);
	for(int i=1;i<=n;i++) val.push_back(a[i]);
	for(int i=1;i<=q;i++) val.push_back(qx[i]);
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(val.begin(),val.end(),a[i])-val.begin();
		pos[a[i]].push_back(i);
	}
	for(int i=1;i<=q;i++){
		qx[i]=lower_bound(val.begin(),val.end(),qx[i])-val.begin();
		qry[qx[i]].push_back(i);
	}

	Build(1,1,n);
	for(int i=val.size()-1;i;i--){
		for(int j:pos[i]){
			cout<<i<<" + "<<j<<endl;
			Modify(1,j,n,val[i],0);
			Modify(1,j+1,n,0,val[i]);
		}
		for(int j:qry[i]){
			cout<<i<<" ? "<<j<<endl;
			ans[j]=Query(1,ql[j],qr[j]).ans;
		}
		cout<<"# "<<i<<" : "<<endl;
		for(int j=1;j<=n;j++) cout<<Query(1,j,j).a1<<' ';cout<<endl;
		for(int j=1;j<=n;j++) cout<<Query(1,j,j).a2<<' ';cout<<endl;
		for(int j=1;j<=n;j++) cout<<Query(1,j,j).b1<<' ';cout<<endl;
		for(int j=1;j<=n;j++) cout<<Query(1,j,j).b2<<' ';cout<<endl;
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}