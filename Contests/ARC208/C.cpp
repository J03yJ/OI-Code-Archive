#include<bits/stdc++.h>

using namespace std;

using ll=long long;

signed main(){
	int T;
	cin>>T;
	while(T--){
		ll c,x;
		cin>>c>>x;

		if((c^x)>x) cout<<(c^x)<<endl;
		else{
			ll tmp=c,n=0;
			for(int i=30,r=0;~i;i--){
				if(~c>>i&1) continue ;
				if(tmp-(1ll<<i+1)>=x){
					tmp-=1ll<<i+1;
					n|=1ll<<i;
				}
			}
			n|=1ll<<__lg(c)+1;
			if(tmp==x){
				cout<<n<<endl;
				assert((n^c)%n==x);
			}else cout<<-1<<endl;
		}
	}

	return 0;
}