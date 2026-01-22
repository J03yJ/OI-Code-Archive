#include<bits/stdc++.h>

using namespace std;

ifstream fin("constructive.in");
ofstream fout("constructive.out");
#define cin fin
#define cout fout
#define endl '\n'

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;

		if(n<=7){
			if(n==1) cout<<"1"<<endl;
			else if(n==2||n==3||n==4||n==6) cout<<"-1"<<endl;
			else if(n==5) cout<<"1 5 3 2 4"<<endl;
			else if(n==7) cout<<"1 5 3 7 6 2 4"<<endl;
			continue ;
		}

		vector<int> vis(n+1,0),l[2],r[2];
		for(int i=4;i<=n;i++){
			if(vis[i]) continue ;
			l[i&1].push_back(i),vis[i]=1;
			if((i^2)<=n) r[i&1].push_back(i^2),vis[i^2]=1;
		}
		for(int i:l[1]) cout<<i<<' ';
		cout<<1<<' ';
		for(int i:r[1]) cout<<i<<' ';
		cout<<3<<' '<<2<<' ';
		for(int i:l[0]) cout<<i<<' ';
		for(int i:r[0]) cout<<i<<' ';
		cout<<endl;
	}

	return 0;
}