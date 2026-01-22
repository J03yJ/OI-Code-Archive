#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;

int a[N],n,m,q;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>q>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	while(q--){
		int l,r,v;
		cin>>l>>r>>v;
		vector<int> b(a+l,a+r+1);
		for(int &x:b) if(x<v) x+=m;
		b.push_back(v),b.push_back(v+m);
		sort(b.begin(),b.end());
		int ans=0;
		for(int i=1;i<b.size();i++) ans=max(ans,b[i]-b[i-1]);
		cout<<m-ans<<endl;
	}

	return 0;
}