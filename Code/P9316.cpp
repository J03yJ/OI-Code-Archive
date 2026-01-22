#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>

using namespace std;

#define endl '\n'
using ll=long long;
using ull=unsigned long long;
const int N=3e1+9;

ll f[N],ans;
int a[N],b[N],n,k;

int fa[N],vsiz[N],esiz[N];
inline void Init(){iota(fa+1,fa+n+1,1),fill(vsiz+1,vsiz+n+1,1);}
inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){
	x=Find(x),y=Find(y);
	if(x==y) return ;
	fa[y]=x;
	esiz[x]+=esiz[y];
	vsiz[x]+=vsiz[y];
}

__gnu_pbds::gp_hash_table<ull,ll> mF;
inline ull Hash(vector<int> &v,int c){
	ull ans=131+c;
	for(int x:v) ans=ans*131+x;
	return ans;
}
inline ll F(int o,vector<int> v,int c,ll tot){
	if(o>n+1) return 0;
	ull h=Hash(v,c);
	if(mF[h]) return mF[h];

	ll ans=0;
	vector<int> u;
	for(int i=0;i<v.size();i++){
		u.insert(u.end(),v.begin(),v.begin()+i);
		u.insert(u.end(),v.begin()+i+1,v.end());
		ans=max(ans,(tot/v[i]>>1)-F(o+1,u,c,tot/v[i]>>1));
		ans=max(ans,(tot/v[i]<<1>>1)-F(o+1,u,c+1,tot/v[i]<<1>>1));
		u.clear();
		for(int j=i+1;j<v.size();j++){
			u.insert(u.end(),v.begin(),v.begin()+i);
			u.insert(u.end(),v.begin()+i+1,v.begin()+j);
			u.insert(u.end(),v.begin()+j+1,v.end());
			u.insert(lower_bound(u.begin(),u.end(),v[i]+v[j]),v[i]+v[j]);
			ans=max(ans,(tot/v[i]/v[j]*(v[i]+v[j])>>1)-F(o+1,u,c,tot/v[i]/v[j]*(v[i]+v[j])>>1));
			u.clear();
		}
	}
	
	return mF[h]=ans;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>k;
	for(int i=1;i<=k;i++) cin>>a[i]>>b[i];

	Init();
	f[0]=1ll<<n+1;
	for(int i=1,p,q,x,y;i<=k;i++){
		x=esiz[Find(a[i])]-(p=vsiz[Find(a[i])]);
		y=esiz[Find(b[i])]-(q=vsiz[Find(b[i])]);
		if(Find(a[i])==Find(b[i])&&!~x) f[i]=(f[i-1]>>1)/p<<1;
		else if(!~x&&!~y) f[i]=(f[i-1]>>1)/p/q*(p+q);
		else if(!x&&!~y) f[i]=(f[i-1]>>1)/q;
		else if(!~x&&!y) f[i]=(f[i-1]>>1)/p;
		Merge(a[i],b[i]);
		esiz[Find(a[i])]++;
		if(esiz[Find(a[i])]>vsiz[Find(a[i])]) f[i]=0;
		if(~i&1) ans+=f[i-1]-f[i];
	}

	if(!f[k]){
		cout<<ans<<' '<<(1ll<<n+1)-ans<<endl;
		return 0;
	}
	
	int c=0;
	vector<int> v;
	for(int i=1;i<=n;i++){
		if(fa[i]!=i) continue ;
		if(esiz[i]<vsiz[i]) v.push_back(vsiz[i]);
		else if(esiz[i]==vsiz[i]) c++;
	}
	sort(v.begin(),v.end());
	
	if(~k+1&1) ans+=f[k]-F(k+1,v,c,f[k]);
	else ans+=F(k+1,v,c,f[k]);

	cout<<ans<<' '<<(1ll<<n+1)-ans<<endl;

	return 0;
}