#include<bits/stdc++.h>

using namespace std;

ifstream fin("dream.in");
ofstream fout("dream.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e6+9;

int n;
ll a[N],s[N],x;

signed main(){
	cin>>n>>x;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) a[i]-=i,s[i]=s[i-1]+a[i];

	int ans=0;
	for(int i=1;i<=n;i++){
		int j=lower_bound(a+1,a+n+1,-i)-a;
		auto W=[&](int k){
			if(i>=j) return (s[k]-s[i-1])-ll(-i)*(k-i+1);
			else if(k<j) return ll(-i)*(k-i+1)-(s[k]-s[i-1]);
			else return (s[k]-s[j-1])-ll(-i)*(k-j+1)+ll(-i)*(j-i)-(s[j-1]-s[i-1]);
		};
		int l=i-1,r=n+1;
		while(l+1<r){
			int mid=l+r>>1;
			if(W(mid)<=x) l=mid;
			else r=mid;
		}
		ans=max(ans,l-i+1);
	}

	cout<<ans<<endl;

	return 0;
}