#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;

int a[N],ms[N],n;

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		
		if(a[1]==-1) a[1]=1;
		for(int i=1;i<=n;i++){
			if(a[i]!=-1&&a[a[i]]==-1&&i<a[i]) a[a[i]]=1;
		}
		fill(ms+1,ms+n+1,n+1);

		for(int i=1;i<=n;i++) cout<<a[a[i]]<<' ';cout<<endl;
	}

	return 0;
}