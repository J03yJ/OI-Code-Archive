#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=5e5+9;

ll su[N][2],ans[N];
char s[N],t[N];
int c[N],ddl[N],ql[N],qr[N],n,q;
vector<int> qry[N<<1];

struct Fenw{
	ll tr[N];
	inline void Add(int x,ll k){while(x<=n) tr[x]+=k,x+=x&-x;}
	inline ll Ask(int x){ll sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}
	inline ll Ask(int l,int r){return Ask(r)-Ask(l-1);}
	inline void Clear(){for(int i=1;i<=n;i++) tr[i]=0;}
}k,b;

multiset<array<int,2>> seg[2][2];
priority_queue<array<int,2>> cnd,iac;
inline void Insert(int l,int r,int lp,int rp){
	seg[lp][rp].insert({l,r});
	k.Add(l,(r-l+1+lp+rp)/2);
	b.Add(l,su[r-!rp][r-!rp&1]-su[l+!lp-1][r-!rp&1]);
	if(!lp&&!rp){
		ll f=su[r][r&1]-su[l-1][r&1],g=su[r][~r&1]-su[l-1][~r&1];
		if(g-f+1<=n) cnd.push({-(ddl[l]=g-f+1),l});
	}
}
inline void Erase(int l,int r,int lp,int rp){
	seg[lp][rp].erase({l,r});
	k.Add(l,-(r-l+1+lp+rp)/2);
	b.Add(l,-(su[r-!rp][r-!rp&1]-su[l+!lp-1][r-!rp&1]));
	ddl[l]=-1e9;
}
inline void Activate(int pos){
	int l=pos,r=pos,lp=0,rp=0;
	for(int p:{0,1}){
		auto it=seg[p][1].lower_bound({pos,0});
		if(it==seg[p][1].begin()) continue ;
		it--;
		if((*it)[1]!=pos-1) continue ;
		lp=p;
		l=(*it)[0];
		Erase((*it)[0],(*it)[1],p,1);
		break ;
	}
	for(int p:{0,1}){
		auto it=seg[1][p].upper_bound({pos,0});
		if(it==seg[1][p].end()) continue ;
		if((*it)[0]!=pos+1) continue ;
		rp=p;
		r=(*it)[1];
		Erase((*it)[0],(*it)[1],1,p);
		break ;
	}
	Insert(l,r,lp,rp);
}
inline void Update(int l){
	int r=-1,lp=1,rp=1;
	for(int p:{0,1}){
		for(int q:{0,1}){
			auto it=seg[p][q].lower_bound({l,0});
			if(it==seg[p][q].end()||(*it)[0]!=l) continue ;
			r=(*it)[1];
			break ;
		}
	}
	Erase(l,r,0,0);
	for(int p:{0,1}){
		auto it=seg[p][0].lower_bound({l,0});
		if(it==seg[p][0].begin()) continue ;
		it--;
		if((*it)[1]!=l-1) continue ;
		lp=p;
		l=(*it)[0];
		Erase((*it)[0],(*it)[1],p,0);
		break ;
	}
	for(int p:{0,1}){
		auto it=seg[0][p].upper_bound({r,0});
		if(it==seg[0][p].end()) continue ;
		if((*it)[0]!=r+1) continue ;
		rp=p;
		r=(*it)[1];
		Erase((*it)[0],(*it)[1],0,p);
		break ;
	}
	Insert(l,r,lp,rp);
}

signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int i=1;i<=n;i++) cin>>t[i];
	
	for(int i=1;i<=n;i++) c[i]=c[i-1]+(s[i]-t[i]);
	for(int i=1;i<=n;i++){
		for(int k:{0,1}) su[i][k]=su[i-1][k];
		su[i][i&1]+=c[i];
	}

	for(int i=1;i<=q;i++){
		cin>>ql[i]>>qr[i];
		if(qr[i]-ql[i]+1<3) ans[i]=-int(string(s+ql[i],s+qr[i]+1)!=string(t+ql[i],t+qr[i]+1));
		else if(c[ql[i]-1]==c[qr[i]]) qry[-c[ql[i]-1]+N].push_back(i);
		else ans[i]=-1;
	}
	
	for(int o:{0,1}){
		for(int i=1;i<=n;i++) iac.push({c[i]-1,i});
		for(int i=-n;i<=n;i++){
			while(iac.size()&&-iac.top()[0]<=i){
				int j=iac.top()[1];
				iac.pop();
				Activate(j);
			}
			while(cnd.size()&&-cnd.top()[0]<=i){
				int j=cnd.top()[1],x=-cnd.top()[0];
				cnd.pop();
				if(ddl[j]!=x) continue ;
				Update(j);
			}
			for(int j:qry[i+N]){
				ans[j]+=k.Ask(ql[j],qr[j])*i+b.Ask(ql[j],qr[j]);
			}
		}
		k.Clear();
		b.Clear();
		for(int p:{0,1}) for(int q:{0,1}) seg[p][q].clear();
		while(cnd.size()) cnd.pop();
		while(iac.size()) iac.pop();
		for(int i=1;i<=n;i++){
			c[i]=-c[i];
			for(int k:{0,1}) su[i][k]=-su[i][k];
			qry[i+N].swap(qry[-i+N]);
		}
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}