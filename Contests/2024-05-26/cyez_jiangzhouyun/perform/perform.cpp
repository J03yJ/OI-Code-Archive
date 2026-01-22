#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
ifstream fin("perform.in");
ofstream fout("perform.out");
#define cin fin
#define cout fout
const int p=1e9+7;
int qpow(int x,int y){
	int m=1;
	while(y){
		if(y&1) m=m*x%p;
		x=x*x%p;
		y>>=1;
	}
	return m;
}
const int N=1e6+9;
int a[N],nxt[N],ans[N];
signed main(){
	int n;
	cin>>n;
	int m;
	cin>>m;
	for(int i=1;i<=m;i++) cin>>a[i];
	nxt[1]=0;
	for(int i=2,j=0;i<=m;i++){
		while(j&&a[j+1]!=a[i]) j=nxt[j];
		if(a[j+1]==a[i]) j++;
		nxt[i]=j;
	}
	for(int i=1;i<=m;i++){
		ans[i]=(ans[nxt[i]]+qpow(n,i))%p;
		cout<<ans[i]<<endl;
	}
	return 0;
}
