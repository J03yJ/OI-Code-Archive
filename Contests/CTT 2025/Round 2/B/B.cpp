#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=3e5+9;
const int inf=1e9+7;

int id[N<<1],typ[N<<1],l[N],r[N],w[N],n,k;

struct Node{
	int l,r;
	int tag,du,dudu;
	array<int,2> can,use,lim;
	ll su,sc;
}tr[N<<3];

inline void PushUp(int x){
	tr[x].lim=min(tr[x<<1].lim,tr[x<<1|1].lim);
	tr[x].can=max(tr[x<<1].can,tr[x<<1|1].can);
	tr[x].use=min(tr[x<<1].use,tr[x<<1|1].use);
	tr[x].du=min(tr[x<<1].du,tr[x<<1|1].du);
	tr[x].su=tr[x<<1].su+tr[x<<1|1].su;
	tr[x].sc=tr[x<<1].sc+tr[x<<1|1].sc;
}
inline void PushAdd(int x,int k){tr[x].lim[0]+=k,tr[x].tag+=k;}
inline void PushDu(int x,int du){tr[x].du+=du,tr[x].dudu+=du;}
inline void PushDown(int x){
	if(tr[x].tag) PushAdd(x<<1,tr[x].tag),PushAdd(x<<1|1,tr[x].tag),tr[x].tag=0;
	if(tr[x].dudu) PushDu(x<<1,tr[x].dudu),PushDu(x<<1|1,tr[x].dudu),tr[x].dudu=0;
}

inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(tr[x].l==tr[x].r) return tr[x].can[1]=-l,tr[x].use[1]=l,tr[x].use[0]=inf,tr[x].lim[1]=-l,void();
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void AddLim(int x,int l,int r,int k){
	if(l<=tr[x].l&&tr[x].r<=r) return PushAdd(x,k);
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) AddLim(x<<1,l,r,k);
	if(r>mid) AddLim(x<<1|1,l,r,k);
	PushUp(x);
}
inline void DuDuDu(int x,int l,int r,int k){
	if(l<=tr[x].l&&tr[x].r<=r) return PushDu(x,k);
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) DuDuDu(x<<1,l,r,k);
	if(r>mid) DuDuDu(x<<1|1,l,r,k);
	PushUp(x);
}
inline void SetCan(int x,int pos,int k){
	if(tr[x].l==tr[x].r) return tr[x].can[0]=k,void();
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) SetCan(x<<1,pos,k);
	else SetCan(x<<1|1,pos,k);
	PushUp(x);
}
inline void SetUse(int x,int pos,int k){
	if(tr[x].l==tr[x].r) return tr[x].use[0]=k,tr[x].su=k<inf?k:0,void();
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) SetUse(x<<1,pos,k);
	else SetUse(x<<1|1,pos,k);
	PushUp(x);
}
inline void SetCon(int x,int pos,int k){
	if(tr[x].l==tr[x].r) return tr[x].sc=k,void();
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) SetCon(x<<1,pos,k);
	else SetCon(x<<1|1,pos,k);
	PushUp(x);
}
inline array<int,2> GetLim(int x,int l,int r){
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].lim;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return GetLim(x<<1,l,r);
	else if(l>mid) return GetLim(x<<1|1,l,r);
	else return min(GetLim(x<<1,l,r),GetLim(x<<1|1,l,r));
}
inline array<int,2> MaxCan(int x,int l,int r){
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].can;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return MaxCan(x<<1,l,r);
	else if(l>mid) return MaxCan(x<<1|1,l,r);
	else return max(MaxCan(x<<1,l,r),MaxCan(x<<1|1,l,r));
}
inline array<int,2> MinUse(int x,int l,int r){
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].use;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return MinUse(x<<1,l,r);
	else if(l>mid) return MinUse(x<<1|1,l,r);
	else return min(MinUse(x<<1,l,r),MinUse(x<<1|1,l,r));
}
inline ll SumUse(int x,int l,int r){
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].su;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return SumUse(x<<1,l,r);
	else if(l>mid) return SumUse(x<<1|1,l,r);
	else return SumUse(x<<1,l,r)+SumUse(x<<1|1,l,r);
}
inline ll SumCon(int x,int l,int r){
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].sc;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return SumCon(x<<1,l,r);
	else if(l>mid) return SumCon(x<<1|1,l,r);
	else return SumCon(x<<1,l,r)+SumCon(x<<1|1,l,r);
}
inline int GetDu(int x,int pos){
	if(tr[x].l==tr[x].r) return tr[x].du;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) return GetDu(x<<1,pos);
	else return GetDu(x<<1|1,pos);
}
inline int Gt0(int x){
	if(tr[x].l==tr[x].r) return tr[x].l-(tr[x].lim[0]<=0);
	PushDown(x);
	if(tr[x<<1].lim[0]<=0) return Gt0(x<<1);
	else return Gt0(x<<1|1);
}
inline int Geq0(int x){
	if(tr[x].l==tr[x].r) return tr[x].l-(tr[x].lim[0]<0);
	PushDown(x);
	if(tr[x<<1].lim[0]<0) return Geq0(x<<1);
	else return Geq0(x<<1|1);
}
inline int UdUdUd(int x,int k){
	if(tr[x].l==tr[x].r) return tr[x].l-(tr[x].du>k);
	PushDown(x);
	if(tr[x<<1].du>k) return UdUdUd(x<<1,k);
	else return UdUdUd(x<<1|1,k); 
}
inline bool IsUse(int pos){return MinUse(1,pos,pos)[0]<inf;}

signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>l[i]>>r[i]>>w[i];
		typ[l[i]]=0,typ[r[i]]=1;
		id[l[i]]=id[r[i]]=i;
	}

	ll ans=0;
	set<int> o;
	Build(1,1,2*n);
	AddLim(1,1,2*n,k);
	for(int i=2*n;i>=1;i--){
		// if(typ[i]) continue ;
		// ll sum=0;
		// // queue<int> q;
		// // priority_queue<array<int,2>> h;
		// int c=0,maxc=0;
		// vector<int> lim(2*n+1,0);
		// vector<ll> con(2*n+1,0);
		// for(int j=i+1;j<=2*n;j++){
		// 	if(typ[j]==0) maxc=max(maxc,++c);
		// 	else if(typ[j]==1&&l[id[j]]>i) c--,sum+=w[id[j]];
		// 	lim[j]=k-maxc,con[j]=sum;
		// }
		// sum=0;
		// priority_queue<int> q;
		// vector<ll> shr(2*n+1,0);
		// for(int j=2*n;j>i;j--){
		// 	if(typ[j]==1&&l[id[j]]<i){
		// 		q.push(-w[id[j]]);
		// 		sum+=w[id[j]];
		// 	}
		// 	while(q.size()&&q.size()>lim[j]){
		// 		sum-=-q.top();
		// 		q.pop();
		// 	}
		// 	shr[j]=sum;
		// }
		// for(int j=i+1;j<=2*n;j++){
		// 	if(lim[j]<0) break ;
		// 	// shr[j]=max(shr[j],shr[j-1]);
		// 	ans=max(ans,shr[i+1]+con[j]);
		// }

		// cout<<"# "<<i<<endl;
		if(typ[i]==1){
			if(GetLim(1,i,i)[0]>0){
				cout<<" + "<<i<<endl;
				SetUse(1,i,w[id[i]]);
				AddLim(1,1,i,-1);
				o.insert(i);
			}else{
				auto t=MinUse(1,i,2*n);
				if(t[0]<w[id[i]]){
					cout<<" - "<<t[1]<<endl;
					cout<<" + "<<i<<endl;
					SetUse(1,t[1],inf);
					SetCan(1,t[1],t[0]);
					AddLim(1,1,t[1],1);
					o.erase(t[1]);
					SetUse(1,i,w[id[i]]);
					AddLim(1,1,i,-1);
					o.insert(i);
				}else SetCan(1,i,w[id[i]]);
			}
		}else{
			if(IsUse(r[id[i]])){
				SetUse(1,r[id[i]],inf);
				AddLim(1,1,r[id[i]],1);
				o.erase(r[id[i]]);
				int pos=Gt0(1);
				// cout<<" -> "<<pos<<endl;
				// cout<<" -> ";for(int i=1;i<=2*n;i++) cout<<GetLim(1,i,i)<<'/'<<SumUse(1,i,i)<<' ';cout<<endl;
				if(pos>=i){
					auto t=MaxCan(1,i,pos);
					// cout<<" -> "<<t[0]<<' '<<t[1]<<endl;
					if(t[0]>0){
						SetUse(1,-t[1],t[0]);
						SetCan(1,-t[1],0);
						AddLim(1,1,-t[1],-1);
						o.insert(-t[1]);
					}
				}
				// cout<<" -> ";for(int i=1;i<=2*n;i++) cout<<GetLim(1,i,i)<<'/'<<SumUse(1,i,i)<<' ';cout<<endl;
			}else SetCan(1,r[id[i]],0);
		}

		int pos=Geq0(1);
		cout<<i<<" : "<<pos<<' '<<typ[i]<<" ~ "<<r[id[i]]<<endl;
		if(pos>=i){
			ans=max(ans,SumCon(1,i,pos)+SumUse(1,i,pos));
		}
		// for(int i=1;i<=2*n;i++) cout<<GetLim(1,i,i)[0]<<'/'<<SumUse(1,i,i)<<'/'<<SumCon(1,i,i)<<' ';cout<<endl;
		cout<<" -> ";for(int i=1;i<=2*n;i++) cout<<GetLim(1,i,i)[0]<<' ';cout<<endl;
		cout<<" -> ";for(int i=1;i<=2*n;i++) cout<<SumUse(1,i,i)<<' ';cout<<endl;
		cout<<" -> ";for(int i=1;i<=2*n;i++) cout<<SumCon(1,i,i)<<' ';cout<<endl;
		cout<<" -> ";for(int i=1;i<=2*n;i++) cout<<GetDu(1,i)<<' ';cout<<endl;

		if(typ[i]==0){
			int pos=UdUdUd(1,GetDu(1,r[id[i]]));
			AddLim(1,i,pos,-1);
			DuDuDu(1,i,pos,1);
			SetCon(1,r[id[i]],w[id[i]]);
			int p=Geq0(1);
			cout<<" ~> "<<pos<<endl;
			if(GetLim(1,i,r[id[i]])[0]<0){
				int q=-GetLim(1,i,r[id[i]])[1];
				auto s=MinUse(1,q,2*n);
				cout<<" ~~~> "<<i<<' '<<r[id[i]]<<' '<<q<<endl;
				if(s[0]<inf){
					cout<<" - "<<s[1]<<endl;
					SetUse(1,s[1],inf);
					AddLim(1,1,s[1],1);
					o.erase(s[1]);
				}
				if(p>=i){
					auto t=MaxCan(1,i,p);
					if(t[0]>0){
						SetUse(1,-t[1],t[0]);
						SetCan(1,-t[1],0);
						AddLim(1,1,-t[1],-1);
					}
				}
			}
			int u=Geq0(1);
		}
	}

	int pos=Geq0(1);
	if(pos>=1){
		ans=max(ans,SumCon(1,1,pos)+SumUse(1,1,pos));
	}

	cout<<ans<<endl;

	return 0;
}