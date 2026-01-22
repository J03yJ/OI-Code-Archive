#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e5+9;

int a[N],n,k;

inline int Count(int w){
	int cnt=0;
	for(int i=1;i<=n;i++) if(a[i]<=(w>>1)) cnt++;
	if(!cnt) return 0;
	int lp=n,rp=0;
	for(int i=1;i<=n;i++){
		if(a[i]>(w>>1)) continue ;
		if(!rp) lp=rp=i;
		else{
			if(rp+1<i){
				int k=*min_element(a+rp+1,a+i);
				if(ll(max(a[i],a[rp]))+k<=w) cnt++;
			}
			rp=i;
		}
	}
	int k=2e9;
	if(lp!=1) k=min(k,*min_element(a+1,a+lp));
	if(rp!=n) k=min(k,*min_element(a+rp+1,a+n+1));
	if(ll(max(a[lp],a[rp]))+k<=w) cnt++;
	return cnt;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];

	int L=-1,R=2e9+1;
	while(L+1<R){
		int mid=ll(L)+R>>1;
		if(Count(mid)>=k) R=mid;
		else L=mid;
	}

	cout<<R<<endl;

	return 0;
}