#include<bits/stdc++.h>

using namespace std;

ifstream fin("redstone.in");
ofstream fout("redstone.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e5+9;
const int inf=1e9+7;

const int mod=16;
inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}

int a[N],c[N],d[N],n,k;
inline pair<vector<int>,int> Try(vector<int> v,int s){
	int m=v.size(),cnt=0;
	vector<int> c(m,0);
	AddAs(v[m-1],s),SubAs(v[0],s);
	cnt+=min(s,16-s);
	c[m-1]=s;
	for(int i=0;i<m-1;i++){
		int p=Sub(0,v[i]);
		AddAs(v[i],p),SubAs(v[i+1],p);
		cnt+=min(p,16-p);
		c[i]=p;
	}
	if(v[m-1]) return {c,inf};
	else return {c,cnt};
}

signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];

	int ans=inf;
	mt19937 rng(4649);

	int step=20;
	while(step--){
		int sum=0,g=__gcd(n,k);
		for(int i=1;i<=n;i++) d[i]=((a[i]-a[(i+n-2)%n+1])%mod+mod)%mod;
		for(int i=1;i<=g;i++){
			int mn=inf,p=-1;
			vector<int> tmp(n/g);
			for(int j=0;j<n/g;j++) tmp[j]=d[(i-1+1ll*j*k)%n+1];
			for(int j=0;j<mod;j++){
				int c=Try(tmp,j).second;
				if(c<mn) mn=c,p=j;
			}
			if(!~p){
				cout<<-1<<endl;
				return 0;
			}
			int r=rng()%mod;
			vector<int> op=Try(tmp,r).first;
			for(int j=0;j<n/g;j++) c[(i-1+1ll*j*k)%n+1]=op[j];
			sum+=Try(tmp,r).second;
		}

		int s=a[k];
		for(int i=1;i<=k;i++) AddAs(s,c[i]);

		int r=0;
		while(r<=mod&&Add(Mul(r,k/g),s)) r++;
		if(r==mod){
			cout<<-1<<endl;
			return 0;
		}

		auto GetW=[&](int rem,int t){
			int cnt=0;
			for(int i=0;i<n/g;i++){
				int p=(rem-1+1ll*i*k)%n+1;
				cnt-=min(c[p],16-c[p]);
				cnt+=min(Add(c[p],t),16-Add(c[p],t));
			}
			return cnt;
		};
		vector<int> f(mod,inf),b;
		f[0]=0;
		for(int i=1;i<=g;i++){
			b=f;
			for(int j=0;j<mod;j++){
				int w=GetW(i,j);
				for(int k=0;k<mod;k++){
					b[k]=min(b[k],f[Sub(k,j)]+w);
				}
			}
			f=b;
		}
		sum+=f[r];

		ans=min(ans,sum);
	}

	cout<<ans<<endl;

	return 0;
}