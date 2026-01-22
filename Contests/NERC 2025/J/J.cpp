#include<bits/stdc++.h>

using namespace std;

using ld=long double;
const int N=1e5+9;

ld C[31][31],p[N],q[N],e[31][31];
int _p[N];

signed main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>_p[i],p[i]=_p[i]/ld(100),q[i]=1-p[i];

	for(int i=0;i<=k;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++){
			C[i][j]=C[i-1][j]+C[i-1][j-1];
		}
	}
	for(int i=1;i<=n;i++){
		ld pp=1;
		for(int s=0;s<=30;s++){
			ld qq=1;
			for(int t=0;t<=30;t++){
				e[s][t]+=pp*qq;
				qq*=q[i];
			}
			pp*=p[i];
		}
	}
	for(int i=0;i<=30;i++){
		for(int j=0;j<=30;j++){
			e[i][j]/=n;
			cout<<i<<' '<<j<<" : "<<e[i][j]<<endl;
		}
	}

	ld ans=0;
	for(int i=0;i<=k;i++){
		for(int j=0;j<=i;j++){
			ld res=0,sum=0;
			for(int o=j;o<=i;o++){
				// sum+=C[i][o]*e[o][i-o];
				res+=C[i][o]*e[k-i+o][i-o];
			}
			// res/=sum;
			res*=powl(2,k-i);
			for(int o=0;o<j;o++){
				res+=C[i][o]*e[o][i-o];
			}
			cout<<i<<' '<<j<<" = "<<res<<endl;
			res*=1000;
			res-=1000;
			ans=max(ans,res);
		}
	}

	cout<<fixed<<setprecision(10)<<max(ans,ld(0))<<endl;

	return 0;
}