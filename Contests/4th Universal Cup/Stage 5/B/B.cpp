#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ld=long double;
const int N=2e5+9;
const ld pi=acosl(-1);
const ld eps=1e-18;

int a[N],b[N],c[N],n;
ld tl[N],tr[N];

inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i]>>c[i];

	vector<ld> val;
	for(int i=1;i<=n;i++){
		if(!a[i]&&!b[i]) continue ;
		tr[i]=atan2l(a[i],-b[i]);
		if(tr[i]>=0) tl[i]=tr[i]-pi;
		else tl[i]=tr[i]+pi;
		tl[i]+=eps,tr[i]-=eps;
		val.push_back(tl[i]);
		val.push_back(tr[i]);
	}
	val.push_back(-pi),val.push_back(pi);

	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());

	vector<int> d(val.size()<<1,0);
	for(int i=1;i<=n;i++){
		if(!a[i]&&!b[i]) continue ;
		int l=lower_bound(val.begin(),val.end(),tl[i])-val.begin();
		int r=lower_bound(val.begin(),val.end(),tr[i])-val.begin();
		if(tl[i]<=tr[i]) d[l<<1|1]++,d[r<<1]--;
		else{
			d[l<<1|1]++,d.back()--;
			d.front()++,d[r<<1]--;
		}
	}
	partial_sum(d.begin(),d.end(),d.begin());

	cout<<*max_element(d.begin(),d.end())<<endl;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}