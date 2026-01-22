#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=2e5+9;

int a[N],n;
ll s[N],ans[N];

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];

		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];

		for(int i=n,j=n;i>=1;i--){
			int k=lower_bound(s,s+n+1,s[i]-2*a[i])-s-1;
			if(!~k) continue ;
			for(j=min(j,i);j>=i-k;j--) ans[j]=s[i]-s[i-j];
		}

		for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;

		for(int i=1;i<=n;i++) ans[i]=s[i]=a[i]=0;
	}

	return 0;
}