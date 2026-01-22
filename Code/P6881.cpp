#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;

using ll=long long;

int a[N],prf[N],suc[N],n,q,tot;
ll ans[N];
vector<array<int,4>> opt;

struct Fenw{
	ll tr[N];
	inline void Add(int x,ll k){while(x<=tot) tr[x]+=k,x+=x&-x;}
	inline ll Ask(int x){ll ans=0;while(x) ans+=tr[x],x&=x-1;return ans;}
	inline ll Ask(int l,int r){return Ask(r)-Ask(l-1);}
}tr[3];

inline void Work1(int l,int r){
	if(l==r) return ;
	int mid=l+r>>1;
	Work1(l,mid),Work1(mid+1,r);
	int i=mid+1,j=l;
	vector<array<int,4>> tmp;
	tmp.reserve(r-l+1);
	while(i<=r){
		while(j<=mid&&opt[j][1]+opt[j][2]>=opt[i][1]+opt[i][2]){
			if(!opt[j][0]){
				ll t=opt[j][1]+opt[j][2]+1;
				tr[0].Add(opt[j][1],opt[j][3]*(t*t+t));
				tr[1].Add(opt[j][1],opt[j][3]*-(2*t+1));
				tr[2].Add(opt[j][1],opt[j][3]);
			}
			tmp.push_back(opt[j]);
			j++;
		}
		if(opt[i][0]){
			ll t=opt[i][1]+opt[i][2];
			ans[opt[i][0]]+=opt[i][3]*tr[0].Ask(opt[i][1]);
			ans[opt[i][0]]+=opt[i][3]*tr[1].Ask(opt[i][1])*t;
			ans[opt[i][0]]+=opt[i][3]*tr[2].Ask(opt[i][1])*t*t;
		}
		tmp.push_back(opt[i]);
		i++;
	}
	for(int k=j;k<=mid;k++) tmp.push_back(opt[k]);
	while(--j>=l){
		if(opt[j][0]==0){
			ll t=opt[j][1]+opt[j][2]+1;
			tr[0].Add(opt[j][1],-opt[j][3]*(t*t+t));
			tr[1].Add(opt[j][1],-opt[j][3]*-(2*t+1));
			tr[2].Add(opt[j][1],-opt[j][3]);
		}
	}
	for(int k=l;k<=r;k++) opt[k]=tmp[k-l];
}
inline void Work2(int l,int r){
	if(l==r) return ;
	int mid=l+r>>1;
	Work2(l,mid),Work2(mid+1,r);
	int i=mid+1,j=l;
	vector<array<int,4>> tmp;
	while(i<=r){
		while(j<=mid&&opt[j][2]>=opt[i][2]){
			if(!opt[j][0]){
				ll t=opt[j][2]+1;
				tr[0].Add(opt[j][1],opt[j][3]*(t*t+t));
				tr[1].Add(opt[j][1],opt[j][3]*-(2*t+1));
				tr[2].Add(opt[j][1],opt[j][3]);
			}
			tmp.push_back(opt[j]);
			j++;
		}
		if(opt[i][0]){
			ll t=opt[i][2];
			ans[opt[i][0]]+=opt[i][3]*tr[0].Ask(opt[i][1]+1,tot);
			ans[opt[i][0]]+=opt[i][3]*tr[1].Ask(opt[i][1]+1,tot)*t;
			ans[opt[i][0]]+=opt[i][3]*tr[2].Ask(opt[i][1]+1,tot)*t*t;
		}
		tmp.push_back(opt[i]);
		i++;
	}
	for(int k=j;k<=mid;k++) tmp.push_back(opt[k]);
	while(--j>=l){
		if(opt[j][0]==0){
			ll t=opt[j][2]+1;
			tr[0].Add(opt[j][1],-opt[j][3]*(t*t+t));
			tr[1].Add(opt[j][1],-opt[j][3]*-(2*t+1));
			tr[2].Add(opt[j][1],-opt[j][3]);
		}
	}
	for(int k=l;k<=r;k++) opt[k]=tmp[k-l];
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=q;i++){
		int x,y,z;
		cin>>x>>y>>z;
		opt.push_back({i,y,-x,1});
		opt.push_back({i,y,-x+1,-1});
		opt.push_back({i,z+1,-x,-1});
		opt.push_back({i,z+1,-x+1,1});
	}

	vector<int> stk;
	for(int i=1;i<=n;i++){
		while(stk.size()&&a[stk.back()]<a[i]) stk.pop_back();
		prf[i]=stk.size()?stk.back():-n+1; 
		stk.push_back(i);
	}
	stk.clear();
	for(int i=n;i>=1;i--){
		while(stk.size()&&a[stk.back()]<=a[i]) stk.pop_back();
		suc[i]=stk.size()?stk.back():n+1;
		stk.push_back(i);
	}
	for(int i=1;i<=n;i++){
		opt.push_back({0,i,0,a[i]});
		opt.push_back({0,i,prf[i]-i,-a[i]});
		opt.push_back({0,suc[i],i-suc[i],-a[i]});
		opt.push_back({0,suc[i],prf[i]-suc[i],a[i]});
	}
	tot=n+1;

	sort(opt.begin(),opt.end(),[](auto oi,auto oj){return oi[0]<oj[0];});
	Work1(0,opt.size()-1);
	sort(opt.begin(),opt.end(),[](auto oi,auto oj){return oi[0]<oj[0];});
	Work2(0,opt.size()-1);

	for(int i=1;i<=q;i++) cout<<ans[i]/2<<endl;

	return 0;
}