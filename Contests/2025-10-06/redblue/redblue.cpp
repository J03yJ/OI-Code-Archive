#include<bits/stdc++.h>

using namespace std;

ifstream fin("redblue.in");
ofstream fout("redblue.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;

int a[N],b[N],ans[N],n,q;

inline void Solve(int n,vector<int> qry){
	vector<int> t(n+1,0);
	for(int i=1;i<=n;i++) t[i]=a[i];
	vector<int> res(n+1,0),mn1(n+1,0),mn2(n+2,0);
	mn1[0]=mn2[n+1]=INT_MAX;
	for(int i=1;i<=n;i++) mn1[i]=min(mn1[i-1],t[i]-(i-1));
	for(int i=n;i>=1;i--) mn2[i]=min(mn2[i+1],t[i]);
	for(int i=1;i<=n;i++) res[i]=min(mn1[i],mn2[i+1]-i);
	res[0]=mn2[1];

	ll c=0;
	for(int i=1;i<=n;i++) c+=t[i]-(i-1)-mn1[n];

	for(int i:qry){
		if(b[i]<=n) ans[i]=res[b[i]]+b[i];
		else{
			int k=(b[i]-n)>>1;
			if(k<=c) ans[i]=mn1[n]+b[i];
			else ans[i]=mn1[n]+b[i]-(k-c+n-1)/n;
		}
	}
}

signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=q;i++) cin>>b[i];

	sort(a+1,a+n+1);
	vector<int> q1,q2;
	for(int i=1;i<=q;i++){
		if((b[i]&1)==(n&1)||b[i]<=n) q1.push_back(i);
		else q2.push_back(i);
	}

	Solve(n,q1),Solve(n-1,q2);
	for(int i:q2) ans[i]=min(ans[i],a[n]);

	for(int i=1;i<=q;i++) cout<<ans[i]<<' ';cout<<endl;

	return 0;
}