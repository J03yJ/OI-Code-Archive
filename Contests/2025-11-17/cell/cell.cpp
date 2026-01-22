#include<bits/stdc++.h>

using namespace std;

ifstream fin("cell.in");
ofstream fout("cell.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=5e3+9;
template<class T> inline void ChMin(T &x,T y){if(y<x) x=y;}

int c[N][N],f[N][N],x[N],n,m,q,T;
inline void Add(int l1,int r1,int l2,int r2){c[l1][l2]++,c[l1][r2+1]--,c[r1+1][l2]--,c[r1+1][r2+1]++;}
inline void Calc(){
	for(int i=0;i<T;i++){
		for(int j=0;j<T;j++){
			if(i) c[i][j]+=c[i-1][j];
			if(j) c[i][j]+=c[i][j-1];
			if(i&&j) c[i][j]-=c[i-1][j-1];
		}
	}
}

signed main(){
	cin>>m>>T;
	while(m--){
		int l,r;
		cin>>l>>r,r=(r+T-1)%T;
		if(l<=r){
			if(l>0) Add(0,l-1,l,r);
			if(r+1<T) Add(r+1,T-1,l,r);
		}else{
			if(r+1<l) Add(r+1,l-1,0,r);
			if(r+1<l) Add(r+1,l-1,l,T-1);
		}
	}
	Calc();

	memset(f,0x3f,sizeof f);
	for(int i=0;i<T;i++) f[i][i]=0;
	for(int L=1;L<T;L++){
		for(int k:{0,1}){
			for(int i=T-1;~i;i--){
				int j=(i+L)%T;
				ChMin(f[i][j],f[(i+1)%T][(j+1)%T]+1);
				if(c[i][j]) ChMin(f[i][j],f[(i+1)%T][j]+1);
			}
		}
	}

	cin>>q;
	while(q--){
		cin>>n;
		for(int i=0;i<n;i++) cin>>x[i];

		int ans=0x3f3f3f3f;
		for(int i=0;i<n;i++) ans=min(ans,f[x[(i+1)%n]][x[i]]);

		cout<<ans<<endl;
	}

	return 0;
}