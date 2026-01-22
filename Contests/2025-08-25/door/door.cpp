#include<bits/stdc++.h>

using namespace std;

ifstream fin("door.in");
ofstream fout("door.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e3+9;
const int mod=1e9+7;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
	int res=1;
	while(y){
		if(y&1) MulAs(res,x);
		MulAs(x,x);
		y>>=1;
	}
	return res;
}
#define Inv(x) QPow(x,mod-2)

int f[N][N][2][2][3][3],n,m;

signed main(){
	cin>>n>>m;

	f[1][1][0][0][0][0]=1;
	for(int i=1;i<n;i++){
		for(int j=1;j<=i;j++){
			for(int rr:{0,1}){
				for(int yy:{0,1}){
					for(int rgg:{0,1,2}){
						for(int p:{0,1,2}){
							if(!f[i][j][rr][yy][rgg][p]) continue ;
							for(int q:{0,1,2}){
								if(rgg==1&&q!=1) continue ;
								if(i==1&&q==2) continue ;
								if(p==2&&q==1) continue ;
								int _i=i+1,_j=j+!q;
								int _rr=rr|(p==0&&q!=1);
								int _yy=yy|(p==2&&q==2);
								int _rgg=max(q==1?(rgg-1):0,!q&&(yy||p==2)?2:0);
								AddAs(f[_i][_j][_rr][_yy][_rgg][q],f[i][j][rr][yy][rgg][p]);
							}
						}
					}
				}
			}
		}
	}

	int ans=0;
	for(int j=m;j<=n;j++){
		for(int rr:{0,1}){
			for(int yy:{0,1}){
				for(int rgg:{0,1,2}){
					for(int p:{0,1,2}){
						if(j-(rr||!p)<m) continue ;
						if(p==1&&rgg==1) continue ;
						AddAs(ans,f[n][j][rr][yy][rgg][p]);
					}
				}
			}
		}
	}
	cout<<ans<<endl;

	return 0;
}