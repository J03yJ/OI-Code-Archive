#include<bits/stdc++.h>

using namespace std;

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n,m,s;
		cin>>n>>m>>s;

		int ans=n+m,tmp=sqrt(s);
		for(int len=1;len<=min(tmp,n);len++){
			int i=(n+len-1)/len-1;
			int t=s/len;
			if(!t) continue ;
			int c=(m+t-1)/t-1;
			ans=min(ans,i+c);
		}
		for(int len=1;len<=min(tmp,m);len++){
			int i=(m+len-1)/len-1;
			int t=s/len;
			if(!t) continue ;
			int c=(n+t-1)/t-1;
			ans=min(ans,i+c);
		}

		cout<<ans<<endl;
	}

	return 0;
}