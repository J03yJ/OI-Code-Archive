#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e6+9;
const int B=2e1;
const int S=(1<<B)+9;

int a[N],b[N],c[S],n;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]^=a[i-1];

	for(int i=1;i<=n;i++) c[a[i]=~a[i]&(1<<B)-1]++;
	for(int i=0;i<B;i++){
		for(int j=0;j<(1<<B);j++){
			if(~j>>i&1) c[j]+=c[j|(1<<i)];
		}
	}

	memset(b,0x3f,sizeof b);
	for(int i=0;i<(1<<B);i++){
		if((i&a[n])==i) b[c[i]]=min(b[c[i]],~i&(1<<B)-1);
	}

	for(int i=n;i>=1;i--) b[i]=min(b[i+1],b[i]);
	for(int i=1;i<=n;i++) cout<<b[i]<<' ';cout<<endl;

	return 0;
}