#include<bits/stdc++.h>

using namespace std;

signed main(){
	int n,a,b;
	cin>>n>>a>>b;

	double t=1;
	while(n--){
		int l,r;
		cin>>l>>r;
		l=max(l,a),r=min(r,b);
		if(l>r) t=0;
		else t*=double(r-l)/(b-a);
	}

	cout<<fixed<<setprecision(10)<<1-t<<endl;

	return 0;
}