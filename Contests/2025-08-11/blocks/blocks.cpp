#include<bits/stdc++.h>

using namespace std;

ifstream fin("blocks.in");
ofstream fout("blocks.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;

int a[N],n,k;

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>k>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+n+1);
		
		ll ans=1ll*(k/2)*(k/2+1)/2+1ll*((k-1)/2)*((k-1)/2+1)/2; // sum of 0, 1, 1, 2, 2, ...
		for(int i=1;i<=n;i++){
			ans-=k-a[i]; // exclude {x,a[i],y}
			ans-=a[i]/2; // excldue {x,y,a[i]}
		}
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				if(a[i]+a[j]<=k) ans++; // include {a[i],a[j],x}
			}
		}
		for(int i=1;i<=n;i++){
			int tmp=i-1; // include {a[i],x,a[j]}
			for(int j=1,k=i-1;j<k;j++){
				while(k>j&&a[j]+a[k]>a[i]) k--;
				if(j<k&&a[j]+a[k]==a[i]) tmp--; // exclude {a[i],a[j],a[k]}
			}
			ans+=tmp;
		}

		cout<<ans<<endl;
	}

	return 0;
}