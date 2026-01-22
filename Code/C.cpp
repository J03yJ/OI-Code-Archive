#include<bits/stdc++.h>
using namespace std;

#define int long long

const int p=998244353;
int qpow(int x,int y){
	int m=1;
	while(y){
		if(y&1) m=m*x%p;
		x=x*x%p;
		y>>=1;
	}
	return m;
}
vector<int> P,c;
int n,d,ans;
void dfs(int dep,int x,int mx){
	if(x>n) return ;
//	cout<<x<<' '<<mx<<' '<<dep<<endl;
	if(dep==P.size()){
		ans=(ans-x+p)%p;
		ans=(ans+qpow(x,mx+1))%p;
		return ;
	}
//	cout<<c[dep]<<' '<<P[dep]<<endl;
	for(int i=1,j=P[dep];i<=c[dep];i++,j*=P[dep]){
		dfs(dep+1,x*j,max(mx,(c[dep]+i-1)/i));
	}
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>d;
		ans=(n%p)*(n%p+1)%p*qpow(2,p-2)%p;
		
		int k=d;
		for(int i=2;i*i<=k;i++){
			if(k%i) continue ;
			P.push_back(i);
			c.push_back(0);
			while(k%i==0){
				k/=i;
				c.back()++;
			}
		}
		if(k!=1) P.push_back(k),c.push_back(1);
		
//		cout<<P.size()<<' '<<ans<<endl;
		dfs(0,1,0);
		cout<<ans<<endl;
		
		ans=0;
		P.clear();
		c.clear();
	}
}
