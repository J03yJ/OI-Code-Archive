#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;
const int S=1e3+9;

int a[N],b[N],n,q;

int blk[N],L[N],R[N],c[N],cnt[S][10],hcnt[S],tag[S],B;
inline void Push(int x,int k){tag[x]+=k;}
inline void Build(int x){
	for(int i=0;i<=2;i++) cnt[x][i]=0;
	for(int i=L[x];i<=R[x];i++) cnt[x][c[i]]++;
}
inline void PushDown(int x){
	for(int i=L[x];i<=R[x];i++) c[i]+=tag[x];
	tag[x]=0;
}
inline void Stamp(){for(int x=1;x<=blk[n];x++) hcnt[x]+=cnt[x][2-tag[x]];}
inline void Init(){
	B=sqrt(n);
	for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
	for(int i=1;i<=n;i++) R[blk[i]]=i;
	for(int i=n;i>=1;i--) L[blk[i]]=i;
	for(int i=1;i<=blk[n];i++) cnt[i][0]=R[i]-L[i]+1;
}
inline void BModify(int l,int r,int k){
	PushDown(blk[l]);
	for(int i=l;i<=r;i++) c[i]+=k;
	Build(blk[l]);
}
inline void Modify(int l,int r,int k){
	if(l==r) return BModify(l,r,k);
	BModify(l,R[blk[l]],k),BModify(L[blk[r]],r,k);
	for(int i=blk[l]+1;i<blk[r];i++) Push(i,k);
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];

	return 0;
}