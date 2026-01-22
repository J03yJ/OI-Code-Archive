#include<bits/stdc++.h>

using namespace std;

const int N=5e3+9;

#define endl '\n'
int p[N],q[N],n;

inline int F(int l,int r){
	if(l==r) return 0;
	int O=0,T=n+1;
	for(int i=l;i<=r;i++) p[q[i]]=i;
	auto Prev=[&](int x){return x!=l?x-1:r;};
	auto Next=[&](int x){return x!=r?x+1:l;};
	auto W=[&](int x){return x<=p[r]?0:r-x+1;};
	for(int i=l,c=0;i<r;i++){
		c++;
		if(q[Prev(p[i])]<=i) c--;
		if(q[Next(p[i])]<=i) c--;
		O=max(O,W(p[i]));
		if(c<=1){
			if(O||q[l]<=i) T=min(T,O);
		}
	}
	if(T) rotate(q+l,q+r-T+1,q+r+1);
	int ans=0;
	for(int i=l,j=l-1,mx=0;i<=r;i++){
		mx=max(mx,q[i]);
		if(mx==i) ans=max(ans,F(j+1,i)),j=i;
	}
	return ans+T;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i],q[p[i]]=i;

	cout<<F(1,n)<<endl;

	return 0;
}