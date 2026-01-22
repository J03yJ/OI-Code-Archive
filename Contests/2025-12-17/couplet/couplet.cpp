#include<bits/stdc++.h>

using namespace std;

ifstream fin("couplet.in");
ofstream fout("couplet.out");
#define cin fin
#define cout fout

inline void Constr1(int n){
	if(n&1){
		for(int i=0;i<n;i++) cout<<i<<' ';cout<<endl;
	}else cout<<-1<<endl;
}
inline void Constr2(int n){
	if(n<=2){
		for(int i=0;i<=n;i++) cout<<i<<' ';cout<<endl;
	}else cout<<-1<<endl;
}

using ll=long long;
inline int QPow(int x,int y,int mod){
	int res=1;
	while(y){
		if(y&1) res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return res;
}

signed main(){
	int T,n;
	cin>>T>>n;

	if(T==1) Constr1(n);
	else Constr2(n);

	return 0;
}