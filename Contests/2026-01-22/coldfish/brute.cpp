#include<bits/stdc++.h>

using namespace std;

ifstream fin("brute.in");
ofstream fout("brute.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e6+9;

int a[N],b[N],n;
inline bool DFS(int x,int t){
	if(x<1||x>n) return 0;
	b[x]++;
	if(b[x]>a[x]) return b[x]--,0;
	if(x==t){
		bool flag=1;
		for(int i=1;i<=n;i++) flag&=a[i]==b[i];
		if(flag) return b[x]--,1;
	}
	if(DFS(x+1,t)) return b[x]--,1;
	if(DFS(x-1,t)) return b[x]--,1;
	return b[x]--,0;
}

inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) ans+=DFS(i,j);
	}

	cout<<ans<<endl;
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}