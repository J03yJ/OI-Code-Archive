#include<bits/stdc++.h>

using namespace std;

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		vector<int> a(n);
		for(int &x:a) cin>>x;

		int x=0,y=0;
		for(int z:a) x|=z,y^=z;
		
		if(x==y) cout<<"Bob"<<endl;
		else cout<<"Alice"<<endl;
	}

	return 0;
}