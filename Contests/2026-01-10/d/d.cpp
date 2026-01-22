#include<bits/stdc++.h>

using namespace std;

ifstream fin("d.in");
ofstream fout("d.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e5+9;

int a[N],L[N],R[N],blk[N],len[N],n,q,B;

struct Node{
	int lc,rc;
	vector<int> ip,dlt;
}tr[N<<2];

int cnt;
inline int Allc(){return ++cnt;}
inline void PushUp(int x){
	vector<int> tip,td;
	tr[x].ip.clear(),tr[x].dlt.clear();
	auto &lip=tr[tr[x].lc].ip,&ld=tr[tr[x].lc].dlt;
	auto &rip=tr[tr[x].rc].ip,&rd=tr[tr[x].rc].dlt;
	vector<int> op(lip.size());
	for(int i=0;i<op.size();i++) op[i]=lip[i]+ld[i];
	int i=0,j=0;
	while(i<op.size()&&j<rip.size()){
		if(op[i]==rip[j]){
			tip.push_back(op[i]-ld[i]);
			td.push_back(ld[i]+rd[j]);
			i++,j++;
		}else if(op[i]<rip[j]){
			tip.push_back(op[i]-ld[i]);
			td.push_back(ld[i]+rd[j-1]);
			i++;
		}else{
			tip.push_back(rip[j]-ld[i-1]);
			td.push_back(ld[i-1]+rd[j]);
			j++;
		}
	}
	while(i<op.size()){
		tip.push_back(op[i]-ld[i]);
		td.push_back(ld[i]+rd.back());
		i++;
	}
	while(j<rip.size()){
		tip.push_back(rip[j]-ld.back());
		td.push_back(rd[j]+ld.back());
		j++;
	}
	for(int i=0;i<tip.size();i++){
		while(tr[x].ip.size()&&tr[x].ip.back()>=tip[i]){
			tr[x].ip.pop_back();
			tr[x].dlt.pop_back();
		}
		tr[x].ip.push_back(tip[i]);
		tr[x].dlt.push_back(td[i]);
	}
}
inline void Build(int &x,int L,int R,int *a){
	if(!x) x=Allc();
	if(L==R){
		tr[x].ip={-1,a[L]};
		tr[x].dlt={0,1};
		return ;
	}
	int mid=L+R>>1;
	Build(tr[x].lc,L,mid,a);
	Build(tr[x].rc,mid+1,R,a);
	PushUp(x);
}
inline void Set(int x,int L,int R,int pos,int k){
	if(L==R){
		tr[x].ip={-1,k};
		tr[x].dlt={0,1};
		return ;
	}
	int mid=L+R>>1;
	if(pos<=mid) Set(tr[x].lc,L,mid,pos,k);
	else Set(tr[x].rc,mid+1,R,pos,k);
	PushUp(x);
}

int root[N];

signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];

	B=sqrt(n);
	for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
	for(int i=1;i<=n;i++) R[blk[i]]=i;
	for(int i=n;i>=1;i--) L[blk[i]]=i;

	for(int i=1;i<=blk[n];i++){
		Build(root[i],1,len[i]=R[i]-L[i]+1,a+L[i]-1);
	}
	while(q--){
		int op;
		cin>>op;
		if(op==1){
			int x,y;
			cin>>x>>y;
			Set(root[blk[x]],1,len[blk[x]],x-L[blk[x]]+1,a[x]=y);
		}else if(op==2){
			int x;
			cin>>x;
			int cur=a[x];

			for(int i=x+1;i<=R[blk[x]];i++) cur+=(a[i]<=cur);
			for(int i=blk[x]+1;i<=blk[n];i++){
				auto &ip=tr[root[i]].ip,&dlt=tr[root[i]].dlt;
				int pos=upper_bound(ip.begin(),ip.end(),cur)-ip.begin()-1;
				cur+=dlt[pos];
			}
			cout<<n-cur<<endl;
		}
	}

	return 0;
}