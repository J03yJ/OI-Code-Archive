#include<bits/stdc++.h>

using namespace std;

using ll=long long;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		vector<array<ll,2>> p(n);
		for(auto &t:p) cin>>t[0]>>t[1];

		int lm=-1,rm=-1;
		sort(p.begin(),p.end(),less<array<ll,2>>());
		for(int i=0;i<n;i++){
			if(!~lm||(p[i][0]-p[lm][0])<=(p[i][1]-p[lm][1])) lm=i;
		}
		for(int i=n-1;~i;i--){
			if(!~rm||(p[rm][0]-p[i][0])<=(p[i][1]-p[rm][1])) rm=i;
		}

		ll step=1e9,s1=0,s2=0,tmp=0;
		cout<<"? U "<<step<<endl,cout.flush(),cin>>tmp;
		cout<<"? U "<<step<<endl,cout.flush(),cin>>tmp;
		cout<<"? L "<<step<<endl,cout.flush(),cin>>tmp;
		cout<<"? L "<<step<<endl,cout.flush(),cin>>s1;
		cout<<"? R "<<step<<endl,cout.flush(),cin>>tmp;
		cout<<"? R "<<step<<endl,cout.flush(),cin>>tmp;
		cout<<"? R "<<step<<endl,cout.flush(),cin>>tmp;
		cout<<"? R "<<step<<endl,cout.flush(),cin>>s2;

		ll dltx=p[rm][0]-p[lm][0],dlty=p[rm][1]-p[lm][1];
		s2+=dlty;
		ll h=(s1+s2-(ll(4e9)-dltx))/2;
		ll lpy=p[lm][1]+h,lpx=p[lm][0]-(s1-h);
		ll px=lpx+ll(2e9),py=lpy-ll(2e9);
		cout<<"! "<<px<<' '<<py<<endl,cout.flush();
	}

	return 0;
}