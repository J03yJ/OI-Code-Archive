#include<bits/stdc++.h>

using namespace std;

ifstream fin("center.in");
ofstream fout("center.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e2+9;

int a[N][N],n,m;

inline array<double,2> Merge(array<double,2> a,array<double,2> b){
	if(a[0]>b[0]) swap(a[0],b[0]);
	if(b[0]-a[0]+a[1]>b[1]) return a;
	else if(b[0]-a[0]+b[1]>a[1]) return b;
	else{
		double x=(a[0]+b[0]+b[1]-a[1])/2;
		return {x,x-a[0]+a[1]};
	}
}

signed main(){
	cin>>n>>m;
	memset(a,0x3f,sizeof a);
	for(int i=1,u,v,w;i<=m;i++){
		cin>>u>>v>>w;
		a[u][v]=a[v][u]=min(a[u][v],w);
	}

	for(int i=1;i<=n;i++) a[i][i]=0;
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			if(i==k) continue ;
			for(int j=1;j<=n;j++){
				if(i==j) continue ;
				if(j==k) continue ;
				a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
			}
		}
	}

	double ans=1e18;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j) continue ;
			vector<array<double,2>> v,stk;
			for(int k=1;k<=n;k++){
				double tmp=double(a[i][k]+a[j][k]+a[i][j])/2;
				v.push_back({tmp-a[i][k],tmp});
			}
			sort(v.begin(),v.end(),[](auto p,auto q){
				return array<double,2>({p[0]+p[1],p[1]-p[0]})<array<double,2>({q[0]+q[1],q[1]-q[0]});
			});
			for(auto t:v){
				while(stk.size()&&stk.back()[1]-stk.back()[0]<=t[1]-t[0]) stk.pop_back();
				stk.push_back(t);
			}
			sort(v.begin(),v.end());
			ans=min(ans,stk.front()[1]-abs(0-stk.front()[0]));
			ans=min(ans,stk.back()[1]-abs(a[i][j]-stk.back()[0]));
			for(int k=0;k+1<stk.size();k++){
				double x=(stk[k][0]+stk[k+1][0]+stk[k][1]-stk[k+1][1])/2;
				x=max(x,double(0));
				x=min(x,double(a[i][j]));
				ans=min(ans,stk[k][1]-abs(stk[k][0]-x));
			}
		}
	}

	cout<<fixed<<setprecision(2)<<ans<<endl;

	return 0;
}