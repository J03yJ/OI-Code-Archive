#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;

int n,m,k;
array<int,2> a[N],b[N];

inline ll Calc(int op){
	ll t=0;
	int i=1,j=1,cnt=0;
	while(i<=n||j<=m){
		cnt++;
		if(op==0){
			if(i<=n){
				t=max(t,1ll*k*cnt+a[i][0]);
				i++;
			}
		}else if(op==1){
			if(j<=m){
				t=max(t,1ll*k*cnt+b[j][0]);
				j++;
			}
		}
		op^=1;
	}
	return t;
}
inline vector<array<ll,3>> Work(ll t,int op){
	vector<array<ll,3>> ans;
	int i=1,j=1,cnt=0;
	while(i<=n||j<=m){
		cnt++;
		if(op==0){
			if(i<=n){
				ans.push_back({t-1ll*k*cnt,op,a[i][1]});
				i++;
			}
		}else if(op==1){
			if(j<=m){
				ans.push_back({t-1ll*k*cnt,op,b[j][1]});
				j++;
			}
		}
		op^=1;
	}
	reverse(ans.begin(),ans.end());
	return ans;
}

inline void Solve(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) cin>>a[i][0],a[i][1]=i;
	for(int i=1;i<=m;i++) cin>>b[i][0],b[i][1]=i;

	sort(a+1,a+n+1,greater<array<int,2>>());
	sort(b+1,b+m+1,greater<array<int,2>>());

	if(Calc(0)<Calc(1)){
		ll t=Calc(0);
		cout<<t<<endl;
		auto ans=Work(t,0);
		for(auto p:ans) cout<<p[0]<<' '<<p[1]<<' '<<p[2]<<endl;
	}else{
		ll t=Calc(1);
		cout<<t<<endl;
		auto ans=Work(t,1);
		for(auto p:ans) cout<<p[0]<<' '<<p[1]<<' '<<p[2]<<endl;
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	Solve();

	return 0;
}