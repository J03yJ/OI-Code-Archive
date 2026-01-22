#include "testlib.h"
#include<bits/stdc++.h>
#define ci const int
using namespace std;
ci N=1e7+5;
int p[N],len,a[N],b[N];
bool vis[N],u[N];
int main(int argc,char* argv[]){
    registerTestlibCmd(argc,argv);
	vis[1]=1;
	for(int i=2;i<N;++i){
		if(!vis[i])p[++len]=i;
		for(int j=1;j<=len&&i*p[j]<N;++j){
			vis[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
	int T=inf.readInt();
	for(int t=1;t<=T;++t){
		int n=inf.readInt();
		a[1]=ouf.readInt(-1,n);
		if(a[1]!=-1)for(int i=2;i<=n;++i)a[i]=ouf.readInt(1,n);
		b[1]=ans.readInt(-1,n);
		if(b[1]!=-1)for(int i=2;i<=n;++i)b[i]=ans.readInt(1,n);
		if(a[1]==0)quitf(_wa,"Wrong Answer on test case %d.",t);
		if(a[1]==-1&&b[1]!=-1)quitf(_wa,"Wrong Answer on test case %d.",t);
		if(a[1]!=-1){
			for(int i=1;i<n;++i)if(!vis[a[i]^a[i+1]])quitf(_wa,"Wrong Answer on test case %d.",t);
			for(int i=1;i<=n;++i)u[i]=0;
			for(int i=1;i<=n;++i)u[a[i]]=1;
			for(int i=1;i<=n;++i)if(!u[i])quitf(_wa,"Wrong Answer on test case %d.",t);
		}
	}
	quitf(_ok,"Accepted");
    return 0;
}