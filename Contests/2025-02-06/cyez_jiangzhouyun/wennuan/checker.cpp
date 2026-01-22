#include<bits/stdc++.h>
#include"testlib.h"
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
const int N=1010;
int n,a[N][N];
void transform(int u,int v)
{
	if(!a[u][v]||std::abs(u-v)<=1||(u==1&&v==n)||(u==n&&v==1)) quitf(_wa,"#3");
	int x=0,y=0;
	fr(i,1,n) if(a[i][u]&&a[i][v]) (x?y:x)=i;
	a[u][v]=a[v][u]=0; a[x][y]=a[y][x]=1;
}
int main(int argc,char **argv)
{
	registerTestlibCmd(argc,argv);
	n=inf.readInt(); int q=(n>=20&&n<=100?10000:20000);
	int m=ouf.readInt(); if(q<m) quitf(_wa,"#1");
	fr(i,1,n){ int x=i,y=i%n+1; a[x][y]=a[y][x]=1; }
	fr(i,1,n-3){ int x=inf.readInt(),y=inf.readInt(); a[x][y]=a[y][x]=1; }
	while(m--){ int x=ouf.readInt(),y=ouf.readInt(); transform(x,y); }
	fr(i,1,n-3){ int x=inf.readInt(),y=inf.readInt(); if(!a[x][y]) quitf(_wa,"#2"); }
	quitf(_ok,"");
	return 0;
}