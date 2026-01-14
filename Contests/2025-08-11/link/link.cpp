#include<bits/stdc++.h>

using namespace std;

const int N=5e4+9;
const int K=1e1+9;
const int M=2e6+9;

int n,k;
char c[N][K][K];

int fi[M],to[M<<2],ne[M<<2],w[N<<2],adj=1;
inline void AddEdge(int x,int y,int z){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=z;
}
inline void AddFlow(int x,int y,int z){
	
}

signed main(){
	cin>>n>>k;
	for(int i=1;i<n;i++){
		for(int p=1;p<=k;p++){
			for(int q=1;q<=k;q++) cin>>c[i][p][q];
		}
	}

	return 0;
}