#include<bits/stdc++.h>

using namespace std;

using ll=long long;

signed main(){
	int n,m;
	cin>>n>>m;
	vector<vector<int>> a(n,vector<int>(m,0));
	for(auto &v:a) for(auto &x:v) cin>>x;
	ll k;
	cin>>k;

	int h=(m+1)/2;
	vector<ll> s1(1<<h,0),s2(1<<m-h,0),s3(1<<n,0);
	for(int i=0;i<n;i++){
		for(int j=0;j<h;j++){
			for(int s=0;s<(1<<h);s++) if(s>>j&1) s1[s]+=a[i][j];
		}
		for(int j=h;j<m;j++){
			for(int s=0;s<(1<<m-h);s++) if(s>>j-h&1) s2[s]+=a[i][j];
		}
		for(int j=0;j<m;j++){
			for(int s=0;s<(1<<n);s++) if(s>>i&1) s3[s]+=a[i][j];
		}
	}
	k=s3[(1<<n)-1]-k;

	for(int s=0;s<(1<<n);s++){
		if(s){
			int t=s^s-1;
			for(int i=0;i<n;i++){
				if(~t>>i&1) continue ;
				if(s>>i&1){
					for(int j=0;j<h;j++){
						for(int u=0;u<(1<<h);u++) if(u>>j&1) s1[u]-=a[i][j];
					}
					for(int j=h;j<m;j++){
						for(int u=0;u<(1<<m-h);u++) if(u>>j-h&1) s2[u]-=a[i][j];
					}
				}else{
					for(int j=0;j<h;j++){
						for(int u=0;u<(1<<h);u++) if(u>>j&1) s1[u]+=a[i][j];
					}
					for(int j=h;j<m;j++){
						for(int u=0;u<(1<<m-h);u++) if(u>>j-h&1) s2[u]+=a[i][j];
					}
				}
			}
		}

		vector<ll> p1(s1),p2(s2);
		sort(p1.begin(),p1.end(),less<ll>());
		sort(p2.begin(),p2.end(),less<ll>());
		for(ll x:p1){
			while(p2.size()&&x+p2.back()>k-s3[s]) p2.pop_back();
			if(p2.size()&&p2.back()+x==k-s3[s]){
				int p=0,q=0;
				for(int t=0;t<(1<<h);t++) if(s1[t]==x) p=t;
				for(int t=0;t<(1<<m-h);t++) if(s2[t]==p2.back()) q=t;
				p|=q<<h;
				cout<<"YES"<<endl;
				cout<<__builtin_popcount(s)+__builtin_popcount(p)<<endl;
				for(int i=0;i<n;i++) if(s>>i&1) cout<<1<<' '<<i+1<<endl;
				for(int i=0;i<m;i++) if(p>>i&1) cout<<2<<' '<<i+1<<endl;
				return 0;
			}
		}
	}

	cout<<"NO"<<endl;

	return 0;
}