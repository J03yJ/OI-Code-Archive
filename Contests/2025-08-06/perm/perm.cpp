#include<bits/stdc++.h>

using namespace std;

ifstream fin("perm.in");
ofstream fout("perm.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e6+9;

int a[N],b[N],t[N],n;

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];

	iota(t+1,t+n+1,1);
	sort(t+1,t+n+1,[](int i,int j){return a[i]!=a[j]?a[i]<a[j]:b[i]>b[j];});

	ll ans=0,p=0,q=0,r=0;
	for(int i=1;i<=n;i++){
		if(a[t[i]]!=a[t[i-1]]) p=q=r=0;
		ans+=p*b[t[i]]*b[t[i]];
		ans+=q*b[t[i]];
		ans+=r;
		p+=1;
		q+=-2*b[t[i]]+1;
		r+=1ll*b[t[i]]*(b[t[i]]-1);
	}
	
	cout<<ans<<endl;

	return 0;
}