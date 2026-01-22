#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=2e3+9;

void solve(int n,vector<vector<int>> a,ll &ans,vector<int> &sol){
	int lim=n*(n+1)/2;
	vector<int> l(lim+1,0),r(lim+1,0);
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++){
			l[a[i][j]]=j;
			r[a[i][j]]=i;
		}
	}

	ans=0;
	sol.resize(n,0);
	vector<int> req(n);
	iota(req.begin(),req.end(),0);
	for(int i=lim;i>=1;i--){
		if(r[i]>=req[l[i]]){
			ans+=i;
			int val=i,p=l[i];
			while(sol[p]){
				if(r[val]<r[sol[p]]) swap(val,sol[p]);
				p++;
			}
			sol[p]=val;
			for(int j=n-1;~j;j--){
				if(!sol[j]) req[j]=j;
				else{
					req[j]=j+1<n?req[j+1]:n;
					if(r[sol[j]]>=req[j]) req[j]=j;
				}
			}
		}
	}
}

signed main(){
	int n;
	cin>>n;
	vector<vector<int>> a(n);
	for(int i=0;i<n;i++){
		a[i].resize(i+1);
		for(int &x:a[i]) cin>>x;
	}
	
	ll ans=0;
	vector<int> sol;
	solve(n,a,ans,sol);

	cout<<ans<<endl;
	for(int i=0;i<n;i++) cout<<sol[i]<<' ';cout<<endl;

	return 0;
}