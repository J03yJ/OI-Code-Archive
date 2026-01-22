#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=2e6+9;
int a[N],b[N],per[N];

bool cmp(int x,int y){
	if((a[x]-b[x])*(a[y]-b[y])<=0) return a[x]<=b[x];
	if(a[x]<=b[x]) return a[x]<a[y];
	return b[x]>b[y];
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		int x,y,p;
		cin>>a[1]>>x>>y>>p;
		for(int i=2;i<=n;i++) a[i]=(a[i-1]*x+y)%p+1;
		cin>>b[1]>>x>>y>>p;
		for(int i=2;i<=n;i++) b[i]=(b[i-1]*x+y)%p+1;
		
		int res=0;
		for(int i=1;i<=n;i++) per[i]=i,res+=a[i];
		
		int ans=1e18;
		sort(per+1,per+n+1,cmp);
		int t=0;
		for(int i=1;i<=n;i++) t=b[per[i]]+max(t-a[per[i]],0ll);
		ans=min(ans,t);
		cout<<ans+res<<endl;
	}
}
