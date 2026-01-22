#include<bits/stdc++.h>

using namespace std;

ifstream fin("wave.in");
ofstream fout("wave.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=5e5+9;
const int W=1e4+9;
const int SW=1e2+9;

int id,q,w,B;

struct Block1{
	int blk[W],L[W],R[W],B,lim;
	int bpre[SW],pre[W];
	inline void Init(int _lim){
		lim=_lim;
		B=ceil(sqrt(lim+1));
		for(int i=0;i<=lim;i++) blk[i]=i/B;
		for(int i=0;i<=lim;i++) R[blk[i]]=i;
		for(int i=lim;i>=0;i--) L[blk[i]]=i;
	}
	inline void Insert(int pos,int k){
		for(int i=pos;i<=R[blk[pos]];i++) pre[i]+=k;
		for(int i=blk[pos];i<=blk[lim];i++) bpre[i]+=k;
	}
	inline int Query(int pos){
		if(pos<0) return 0;
		return (blk[pos]?bpre[blk[pos]-1]:0)+pre[pos];
	}
	inline int Query(int l,int r){return Query(r)-Query(l-1);}
}bk[SW];

struct Block2{
	int blk[W],L[W],R[W],B,lim;
	int bsum[SW],val[W];
	inline void Init(int _lim){
		lim=_lim;
		B=ceil(sqrt(lim+1));
		for(int i=0;i<=lim;i++) blk[i]=i/B;
		for(int i=0;i<=lim;i++) R[blk[i]]=i;
		for(int i=lim;i>=0;i--) L[blk[i]]=i;
	}
	inline void Insert(int pos,int k){bsum[blk[pos]]+=k,val[pos]+=k;}
	inline int Query(int pos){
		if(pos<0) return 0;
		int sum=0;
		for(int i=0;i<blk[pos];i++) sum+=bsum[i];
		for(int i=L[blk[pos]];i<=pos;i++) sum+=val[i];
		return sum;
	}
	inline int Query(int l,int r){return Query(r)-Query(l-1);}
}bx[SW];

signed main(){
	cin>>id>>q>>w;
	B=ceil(sqrt(w));

	int lst=0;
	for(int i=0;i<=B;i++) bx[i].Init(w),bk[i].Init(w);
	while(q--){
		int op;
		cin>>op;
		if(op==1){
			int k,b;
			cin>>k>>b;
			k^=lst,b^=lst;
			if(k<=B) bk[k].Insert(b,1);
			else for(int x=0;x<=B;x++) if(k*x+b<=w) bx[x].Insert(k*x+b,1);
		}else{
			int t,x,y,ans=0;
			cin>>t>>x>>y;
			x^=lst,y^=lst;
			if(x<=B) ans=bx[x].Query(y-t,y);
			for(int k=0;k<=B;k++) ans+=bk[k].Query(y-t-k*x,y-k*x);
			cout<<ans<<endl;
			lst=ans;
		}
	}

	return 0;
}