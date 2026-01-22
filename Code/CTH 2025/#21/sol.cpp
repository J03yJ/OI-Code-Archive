#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=3e5+9;
const ll inf=1e18;

vector<int> A,B;
int x[N],y[N],p[N],n;
struct Fenwick{
	ll tr[N];
	inline void Init(){fill(tr+1,tr+n+1,-inf);}
	inline void Insert(int x,ll k){while(x<=n) tr[x]=max(tr[x],k),x+=x&-x;}
	inline ll Query(ll x){ll ans=-inf;while(x) ans=max(ans,tr[x]),x&=x-1;return ans;}
}P,R;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
		if(x[i]==y[i]){
			cout<<"Platina"<<endl;
			return 0;
		}else if(x[i]<y[i]){
			y[i]-=2;
			A.push_back(i);
		}else{
			x[i]-=2;
			B.push_back(i);
		}
	}

	vector<int> val(y+1,y+n+1);
	val.push_back(INT_MIN);
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	for(int i=1;i<=n;i++) p[i]=lower_bound(val.begin(),val.end(),y[i])-val.begin();
	sort(A.begin(),A.end(),[](int i,int j){return x[i]<x[j];});
	sort(B.begin(),B.end(),[](int i,int j){return x[i]<x[j];});

	ll ans=-inf;
	P.Init(),R.Init();
	for(int i=0,j=0;i<B.size();i++){
		while(j<A.size()&&x[A[j]]<x[B[i]]){
			P.Insert(p[A[j]],2*x[A[j]]);
			R.Insert(n-p[A[j]]+1,2*x[A[j]]-y[A[j]]);
			j++;
		}
		ans=max(ans,P.Query(p[B[i]]-1)+2*y[B[i]]-x[B[i]]-y[B[i]]);
		ans=max(ans,R.Query(n-p[B[i]]+1)+2*y[B[i]]-x[B[i]]);
	}
	P.Init(),R.Init();
	for(int i=0,j=0;i<A.size();i++){
		while(j<B.size()&&x[B[j]]<=x[A[i]]){
			P.Insert(p[B[j]],2*y[B[j]]);
			R.Insert(n-p[B[j]]+1,2*y[B[j]]-y[B[j]]);
			j++;
		}
		ans=max(ans,P.Query(p[A[i]]-1)+2*x[A[i]]-x[A[i]]-y[A[i]]);
		ans=max(ans,R.Query(n-p[A[i]]+1)+2*x[A[i]]-x[A[i]]);
	}

	cout<<(ans>=0?"Platina":"Yuto")<<endl;

	return 0;
}