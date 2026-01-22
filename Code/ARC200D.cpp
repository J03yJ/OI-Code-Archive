#include<bits/stdc++.h>

using namespace std;

signed main(){
	int T;
	cin>>T;
	while(T--){
		int m,k;
		cin>>m>>k;
		if(k==m){
			cout<<"Yes"<<endl;
			cout<<m<<endl;
			for(int i=0;i<m;i++) cout<<i<<' ';cout<<endl;
		}else if(k==2||k==4){
			if(m%k) cout<<"No"<<endl;
			else{
				cout<<"Yes"<<endl;
				cout<<k<<endl;
				for(int i=0;i<k;i++) cout<<i*(m/k)<<' ';cout<<endl;
			}
		}else if(k&1){
			cout<<"Yes"<<endl;
			cout<<(k+1)/2<<endl;
			for(int i=0;i<(k+1)/2;i++) cout<<i<<' ';cout<<endl;
		}else{
			cout<<"Yes"<<endl;
			cout<<k/2<<endl;
			cout<<0<<' ';
			for(int i=2;i<=k/2;i++) cout<<i<<' ';cout<<endl;
		}
	}

	return 0;
}