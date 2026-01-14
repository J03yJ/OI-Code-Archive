#include<bits/stdc++.h>
#include"testlib.h"
#define fo(i,l,r) for(int i=(l);i<=(r);++i)
#define fd(i,l,r) for(int i=(l);i>=(r);--i)
#define fu(i,l,r) for(int i=(l);i<(r);++i)
using namespace std;
const int N=512,O=131;
int n,m,C[N],p[O][N];
bool f[N][N][N];
int main(int argc,char *argv[])
{
    registerTestlibCmd(argc,argv);
	n=inf.readInt();
	m=ouf.readInt();
	if(m<1||130<m) quitf(_wa,"Wrong answer. Your k is not in [1,130].");
	fo(_,1,m)
	{
		fu(i,0,n) p[_][i]=C[i]=ouf.readInt();
		sort(C,C+n);
		fu(i,0,n) if(C[i]!=i) quitf(_wa,"Wrong answer. Your construction is not a permutation.");
	}
	fo(_,1,m)
	{
		fu(i,0,n) fu(j,i+1,n) fu(k,j+1,n) f[p[_][i]][p[_][j]][p[_][k]]=1;
	}
	fu(i,0,n) fu(j,0,n) if(i!=j) fu(k,0,n) if(i!=k&&j!=k&&!f[i][j][k]) cout<<i<<' '<<j<<' '<<k<<endl,quitf(_wa,"Wrong answer.");
	quitf(_ok,"Accepted.");
	return 0;
}
