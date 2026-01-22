#include<bits/stdc++.h>

using namespace std;

signed main(){
	int T;
	cin>>T;
	while(T--){
		long long n;
		cin>>n;
		if(n%4==0) cout<<"Even"<<endl;
		else if(n%2==0) cout<<"Same"<<endl;
		else cout<<"Odd"<<endl;
	}
}