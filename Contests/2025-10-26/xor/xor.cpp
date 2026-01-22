#include<bits/stdc++.h>

using namespace std;

ifstream fin("xor.in");
ofstream fout("xor.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e5+9;

int a[N],c[32],f[1<<16],n;

inline void Init(){
	for(int sta=0;sta<(1<<16);sta++){
		
	}
}
inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],c[a[i]]++;
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}