#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=3e5+9;
const int lgN=2e1;

int a[N],lp[N],rp[N],mnp[lgN][N],n;
inline int Cmp(int i,int j){return a[i]<a[j]?i:j;}
inline void InitMinP(){
	for(int i=1;i<=n;i++) mnp[0][i]=i;
	for(int k=1;k<=__lg(n);k++){
		for(int i=1;i+(1<<k)-1<=n;i++) mnp[k][i]=Cmp(mnp[k-1][i],mnp[k-1][i+(1<<k-1)]);
	}
}
inline int MinP(int l,int r){
	if(l>r) return 0;
	int k=__lg(r-l+1);
	return Cmp(mnp[k][l],mnp[k][r-(1<<k)+1]);
}

ll ans[N];

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	a[0]=a[n+1]=INT_MAX;

	vector<int> stk;
	for(int i=1;i<=n;i++){
		while(stk.size()&&a[stk.back()]>=a[i]) stk.pop_back();
		lp[i]=stk.size()?stk.back():0;
		stk.push_back(i);
	}
	stk.clear();
	for(int i=n;i>=1;i--){
		while(stk.size()&&a[stk.back()]>=a[i]) stk.pop_back();
		rp[i]=stk.size()?stk.back():n+1;
		stk.push_back(i);
	}

	InitMinP();
	map<array<int,2>,int> mp;
	vector<array<int,2>> ord;
	for(int i=1;i<=n;i++){
		if(lp[i]>=1) ord.push_back({lp[i],i});
		if(rp[i]<=n) ord.push_back({i,rp[i]});
	}
	sort(ord.begin(),ord.end(),[](auto x,auto y){return x[1]-x[0]<y[1]-y[0];});
	for(auto p:ord){
		int l=p[0],r=p[1];
		if(r-l-1<2) mp[{l,r}]=1;
		else{
			int x=MinP(l+1,r-1),y=Cmp(MinP(l+1,x-1),MinP(x+1,r-1));
			if(x>y) swap(x,y);
			mp[{l,r}]=mp[{x,y}]+1;
		}
		if(a[l]<a[r]){
			int L=lp[l],R=l;
			while(L+1<R){
				int mid=L+R>>1;
				if(a[MinP(mid,l-1)]>=a[r]) R=mid;
				else L=mid;
			}
			ans[mp[{l,r}]]+=1ll*(l-L)*(rp[r]-r);
		}else{
			int L=r,R=rp[r];
			while(L+1<R){
				int mid=L+R>>1;
				if(a[MinP(r+1,mid)]>=a[l]) L=mid;
				else R=mid;
			}
			ans[mp[{l,r}]]+=1ll*(l-lp[l])*(R-r);
		}
	}

	for(int i=1;i<=n;i++) cout<<ans[i]<<endl;

	return 0;
}