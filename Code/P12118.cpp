#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=6e5+9;

int u[N],v[N],pp[N],n,q;

namespace LCT{
	struct Node{
		int fa,son[2],rev,siz,vsiz;
		array<int,2> val,dat;
	}tr[N];
	#define fa(x) tr[x].fa
	#define rev(x) tr[x].rev
	#define siz(x) tr[x].siz
	#define dat(x) tr[x].dat
	#define val(x) tr[x].val
	#define vsiz(x) tr[x].vsiz
	#define son(x,k) tr[x].son[k]

	inline bool IsRoot(int x){return son(fa(x),0)!=x&&son(fa(x),1)!=x;}
	inline void PushUp(int x){
		if(x){
			siz(x)=siz(son(x,0))+(x<=n)+siz(son(x,1))+vsiz(x);
			dat(x)=max(max(dat(son(x,0)),dat(son(x,1))),val(x));
		}
	}
	inline void PushRev(int x){if(x) rev(x)^=1,swap(son(x,0),son(x,1));}
	inline void PushDown(int x){if(rev(x)) PushRev(son(x,0)),PushRev(son(x,1)),rev(x)=0;}
	inline bool Id(int x){return son(fa(x),1)==x;}
	inline void Rotate(int x){
		int y=fa(x),z=fa(y),f=Id(x);
		if(!IsRoot(y)) son(z,Id(y))=x;
		son(y,f)=son(x,!f),fa(son(x,!f))=y,PushUp(y);
		son(x,!f)=y,fa(y)=x,PushUp(x);
		fa(x)=z;
	}
	inline void Update(int x){
		if(!IsRoot(x)) Update(fa(x));
		return PushDown(x);
	}
	inline void Splay(int x){
		Update(x);
		for(int y=fa(x);!IsRoot(x);Rotate(x),y=fa(x)){
			if(!IsRoot(y)) Rotate(Id(x)==Id(y)?y:x);
		}
	}
	inline int Access(int x){
		int p=0;
		for(;x;p=x,x=fa(x)) Splay(x),vsiz(x)+=siz(son(x,1))-siz(p),son(x,1)=p,PushUp(x);
		return p;
	}
	inline void MakeRoot(int x){PushRev(Access(x));}
	inline int FindRoot(int x){
		Access(x),Splay(x),PushDown(x);
		while(son(x,0)) PushDown(x=son(x,0));
		return Splay(x),x;
	}
	inline void Split(int x,int y){MakeRoot(x),Access(y),Splay(y);}
	inline void Link(int x,int y){MakeRoot(x),Splay(x);if(FindRoot(y)!=x) fa(x)=y,vsiz(y)+=siz(x),PushUp(y);}
	inline void Cut(int x,int y){Split(x,y);if(fa(x)==y&&!son(x,1)) fa(x)=son(y,0)=0,PushUp(y);}
	inline int Size(int x){return siz(FindRoot(x));}

	#undef fa
	#undef son
	#undef rev
	#undef val
	#undef dat
	#undef siz
	#undef vsiz
}

namespace SgT{
	struct Node{
		int l,r;
		int neg,siz,sum;
	}tr[N<<2];
	#define l(x) tr[x].l
	#define r(x) tr[x].r
	#define neg(x) tr[x].neg
	#define siz(x) tr[x].siz
	#define sum(x) tr[x].sum

	inline void PushUp(int x){sum(x)=sum(x<<1)+sum(x<<1|1);}
	inline void Push(int x){neg(x)^=1,sum(x)=-sum(x);}
	inline void PushDown(int x){if(neg(x)) Push(x<<1),Push(x<<1|1),neg(x)=0;}
	inline void Build(int x,int l,int r){
		l(x)=l,r(x)=r,neg(x)=0;
		if(l(x)==r(x)) return sum(x)=0,void();
		int mid=l(x)+r(x)>>1;
		Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
		PushUp(x);
	}
	inline void Flip(int x,int pos){
		if(l(x)==r(x)) return sum(x)=l(x)*(neg(x)?-1:1)-sum(x),void();
		int mid=l(x)+r(x)>>1;
		PushDown(x);
		if(pos<=mid) Flip(x<<1,pos);
		else Flip(x<<1|1,pos);
		PushUp(x);
	}
	inline void Neg(int x,int l,int r){
		if(l<=l(x)&&r(x)<=r) return Push(x);
		int mid=l(x)+r(x)>>1;
		PushDown(x);
		if(l<=mid) Neg(x<<1,l,r);
		if(r>mid) Neg(x<<1|1,l,r);
		PushUp(x);
	}

	#undef l
	#undef r
	#undef neg
	#undef siz
	#undef sum
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>q;

	auto Insert=[](int pos,int k)->void{
		if(~k&1) return ;
		SgT::Flip(1,pos);
		if(pos-1) SgT::Neg(1,1,pos-1);
	};
	for(int i=1;i<=n;i++) LCT::PushUp(i);
	SgT::Build(1,1,n);
	Insert(1,n);

	priority_queue<array<int,2>> heap;
	for(int i=n+1;i<=n+q;i++){
		char op;
		cin>>op;
		if(op=='a'){
			cin>>u[i]>>v[i]>>LCT::tr[i].val[0];
			LCT::tr[i].val[1]=i;
			LCT::PushUp(i);
			heap.push({LCT::tr[i].val});
			if(LCT::FindRoot(u[i])==LCT::FindRoot(v[i])){
				LCT::Split(u[i],v[i]);
				if(LCT::tr[v[i]].dat>LCT::tr[i].val){
					int j=LCT::tr[v[i]].dat[1];
					LCT::Cut(u[j],j),LCT::Cut(j,v[j]);
					LCT::Link(u[i],i),LCT::Link(i,v[i]);
					pp[j]=1;
				}else pp[i]=1;
			}else{
				Insert(LCT::Size(u[i]),-1);
				Insert(LCT::Size(v[i]),-1);
				LCT::Link(u[i],i),LCT::Link(i,v[i]);
				Insert(LCT::Size(u[i]),1);
			}
		}else if(op=='r'){
			int j=heap.top()[1];
			heap.pop();
			if(pp[j]) continue ;
			Insert(LCT::Size(u[j]),-1);
			LCT::Cut(u[j],j),LCT::Cut(j,v[j]);
			Insert(LCT::Size(v[j]),1);
			Insert(LCT::Size(u[j]),1);
			pp[j]=1;
		}else if(op=='d'){
			cout<<SgT::tr[1].sum<<endl;
			cout.flush();
		}
	}

	return 0;
}