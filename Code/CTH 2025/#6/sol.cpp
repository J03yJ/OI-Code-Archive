#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;
using ll=long long;

int p[N],c[N],d[N],n;
ll a[N],b[N],s[N],fp,fq;

inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	cin>>fp>>fq;

	iota(p+1,p+n+1,1);
	sort(p+1,p+n+1,[](int i,int j){return a[i]<a[j];});
	for(int i=1;i<=n;i++) s[i]=s[i-1]+(b[i]=a[p[i]]);
	for(int i=1;i<=n;i++){
		auto Check=[&](int p){return fp*(s[i]-s[p-1])>=b[i]*(i-p+1)*fq;};
		int l=0,r=i;
		while(l+1<r){
			int mid=l+r>>1;
			if(Check(mid)) r=mid;
			else l=mid;
		}
		c[i]=i-r+1;
	}
	
	int t=*max_element(c+1,c+n+1);
	for(int i=1,j=1;i<=n;i++){
		if(c[i]==t){
			auto Check=[&](int p){return fp*(s[i]-s[i-t+1]+b[p])>=b[i]*t*fq;};
			int l=0,r=i-t+1;
			while(l+1<r){
				int mid=l+r>>1;
				if(Check(mid)) r=mid;
				else l=mid;
			}
			d[r]++,d[i+1]--;
		}
	}

	vector<int> ans;
	for(int i=1;i<=n;i++) if(!(d[i]+=d[i-1])) ans.push_back(p[i]);
	sort(ans.begin(),ans.end());

	cout<<ans.size()<<endl;
	for(int x:ans) cout<<x<<' ';cout<<endl;

	for(int i=1;i<=n+1;i++) d[i]=0;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}