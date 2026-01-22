#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=4e5+9;
const int T=7e2+9;
inline void ChMax(int &x,int y){if(y>x) x=y;}

vector<int> val;
int a[N],ql[N],qr[N],qv[N],vl[N],vr[N],n,q,m,v,h;

int cnt;
namespace Block{
	int ocr[N<<1],blk[N<<1],L[T],R[T],B;
	inline void InitBlock(){
		B=sqrt(v);
		for(int i=1;i<=v;i++) blk[i]=(i-1)/B+1;
		for(int i=1;i<=v;i++) R[blk[i]]=i;
		for(int i=v;i>=1;i--) L[blk[i]]=i;
	}
	pair<int*,int> rcll[N];
	int cl[T],cr[T],res[T],pre[N],suc[N],top;
	inline void Build(){
		for(int x=1;x<=blk[v];x++){
			cr[x]=0;
			for(int i=L[x];i<=R[x];i++){
				if(!ocr[i]) continue ;
				pre[i]=cr[x],suc[cr[x]]=i,cr[x]=i;
				if(pre[i]) ChMax(res[x],val[i]-val[pre[i]]);
				else cl[x]=i;
			}
			pre[cl[x]]=suc[cr[x]]=0;
		}
	}
	inline void Del(int i){
		cnt++;
		if(--ocr[i]) return ;
		// cout<<"Del "<<i<<endl;
		int x=blk[i];
		if(!pre[i]) cl[x]=suc[i];
		else suc[pre[i]]=suc[i];
		if(!suc[i]) cr[x]=pre[i];
		else pre[suc[i]]=pre[i];
		if(pre[i]&&suc[i]) ChMax(res[x],val[suc[i]]-val[pre[i]]);
	}
	inline void RDel(int i){
		rcll[++top]={&ocr[i],ocr[i]};
		if(--ocr[i]) return ;
		// cout<<"RDel "<<i<<endl;
		int x=blk[i];
		if(!pre[i]) rcll[++top]={&cl[x],cl[x]},cl[x]=suc[i];
		else rcll[++top]={&suc[pre[i]],suc[pre[i]]},suc[pre[i]]=suc[i];
		if(!suc[i]) rcll[++top]={&cr[x],cr[x]},cr[x]=pre[i];
		else rcll[++top]={&pre[suc[i]],pre[suc[i]]},pre[suc[i]]=pre[i];
		if(pre[i]&&suc[i]){
			rcll[++top]={&res[x],res[x]};
			ChMax(res[x],val[suc[i]]-val[pre[i]]);
		}
	}
	inline void Recall(){
		while(top){
			*rcll[top].first=rcll[top].second;
			top--;
		}
	}
	inline array<int,3> Buery(int l,int r,int nl=0,int nr=0,int ans=0){
		// if(r<cl[blk[l]]||l>cr[blk[r]]) return {0,0,0};
		// if(l<=cl[blk[l]]&&cr[blk[r]]<=r) return {cl[blk[l]],cr[blk[r]],res[blk[l]]};
		for(int i=l;i<=r;i++){
			if(!ocr[i]) continue ;
			if(nr) ChMax(ans,val[i]-val[nr]);
			else nl=i;
			nr=i;
		}
		// if(r<cl[blk[l]]||l>cr[blk[r]]) cerr<<l<<' '<<r<<" | "<<cl[blk[l]]<<' '<<cr[blk[r]]<<" | "<<nl<<' '<<nr<<' '<<ans<<endl;
		return {nl,nr,ans};
	}
	inline array<int,3> Query(int l,int r){
		if(blk[l]==blk[r]) return Buery(l,r);
		array<int,3> tmp=Buery(l,R[blk[l]]);
		int nl=tmp[0],nr=tmp[1],ans=tmp[2];
		// cout<<"$ "<<nl<<' '<<nr<<' '<<ans<<endl;
		for(int i=blk[l]+1;i<blk[r];i++){
			if(!cl[i]) continue ;
			if(nr) ChMax(ans,val[cl[i]]-val[nr]);
			else nl=cl[i];
			ChMax(ans,res[i]);
			nr=cr[i];
		}
		// cout<<"$ "<<nl<<' '<<nr<<' '<<ans<<endl;
		return Buery(L[blk[r]],r,nl,nr,ans);
	}
	inline void Clear(){
		for(int i=0;i<=v;i++) pre[i]=suc[i]=ocr[i]=0;
		for(int i=0;i<=blk[v];i++) cl[i]=cr[i]=res[i]=0;
	}
}
namespace MoAlgo{
	int blk[N<<1],L[T],R[T],B;
	inline void Init(){
		B=sqrt(q);
		for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
		for(int i=1;i<=n;i++) R[blk[i]]=i;
		for(int i=n;i>=1;i--) L[blk[i]]=i;
	}
	int ans[N];
	vector<int> qry[T];
	inline void MoAlgo(){
		Init();
		Block::InitBlock();
		for(int i=1;i<=q;i++) qry[blk[ql[i]]].push_back(i);
		for(int i=1;i<=blk[n];i++){
			// cerr<<i<<endl;
			sort(qry[i].begin(),qry[i].end(),[](int x,int y){return qr[x]>qr[y];});
			int l=L[i],r=n;
			for(int j=l;j<=r;j++) Block::ocr[a[j]]++,Block::ocr[a[j]+h]++;
			Block::Build();
			vector<array<int,2>> p;
			for(int j=L[i];j<=R[i];j++) p.push_back({a[j],j}),p.push_back({a[j]+h,j});
			sort(p.begin(),p.end());
			for(int j:qry[i]){
				if(blk[ql[j]]==blk[qr[j]]){
					int nl=0,nr=0;
					for(auto t:p){
						if(t[1]<ql[j]||t[1]>qr[j]) continue ;
						if(t[0]<vl[j]||t[0]>vr[j]) continue ;
						if(nr) ChMax(ans[j],val[t[0]]-val[nr]);
						else nl=t[0];
						nr=t[0];
					}
					if(nl) ChMax(ans[j],val[nl]-qv[j]);
					if(nr) ChMax(ans[j],qv[j]+m-val[nr]);
					continue ;
				}
				while(r>qr[j]) Block::Del(a[r]),Block::Del(a[r]+h),r--;
				while(l<ql[j]) Block::RDel(a[l]),Block::RDel(a[l]+h),l++;
				auto tmp=Block::Query(vl[j],vr[j]);
				int nl=tmp[0],nr=tmp[1];
				ans[j]=tmp[2];
				if(nl) ChMax(ans[j],val[nl]-qv[j]);
				if(nr) ChMax(ans[j],qv[j]+m-val[nr]);
				// cout<<i<<' '<<j<<" | "<<ql[j]<<' '<<qr[j]<<' '<<l<<' '<<r<<' '<<vl[j]<<' '<<vr[j]<<" | "<<nl<<' '<<nr<<' '<<ans[j]<<endl;
				// for(int p=1;p<=v;p++) cout<<Block::ocr[p]<<'/'<<p<<'/'<<val[p]<<' ';cout<<endl;
				// for(int p=1;p<=v;p++) cout<<p<<'/'<<Block::pre[p]<<'/'<<Block::suc[p]<<' ';cout<<endl;
				// for(int p=1;p<=Block::blk[v];p++) cout<<Block::cl[p]<<'/'<<Block::cr[p]<<'/'<<Block::res[p]<<' ';cout<<endl;
				Block::Recall();
				l=L[i];
			}
			Block::Clear();
		}
	}
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>q>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i]>>qv[i];

	val.push_back({-1});
	for(int i=1;i<=n;i++) val.push_back(a[i]),val.push_back(a[i]+m);
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	v=val.size()-1,h=v>>1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(val.begin(),val.end(),a[i])-val.begin();
	for(int i=1;i<=q;i++){
		vl[i]=lower_bound(val.begin(),val.end(),qv[i])-val.begin();
		vr[i]=upper_bound(val.begin(),val.end(),qv[i]+m)-val.begin()-1;
	}
	// for(int x:val) cout<<x<<' ';cout<<endl;

	MoAlgo::MoAlgo();

	for(int i=1;i<=q;i++) cout<<m-MoAlgo::ans[i]<<endl;

	return 0;
}