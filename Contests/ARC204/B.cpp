#include<bits/stdc++.h>

using namespace std;

const int N=5e3+9;

template<class S,class T> inline void ChMax(S &x,T y){if(y>x) x=y;}

int p[N],vis[N],rk[N],n,k,m;
int f[N][N],w[N][N],su[N][N];

signed main(){
	cin>>n>>k;
	for(int i=1;i<=n*k;i++) cin>>p[i];
	m=n*k;

	int ans=0;
	for(int s=1;s<=m;s++){
		#define Prv(x) (((x)+t-1)%t)
		#define Nxt(x) (((x)+1)%t)
		#define Len(x,y) (((y)-(x)+t)%t)
		#define Arc(x,y,z) (Len(x,y)<=Len(x,z)&&Len(y,z)<=Len(x,z))
		if(vis[s]) continue ;
		vis[s]=1;
		vector<int> r({s});
		while(!vis[p[r.back()]]){
			r.push_back(p[r.back()]);
			vis[r.back()]=s;
		}
		int t=r.size();
		vector<vector<int>> imp(t);
		for(int i=0;i<t;i++) rk[r[i]]=i;
		for(int i=0;i<t;i++){
			for(int j=r[i]+n;j<=m;j+=n) if(vis[j]==s) w[i][rk[j]]++,imp[i].push_back(rk[j]);
			for(int j=r[i]-n;j>=1;j-=n) if(vis[j]==s) w[i][rk[j]]++,imp[i].push_back(rk[j]);
		}
		// cout<<s<<' '<<t<<" : ";
		// for(int i=0;i<t;i++) cout<<r[i]<<' ';cout<<endl;
		int res=0;
		for(int len=1;len<=t;len++){
			for(int i=0;i<t;i++){
				int j=(i+len-1)%t;
				if(!w[i][Nxt(j)]&&len!=t) continue ;
				// cout<<i<<' '<<j<<' '<<w[i][j]<<endl;
				for(int k=i;;k=Nxt(k)){
					for(int p:imp[k]){
						// cout<<" - "<<k<<' '<<p<<" = "<<Arc(k,p,j)<<endl;
						if(Arc(k,p,j)) ChMax(f[i][j],f[k][Prv(p)]+1);
					}
					if(k==j) break ;
				}
				if(len==t) res=max(res,f[i][j]);
			}
		}
		ans+=res;
		for(int len=1;len<=t;len++){
			for(int i=0;i<t;i++){
				int j=(i+len)%t;
				w[i][j]=f[i][j]=0;
			}
		}
	}

	cout<<ans<<endl;

	return 0;
}