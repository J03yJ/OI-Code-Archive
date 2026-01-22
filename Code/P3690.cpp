#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e5+9;

struct Node{
	int fa,son[2],rev;
	int val,dat;
}tr[N];
#define fa(x) tr[x].fa
#define son(x,k) tr[x].son[k]
#define rev(x) tr[x].rev
#define val(x) tr[x].val
#define dat(x) tr[x].dat

inline bool IsRoot(int x){return son(fa(x),0)!=x&&son(fa(x),1)!=x;}
inline void PushUp(int x){dat(x)=dat(son(x,0))^val(x)^dat(son(x,1));}
inline void PushRev(int x){if(x) rev(x)^=1,swap(son(x,0),son(x,1));}
inline void PushDown(int x){if(rev(x)) PushRev(son(x,0)),PushRev(son(x,1)),rev(x)=0;}
inline bool Id(int x){return son(fa(x),1)==x;}
inline void Rotate(int x){
	int y=fa(x),z=fa(y),f=Id(x);
	if(!IsRoot(y)) son(z,Id(y))=x;
	son(y,f)=son(x,f^1),fa(son(x,f^1))=y,PushUp(y);
	son(x,f^1)=y,fa(y)=x,PushUp(x);
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
	for(;x;p=x,x=fa(x)) Splay(x),son(x,1)=p,PushUp(x);
	return p;
}
inline void MakeRoot(int x){PushRev(Access(x));}
inline int FindRoot(int x){
	Access(x),Splay(x),PushDown(x);
	while(son(x,0)) PushDown(x=son(x,0));
	return Splay(x),x;
}
inline void Split(int x,int y){MakeRoot(x),Access(y),Splay(y);}
inline void Link(int x,int y){
	MakeRoot(x),Splay(x);
	if(FindRoot(y)!=x) fa(x)=y;
}
inline void Cut(int x,int y){
	Split(x,y);
	if(fa(x)==y&&!son(x,1)) fa(x)=son(y,0)=0,PushUp(y);
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>val(i),dat(i)=val(i);

	while(q--){
		int op,x,y;
		cin>>op>>x>>y;
		if(op==0) Split(x,y),cout<<dat(y)<<endl;
		else if(op==1) Link(x,y);
		else if(op==2) Cut(x,y);
		else if(op==3) Splay(x),val(x)=y,PushUp(x);
	}

	return 0;
}