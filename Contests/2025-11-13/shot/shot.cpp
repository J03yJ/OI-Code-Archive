#include<bits/stdc++.h>

using namespace std;

ifstream fin("shot.in");
ofstream fout("shot.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e6+9;

int a[N],n;
ll f[N],r1,r2,r3,d;

signed main(){
	cin>>n>>r1>>r2>>r3>>d;
	for(int i=1;i<=n;i++) cin>>a[i];

	auto Two=[](int i){return min(r2+r1,(a[i]+2)*r1);};
	auto One=[](int i){return a[i]*r1+r3;};
	for(int i=1;i<=n;i++){
		f[i]=f[i-1]+min(One(i),Two(i)+2*d)+(i<n)*d;
		if(i>1) f[i]=min(f[i],f[i-2]+Two(i)+Two(i-1)+3*d+(i<n)*d);
		if(i==n) f[i]=min(f[i],f[i-2]+Two(i-1)+One(i)+2*d);
	}

	cout<<f[n]<<endl;

	return 0;
}