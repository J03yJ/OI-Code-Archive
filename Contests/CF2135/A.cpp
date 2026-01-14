#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		vector<int> a(n);
		for(int &x:a) cin>>x;
		vector<int> f(n);
		vector<queue<int>> q(n+1);
		for(int i=0;i<n;i++){
			q[a[i]].push(i);
			if(q[a[i]].size()>a[i]) q[a[i]].pop();
			if(q[a[i]].size()==a[i]){
				if(q[a[i]].front()==0) f[i]=a[i];
				else f[i]=f[q[a[i]].front()-1]+a[i];
			}
			if(i) f[i]=max(f[i],f[i-1]);
		}
		cout<<f[n-1]<<endl;
	}

	return 0;
}