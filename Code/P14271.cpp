#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;
const ll inf=1e17;

struct Node{
	int l,r;
	array<ll,2> tag;
}tr[N<<2];

inline void Push(int x,array<ll,2> t){tr[x].tag=t;}
inline void PushDown(int x){if(tr[x].tag[0]) Push(x<<1,tr[x].tag),Push(x<<1|1,tr[x].tag),tr[x].tag={0,0};}
inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(tr[x].l==tr[x].r) return ;
	int mid=tr[x].l+tr[x].r>>1;	
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
}
inline void Assign(int x,int l,int r,array<ll,2> k){
	if(l<=tr[x].l&&tr[x].r<=r) return Push(x,k);
	int mid=tr[x].l+tr[x].r>>1;
	PushDown(x);
	if(l<=mid) Assign(x<<1,l,r,k);
	if(r>mid) Assign(x<<1|1,l,r,k);
}
inline array<ll,2> Query(int x,int pos){
	if(tr[x].l==tr[x].r) return tr[x].tag;
	int mid=tr[x].l+tr[x].r>>1;
	PushDown(x);
	if(pos<=mid) return Query(x<<1,pos);
	else return Query(x<<1|1,pos);
}

int l[N],r[N],len[N],ans[N],L[N],R[N],blk[N],n,q,B;
int op[N],ql[N],qr[N],qk[N];
ll tsl[N],tsr[N],qt[N];

inline void Work(vector<array<ll,2>> &m,vector<array<ll,2>> &q){
	if(!q.size()) return ;
	sort(q.begin(),q.end());
	int sum=0,i=0,j=0;
	while(i<q.size()){
		while(j<m.size()&&m[j][0]<=q[i][0]){
			sum+=m[j++][1];
		}
		ans[q[i++][1]]+=sum;
	}
	q.clear();
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>l[i]>>r[i],len[i]=r[i]-l[i];
	for(int i=1;i<=q;i++) cin>>op[i]>>ql[i]>>qr[i]>>qk[i];

	Build(1,1,n);
	for(int i=1;i<=n;i++) tsl[i]=l[i],tsr[i]=r[i];
	for(int i=1;i<=q;i++){
		if(op[i]==3) continue ;
		int j=qk[i];
		auto tmp=Query(1,j);
		if(tmp[0]==1) tsl[j]=tmp[1],tsr[j]=tmp[1]+len[j];
		else if(tmp[0]==2) tsr[j]=tmp[1],tsl[j]=tmp[1]-len[j];
		if(op[i]==1) qt[i]=tsl[j],Assign(1,ql[i],qr[i],{1,tsl[j]});
		else qt[i]=tsr[j],Assign(1,ql[i],qr[i],{2,tsr[j]});
	}

	B=ceil(sqrt(n)*0.375);
	for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
	for(int i=1;i<=n;i++) R[blk[i]]=i;
	for(int i=n;i>=1;i--) L[blk[i]]=i;

	for(int i=1;i<=n;i++) tsl[i]=l[i],tsr[i]=r[i];
	for(int i=1;i<=blk[n];i++){
		ll tag=0,o=0;
		vector<array<ll,2>> mq,lq,rq;
		vector<array<ll,2>> mm(R[i]-L[i]+1<<1),lm(R[i]-L[i]+1<<1),rm(R[i]-L[i]+1<<1);
		auto Build=[&](){
			for(int j=L[i];j<=R[i];j++){
				mm[j-L[i]<<1]={inf+tsl[j],1},mm[j-L[i]<<1|1]={inf+tsr[j],-1};
				lm[j-L[i]<<1]={inf+0,1},lm[j-L[i]<<1|1]={inf+len[j],-1};
				rm[j-L[i]<<1]={inf-len[j],1},rm[j-L[i]<<1|1]={inf,-1};
			}
			sort(mm.begin(),mm.end());
			sort(lm.begin(),lm.end());
			sort(rm.begin(),rm.end());
		};
		auto Rebuild=[&](){
			for(int j=L[i];j<=R[i];j++){
				mm[j-L[i]<<1]={inf+tsl[j],1},mm[j-L[i]<<1|1]={inf+tsr[j],-1};
			}
			sort(mm.begin(),mm.end());
		};
		auto Calc=[&](){
			Work(mm,mq);
			Work(lm,lq);
			Work(rm,rq);
		};
		auto PushDown=[&](){
			if(!o) return ;
			for(int j=L[i];j<=R[i];j++){
				if(o==1) tsl[j]=tag,tsr[j]=tag+len[j];
				else tsr[j]=tag,tsl[j]=tag-len[j];
			}
			tag=o=0;
		};
		Build();
		for(int t=1;t<=q;t++){
			if(op[t]==3){
				if(ql[t]<=L[i]&&R[i]<=qr[t]){
					if(!o) mq.push_back({inf+qk[t],t});
					else if(o==1) lq.push_back({inf+qk[t]-tag,t});
					else if(o==2) rq.push_back({inf+qk[t]-tag,t});
				}else{
					int l=max(ql[t],L[i]),r=min(R[i],qr[t]);
					if(l<=r){
						for(int j=l;j<=r;j++){
							ll l=tsl[j],r=tsr[j];
							if(o==1) l=tag,r=tag+len[j];
							if(o==2) r=tag,l=tag-len[j];
							if(l<=qk[t]&&qk[t]<r) ans[t]++;
						}
					}
				}
			}else{
				if(ql[t]<=L[i]&&R[i]<=qr[t]) tag=qt[t],o=op[t];
				else{
					int l=max(ql[t],L[i]),r=min(R[i],qr[t]);
					if(l<=r){
						Calc();
						PushDown();
						for(int j=l;j<=r;j++){
							if(op[t]==1) tsl[j]=qt[t],tsr[j]=qt[t]+len[j];
							else tsr[j]=qt[t],tsl[j]=qt[t]-len[j];
						}
						Rebuild();
					}
				}
			}
		}
		Calc();
	}

	for(int i=1;i<=q;i++) if(op[i]==3) cout<<ans[i]<<endl;

	return 0;
}