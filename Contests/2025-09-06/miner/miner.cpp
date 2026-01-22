#include<bits/stdc++.h>

using namespace std;

ifstream fin("miner.in");
ofstream fout("miner.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e6+9;
const int B=40;

int op[N],id[N],imp[N],vis[N],ans[N],n,m,k;
array<int,2> a[N];
vector<int> xs[N];

namespace KS1{
	int f[N];
	inline void Init(){memset(f,0,sizeof f);}
	inline void Insert(int v,int w){for(int i=k;i>=v;i--) f[i]=max(f[i],f[i-v]+w);}
}
namespace KS2{
	int f[N];
	inline void Init(){memset(f,0x3f,sizeof f),f[0]=0;}
	inline void Shift(){for(int i=k/B-1;i>=0;i--) f[i]=min(f[i],f[i+1]);}
	inline void Insert(int v,int w){for(int i=k/B;i>=w;i--) f[i]=min(f[i],f[i-w]+v);Shift();}
}
inline int Calc(int lim){
	int ans=0;
	for(int i=0;i<=k/B&&KS2::f[i]<=lim;i++) ans=max(ans,i+KS1::f[lim-KS2::f[i]]);
	return ans;
}

signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) cin>>a[i][0]>>a[i][1];
	for(int i=1;i<=m;i++) cin>>op[i]>>id[i],imp[id[i]]|=op[i]&1;

	KS1::Init();
	for(int i=1;i<=n;i++) if(!imp[i]&&a[i][0]<=B) KS1::Insert(a[i][0]*a[i][1],a[i][1]);
	KS2::Init();
	for(int i=1;i<=n;i++) if(!imp[i]&&a[i][0]>B) xs[a[i][1]].push_back(a[i][0]);
	for(int i=1;i<=k;i++){
		int sum=0;
		sort(xs[i].begin(),xs[i].end());
		for(int t:xs[i]){
			if(i*(sum+t)>k) break ;
			KS2::Insert(i*t,i);
			sum+=t;
		}
	}

	for(int i=m;i>=1;i--){
		if(op[i]==1){
			if(a[id[i]][0]<=B) KS1::Insert(a[id[i]][0]*a[id[i]][1],a[id[i]][1]);
			else KS2::Insert(a[id[i]][0]*a[id[i]][1],a[id[i]][1]);
		}else ans[i]=Calc(id[i]);
	}

	for(int i=1;i<=m;i++) if(op[i]==2) cout<<ans[i]<<endl;

	return 0;
}