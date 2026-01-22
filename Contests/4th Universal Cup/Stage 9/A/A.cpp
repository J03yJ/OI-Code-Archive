#include<bits/stdc++.h>

using namespace std;

using ull=unsigned long long;

signed main(){
	for(int i:{5}){
		cout<<"# "<<i<<endl;
		ull x=i;
		for(int j=1;j<=64;j++,x*=x){
			cout<<" - "<<j<<" = "<<x<<endl;
		}
	}

	return 0;
}