#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=1e6+9;

ifstream fin("coldfish.in");
ofstream fout("coldfish.out");
#define cin fin
#define cout fout
#define endl '\n'

int a[N],f[N],g[N],h[N],n;

inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	a[n+1]=0;
	int L=0,R=n+1;
	while(!a[L]&&L<=n) L++;
	while(!a[R]&&R>=1) R--;
	if(!R) return cout<<0<<endl,void();
	else if(L==R) return cout<<(a[L]==1)<<endl,void();

	a[L]++,a[R]++;
	for(int i=L;i<=R;i++) a[i]-=2,a[i]-=a[i-1];
	// for(int i=L;i<=R;i++) cout<<a[i]<<' ';cout<<endl;

	int p[2]={n+1,n+1};
	for(int i=L;i<=R;i++){
		if(a[i]<0){
			if(a[i]==-1) p[i&1]=min(p[i&1],i);
			else return cout<<0<<endl,void();
		}
	}

	ll ans=0,cnt=0;
	f[R+1]=g[R+1]=h[R+1]=1;
	for(int i=R;i>=L;i--){
		f[i]=(a[i]>=0)&f[i+1];
		g[i]=(a[i]-(i&1)+(~i&1)>=0)&g[i+1];
		h[i]=(a[i]+(i&1)-(~i&1)>=0)&h[i+1];
		if(i==R){
			f[i]&=a[i]==0;
			g[i]&=a[i]-(i&1)+(~i&1)==0;
			h[i]&=a[i]+(i&1)-(~i&1)==0;
		}

		if(~i&1){
			if(p[1]>=i){
				if(f[i]) ans+=(min(i-1,p[0]-1)-L>>1)+1;
			}
			if(p[0]>=i){
				if(h[i]) ans+=(min(i-2,p[1]-1)-L>>1)+1;
			}
			if(p[0]>=i&&p[1]>=i&&h[i]) cnt++;
		}else{
			if(p[0]>=i){
				if(f[i]) ans+=(min(i-1,p[1]-1)-L>>1)+1;
			}
			if(p[1]>=i){
				if(g[i]) ans+=(min(i-2,p[0]-1)-L>>1)+1;
			}
			if(p[0]>=i&&p[1]>=i&&g[i]) cnt++;
		}
	}
	ans<<=1;

	cout<<ans+cnt<<endl;
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}