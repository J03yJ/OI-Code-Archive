#include<bits/stdc++.h>

using namespace std;

ifstream fin("instrument.in");
ifstream fans("instrument.out");

const int N=5e5+9;
int a[N],b[N],n,m,mod;

signed main(){
	fin>>n;
	for(int i=1;i<=n;i++) fin>>a[i]>>b[i];
	mod=n<<1;

	fans>>m;
	for(int i=1,p,s,t;i<=m;i++){
		fans>>p>>s>>t;
		p++;
		if(a[p]==s) a[p]=t;
		else if(b[p]==s) b[p]=t;
		else cerr<<"Wrong Operation."<<endl;
	}

	int c=(a[1]+b[1])%mod;
	for(int i=1;i<=n;i++){
		if((a[i]+b[i])%mod!=c){
			cerr<<"Wrong Answer."<<endl;
			return 0;
		}
	}

	cerr<<"OK Answer."<<endl;

	return 0;
}