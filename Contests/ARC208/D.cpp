#include<bits/stdc++.h>

using namespace std;

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		vector<int> a(n);
		for(int &x:a) cin>>x,x--;

		bool err=0;
		for(int i=0;i<n;i++) if(a[a[i]]!=i) err|=1;
		int c=0;
		for(int i=0;i<n;i++) if(a[i]==i) c++;
		if(n&1&&c!=1) err|=1;
		if((~n&1)&&(c&1)) err|=1;

		if(err){
			cout<<"No"<<endl;
			continue ;
		}

		vector<vector<array<int,2>>> e(n);
		map<int,int> mp;
		int m=n&1?n:n-1;
		for(int i=0;i<m;i++){
			for(int j=1;j<=m/2;j++){
				int u=(i-j+m)%m,v=(i+j)%m;
				e[i].push_back({u,v});
			}
			if(~n&1) e[i].push_back({i,n-1});
		}
		int cnt=0;
		for(int i=0,lft=-1;i<n;i++){
			if(a[i]<i) continue ;
			if(a[i]==i){
				if(n&1) mp[0]=i;
				else{
					if(~lft){
						mp[e[0][cnt][0]]=lft;
						mp[e[0][cnt][1]]=i;
						lft=-1;
						cnt++;
					}else lft=i;
				}
				continue ;
			}
			mp[e[0][cnt][0]]=i;
			mp[e[0][cnt][1]]=a[i];
			cnt++;
		}

		vector<vector<int>> ans(n,vector<int>(n,-1));
		if(n&1){
			for(int i=0;i<n;i++){
				ans[mp[i]][mp[i]]=i;
				for(auto p:e[i]){
					ans[mp[p[0]]][mp[p[1]]]=i;
					ans[mp[p[1]]][mp[p[0]]]=i;
				}
			}
		}else{
			for(int i=0;i<n-1;i++){
				for(auto p:e[i]){
					if(!i&&a[mp[p[0]]]==mp[p[0]]){
						ans[mp[p[0]]][mp[p[0]]]=i;
						ans[mp[p[1]]][mp[p[1]]]=i;
					}else{
						ans[mp[p[0]]][mp[p[1]]]=i;
						ans[mp[p[1]]][mp[p[0]]]=i;
					}
				}
			}
		}


		cout<<"Yes"<<endl;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(~ans[i][j]) cout<<ans[i][j]+1<<' ';
				else cout<<n<<' ';
			}
			cout<<endl;
		}
	}

	return 0;
}