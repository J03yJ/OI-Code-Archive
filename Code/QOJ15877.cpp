#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e6+9;

int f[N<<1],n,q;
char s[N],t[N],o[N<<1];

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>s[i];

	while(q--){
		int k;
		cin>>k;
		for(int i=1;i<=n;i++) t[i]='#';
		for(int i=max(1,k-n);i<=min(n,k-1);i++) t[i]=s[k-i];
		for(int i=1;i<=2*n;i++) o[i]=i&1?s[i+1>>1]:t[i+1>>1];
		
		ll ans=0;
		for(int i=1,l=0,r=-1;i<k;i++){
			int k=i>r?0:min(f[l+r-i-1],r-i);
			while(i-k>=1&&i+k+1<=2*n&&o[i-k]==o[i+k+1]) k++;
			f[i]=k--;
			if(i+k+1>r) l=i-k,r=i+k+1;
			ans+=f[i]+(i&1)>>1;
		}

		cout<<ans<<endl;
	}

	return 0;
}