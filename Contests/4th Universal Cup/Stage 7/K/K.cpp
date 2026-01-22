#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=5e5+9;
const int lgN=2e1;

int a[N],lg[N],st[2][N][lgN],s[N],b[N],ts,n;
inline int Cmp(int i,int j){return i&&j?(a[i]^a[j]?(a[i]<a[j]?i:j):(i>j?i:j)):i|j;};
inline int MinPos(int c,int l,int r){
	int k=lg[r-l+1];
	return Cmp(st[c][l][k],st[c][r-(1<<k)+1][k]);
}
inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++) st[i&1][i][0]=i;
	for(int c:{0,1}){
		for(int k=1;k<=lg[n];k++){
			for(int i=1;i<=n-(1<<k)+1;i++){
				st[c][i][k]=Cmp(st[c][i][k-1],st[c][i+(1<<k-1)][k-1]);
			}
		}
	}
	
	vector<int> stk;
	for(int i=1;i<=n;i++){
		int rlim=stk.size()?b[stk.back()]-1:n;
		int p=MinPos(~i&1,i+1,rlim),lv=p?a[p]:n+1;
		if(stk.size()&&i==b[stk.back()]) lv=n+1;
		int rv=stk.size()&&a[i]==a[b[stk.back()]]?a[stk.back()]:n+1;
		if(lv<rv){
			stk.push_back(i);
			b[i]=p;
			s[i]=0;
		}else{
			stk.pop_back();
			s[i]=1;
		}
	}

	for(int i=1;i<=n;i++) cout<<(s[i]?')':'('),b[i]=0;cout<<endl;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}