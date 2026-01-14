#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e6+9;

struct Data{
	int f,g,ans;
	Data(){}
	Data(int _f,int _g,int _ans){f=_f,g=_g,ans=_ans;}
	Data(int _f,int _g){f=_f,g=_g,ans=f+g;}
	friend inline Data operator +(Data x,Data y){return Data(max(x.f,y.f),max(x.g,y.g),max(max(x.ans,y.ans),x.f+y.g));}
};
struct Node{
	int l,r;
	Data dat;
}tr[N<<2];

inline void PushUp(int x){tr[x].dat=tr[x<<1].dat+tr[x<<1|1].dat;}
inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(tr[x].l==tr[x].r) return ;
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Set(int x,int pos,Data k){
	if(tr[x].l==tr[x].r) return tr[x].dat=k,void();
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) Set(x<<1,pos,k);
	else Set(x<<1|1,pos,k);
	PushUp(x);
}
inline Data Query(int x,int l,int r){
	if(l>r) return Data(0,0,0);
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].dat;
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return Query(x<<1,l,r);
	else if(l>mid) return Query(x<<1|1,l,r);
	else return Query(x<<1,l,r)+Query(x<<1|1,l,r);
}

char op[N];
int a[N],ra[N],rp[N],n,q,tot;
inline void Discretize(){
	vector<array<int,2>> val;
	rp[0]=1;
	for(int i=1;i<=q;i++){
		rp[i]=rp[i-1];
		if(op[i]=='<') rp[i]--;
		else if(op[i]=='>') rp[i]++;
		val.push_back({ra[i],rp[i]});
	}
	val.push_back({0,0});
	for(int i=1;i<=n;i++) val.push_back({a[i],i});
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	tot=val.size()-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(val.begin(),val.end(),array<int,2>({a[i],i}))-val.begin();
	for(int i=1;i<=q;i++) ra[i]=lower_bound(val.begin(),val.end(),array<int,2>({ra[i],rp[i]}))-val.begin();
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=q;i++){
		cin>>op[i];
		if(op[i]=='!') cin>>ra[i];
	}

	Discretize();

	int p=1;
	Build(1,1,tot);
	for(int i=n;i>1;i--){
		Set(1,a[i],Data(0,Query(1,a[i],tot).g+1));
	}
	Set(1,a[1],Data(1,0));

	for(int o=1;o<=q;o++){
		if(op[o]=='<'){
			Set(1,a[p],Data(0,Query(1,a[p],tot).g+1));
			p--;
		}else if(op[o]=='>'){
			p++;
			Set(1,a[p],Data(Query(1,1,a[p]).f+1,0));
		}else{
			Set(1,a[p],Data(0,0));
			a[p]=ra[o];
			Set(1,a[p],Data(Query(1,1,a[p]).f+1,0));
			cout<<tr[1].dat.ans<<endl;
		}
	}

	return 0;
}