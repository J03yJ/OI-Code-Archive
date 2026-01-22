#include<bits/stdc++.h>

using namespace std;

vector<int> solve(vector<int> &a,vector<int> &b,vector<pair<int,int>> &t){
	int n=a.size(),q=t.size();
	for(int i=0;i<n;i++){
		a[i]=min(i+a[i],n-1);
		b[i]=min(i+b[i],n-1);
	}

	vector<int> lg(n+1,0);
	vector<vector<int>> ap(n,vector<int>(20,0));
	auto CheckA=[&](int i,int j){return a[i]<a[j]?j:i;};
	auto MaxAPos=[&](int l,int r){
		int k=lg[r-l+1];
		return CheckA(ap[l][k],ap[r-(1<<k)+1][k]);
	};
	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(int i=0;i<n;i++) ap[i][0]=i;
	for(int k=1;k<=lg[n];k++){
		for(int i=0;i<n-(1<<k)+1;i++){
			ap[i][k]=CheckA(ap[i][k-1],ap[i+(1<<k-1)][k-1]);
		}
	}
	
	vector<vector<int>> bp(n,vector<int>(20,0));
	auto CheckB=[&](int i,int j){return b[i]<b[j]?j:i;};
	auto MaxBPos=[&](int l,int r){
		int k=lg[r-l+1];
		return CheckB(bp[l][k],bp[r-(1<<k)+1][k]);
	};
	for(int i=0;i<n;i++) bp[i][0]=i;
	for(int k=1;k<=lg[n];k++){
		for(int i=0;i<n-(1<<k)+1;i++){
			bp[i][k]=CheckB(bp[i][k-1],bp[i+(1<<k-1)][k-1]);
		}
	}

	vector<vector<array<int,2>>> f(n,vector<array<int,2>>(20,{0,0}));
	auto Far=[&](int l,int r,int k,int t){
		int x=MaxAPos(l,r),y=MaxBPos(l,r),z=r;
		return max(max(f[x][k][t],f[y][k][t]),f[z][k][t]);
	};
	auto Query=[&](int l,int r){
		if(l==r) return 0;
		int cur=l,bur=-1,ans=0;
		auto Upd=[&](int k){
			array<int,2> res={-1,-1};
			res[0]=max(res[0],Far(l,cur,k,0));
			if(~bur) res[0]=max(res[0],Far(l,bur,k,1));
			res[1]=max(res[1],Far(l,cur,k,1));
			if(~bur) res[1]=max(res[1],Far(l,b[MaxBPos(l,bur)],k,0));
			return res;
		};
		for(int k=lg[n];~k;k--){
			auto tmp=Upd(k);
			if(tmp[1]<r) ans+=(1<<k),bur=tmp[0],cur=tmp[1];
		}
		return ans+1;
	};
	for(int i=0;i<n;i++) f[i][0]={i,a[i]};
	for(int k=1;k<=lg[n];k++){
		for(int i=0;i<n;i++){
			f[i][k][0]=max(f[i][k][0],Far(i,f[i][k-1][1],k-1,0));
			f[i][k][0]=max(f[i][k][0],Far(i,f[i][k-1][0],k-1,1));
			f[i][k][1]=max(f[i][k][1],Far(i,f[i][k-1][1],k-1,1));
			f[i][k][1]=max(f[i][k][1],Far(i,b[MaxBPos(i,f[i][k-1][0])],k-1,0));
		}
	}

	vector<int> ans(q,0);
	for(int i=0;i<q;i++){
		int l=t[i].first,r=t[i].second;
		ans[i]=Query(l,r);
	}

	return ans;
}

signed main(){
	int n;
	cin>>n;
	vector<int> a(n),b(n);
	for(int &x:a) cin>>x;
	for(int &x:b) cin>>x;
	int q;
	cin>>q;
	vector<pair<int,int>> t(q);
	for(int i=0;i<q;i++) cin>>t[i].first>>t[i].second;

	auto ans=solve(a,b,t);
	for(int x:ans) cout<<x<<endl;

	return 0;
}