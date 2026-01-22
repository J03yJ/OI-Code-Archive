#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

ifstream fin("railway.in");
ofstream fout("railway.out");
#define cin fin
#define cout fout
#define endl '\n'

vector<int> a,b,p;

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n,m;
		cin>>n>>m;
		a=vector<int>(n);
		b=vector<int>(m);
		for(int &x:a) cin>>x;
		for(int &x:b) cin>>x;

		p=vector<int>(n);
		iota(p.begin(),p.end(),0);
		sort(p.begin(),p.end(),[](int i,int j){return a[i]<a[j];});

		int ans=1;
		vector<int> vis(n+2,0);
		for(int i=0,j=0;i<m;i++){
			while(j<n&&a[p[j]]<=b[i]){
				int s=p[j]==0?1:vis[p[j]-1],t=p[j]+1==n?1:vis[p[j]+1];
				ans-=s+t-1;
				vis[p[j]]=1;
				j++;
			}
			cout<<ans<<' ';
		}
		cout<<endl;
		cerr<<T<<endl;
	}

	return 0;
}