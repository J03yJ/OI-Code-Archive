#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;

int sa[N],rk[N<<1],lsa[N],lrk[N<<1],cnt[N],h[N],n;

inline void CalcSA(string &s){
	n=s.size(),s=" "+s;

	for(int i=1;i<=n;i++) cnt[rk[i]=s[i]]++;
	for(int i=1;i<128;i++) cnt[i]+=cnt[i-1];
	for(int i=n;i>=1;i--) sa[cnt[rk[i]]--]=i;
	for(int i=0;i<128;i++) cnt[i]=0;

	int m=0;
	for(int i=1;i<=n;i++) lrk[i]=rk[i];
	for(int i=1;i<=n;i++){
		if(lrk[sa[i]]!=lrk[sa[i-1]]) m++;
		rk[sa[i]]=m;
	}

	for(int k=1;k<=n&&m<n;k<<=1){
		int t=0;
		for(int i=n-k+1;i<=n;i++) lsa[++t]=i;
		for(int i=1;i<=n;i++) if(sa[i]>k) lsa[++t]=sa[i]-k;

		for(int i=1;i<=n;i++) cnt[rk[lsa[i]]]++;
		for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--) sa[cnt[rk[lsa[i]]]--]=lsa[i];
		for(int i=0;i<=m;i++) cnt[i]=0;

		m=0;
		for(int i=1;i<=n;i++) lrk[i]=rk[i];
		for(int i=1;i<=n;i++){
			if(lrk[sa[i]]!=lrk[sa[i-1]]||lrk[sa[i]+k]!=lrk[sa[i-1]+k]) m++;
			rk[sa[i]]=m;
		}
	}

	for(int i=1,k=0;i<=n;i++){
		if(k) k--;
		while(s[i+k]==s[sa[rk[i]-1]+k]) k++;
		h[rk[i]]=k;
	}
}

int f[N],g[N],p[N],tnc[N];
inline int F(int x){
	if(x>n) return 0;
	if(x<1) return n+1;
	if(f[x]) return f[x];
	int c=0;
	g[1]=++c;
	for(int i=2;i<=n;i++){
		if(h[i]<x) c++;
		g[i]=c;
	}
	for(int i=1;i<=c;i++) tnc[i]=0,p[i]=-n;
	for(int i=1;i<=n;i++){
		if(p[g[rk[i]]]+x<=i){
			p[g[rk[i]]]=i;
			tnc[g[rk[i]]]++;
		}
	}
	return f[x]=*max_element(tnc+1,tnc+c+1);
}
inline void Conquer(int l,int r){
	if(F(l)==F(r)){
		for(int i=l;i<=r;i++) f[i]=f[l];
		return ;
	}
	int mid=l+r>>1;
	if(mid==l) return ;
	Conquer(l,mid),Conquer(mid+1,r);
}

int solve(int k,string s){
	CalcSA(s);
	Conquer(1,k);
	int ans=n;
	for(int i=1;i<=k;i++) ans=min(ans,n-F(i)*(i-1));
	return ans;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int k;
	string s;
	cin>>k>>s;

	cout<<solve(k,s)<<endl;

	return 0;
}