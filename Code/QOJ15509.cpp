#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
using uint=unsigned;
using ull=unsigned long long;
const int N=3e5+9;
const int D=1e1+9;
const int T=(1<<12)+9;

int a[N],n,d,p,q,lim;
int A[N],B[N],C[N],l1[N],r1[N],l2[N],r2[N];
uint w[N],z[T];

struct Block{
	int blk[N],L[N],R[N],S;
	uint sum[N],suf[N],v[N],bs[N],bv[N];
	inline void Init(){
		S=sqrt(n);
		for(int i=1;i<=n;i++) blk[i]=(i-1)/S+1;
		for(int i=1;i<=n;i++) R[blk[i]]=i;
		for(int i=n;i>=1;i--) L[blk[i]]=i;
		for(int i=1;i<=n;i++) sum[blk[i]]+=w[i];
		for(int i=1;i<=blk[n];i++){
			suf[R[i]]=w[R[i]];
			for(int j=R[i]-1;j>=L[i];j--) suf[j]=suf[j+1]+w[j];
		}
	}
	inline void Clear(){
		for(int i=1;i<=n;i++) v[i]=0;
		for(int i=1;i<=blk[n];i++) bs[i]=bv[i]=0;
	}
	inline void Modify(int pos,uint k){
		if(pos<1||pos>n) return ;
		v[pos]+=k,bv[blk[pos]]+=k,bs[blk[pos]]+=suf[pos]*k;
	}
	inline void Modify(int l,int r,uint k){Modify(l,k),Modify(r+1,-k);}
	inline uint Query(int pos){
		if(pos<1||pos>n) return 0;
		uint ans=0,cur=0;
		for(int i=1;i<blk[pos];i++){
			ans+=bs[i]+cur*sum[i];
			cur+=bv[i];
		}
		for(int i=L[blk[pos]];i<=pos;i++){
			cur+=v[i];
			ans+=cur*w[i];
		}
		return ans;
	}
	inline uint Query(int l,int r){return Query(r)-Query(l-1);}
};
namespace P2{
	uint sw[N],sz[N],ans[N];
	int cnt[T],c[T][D][D],tot;
	vector<int> qry[N];
	vector<array<int,2>> ord[T],opr[T];
	
	const ull base=4649;
	inline ull Hash(vector<array<int,2>> v){
		ull res=0;
		for(auto p:v) for(int x:p) res=res*base+x;
		return res;
	}
	#define popc __builtin_popcount
	
	Block bx,by;
	inline void Solve(){
		for(int i=1;i<=n;i++) cnt[a[i]]++;
		for(int i=0;i<lim;i++){
			for(int j=0;j<lim;j++) c[i][popc(i&j)][popc(~i&j)]+=cnt[j];
		}
		for(int i=1;i<=n;i++) sw[i]=sw[i-1]+w[i];
		for(int i=0;i<lim;i++) sz[i]=(i?sz[i-1]:0)+z[i]*popc(i);

		vector<array<int,2>> tmp;
		for(int i=0;i<=d;i++){
			for(int j=0;i+j<=d;j++) tmp.push_back({i,j});
		}
		map<ull,int> mp;
		for(int i=1;i<=q;i++){
			ll X=A[i]-C[i],Y=B[i]+C[i];
			sort(tmp.begin(),tmp.end(),[&](auto x,auto y){
				return X*x[0]+Y*x[1]<X*y[0]+Y*y[1];
			});
			ull h=Hash(tmp);
			if(!mp[h]) mp[h]=++tot,ord[tot]=tmp;
			qry[mp[h]].push_back(i);
		}

		bx.Init(),by.Init();
		for(int o=1;o<=tot;o++){
			for(int i:qry[o]){
				if(l1[i]) opr[l1[i]-1].push_back({i,-1});
				opr[r1[i]].push_back({i,1});
			}
			for(int i=0;i<lim;i++){
				int k=0;
				for(auto p:ord[o]){
					if(!c[i][p[0]][p[1]]) continue ;
					bx.Modify(k+1,k+c[i][p[0]][p[1]],z[i]*p[0]);
					by.Modify(k+1,k+c[i][p[0]][p[1]],z[i]*p[1]);
					k+=c[i][p[0]][p[1]];
				}
				for(auto p:opr[i]){
					int j=p[0],k=p[1];
					ans[j]+=k*(A[j]-C[j])*bx.Query(l2[j],r2[j]);
					ans[j]+=k*(B[j]+C[j])*by.Query(l2[j],r2[j]);
				}
				opr[i].clear();
			}
			bx.Clear(),by.Clear();
		}

		for(int i=1;i<=q;i++){
			ans[i]+=(B[i]+C[i])*(sw[r2[i]]-sw[l2[i]-1])*(sz[r1[i]]-(l1[i]?sz[l1[i]-1]:0));
			cout<<ans[i]<<endl;
		}
	}
	#undef popc
}
namespace P3{
	int popc[T],and3[T][T],or3[T][T],xor3[T][T];
	inline void Init(){
		for(int i=0;i<lim;i++) popc[i]=popc[i/3]+bool(i%3);
		for(int i=0;i<lim;i++){
			for(int j=0;j<lim;j++){
				and3[i][j]=and3[i/3][j/3]*3+min(i%3,j%3);
				or3[i][j]=or3[i/3][j/3]*3+max(i%3,j%3);
				xor3[i][j]=xor3[i/3][j/3]*3+(i+j)%3;
			}
		}
	}

	uint ans[N];
	int cnt[T],c[T][D][D][D],tot;
	vector<int> qry[N];
	vector<array<int,2>> opr[T];
	vector<array<int,3>> ord[N];

	const ull base=4649;
	inline ull Hash(vector<array<int,3>> v){
		ull res=0;
		for(auto p:v) for(int x:p) res=res*base+x;
		return res;
	}

	Block bx,by,bz;
	inline void Solve(){
		Init();
		for(int i=1;i<=n;i++) cnt[a[i]]++;
		for(int i=0;i<lim;i++){
			for(int j=0;j<lim;j++){
				c[i][popc[and3[i][j]]][popc[or3[i][j]]][popc[xor3[i][j]]]+=cnt[j];
			}
		}

		vector<array<int,3>> tmp;
		for(int i=0;i<lim;i++){
			for(int j=0;j<lim;j++){
				tmp.push_back({popc[and3[i][j]],popc[or3[i][j]],popc[xor3[i][j]]});
			}
		}
		sort(tmp.begin(),tmp.end());
		tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());

		map<ull,int> mp;
		for(int i=1;i<=q;i++){
			ll X=A[i],Y=B[i],Z=C[i];
			sort(tmp.begin(),tmp.end(),[&](auto x,auto y){
				ll fx=X*x[0]+Y*x[1]+Z*x[2];
				ll fy=X*y[0]+Y*y[1]+Z*y[2];
				if(fx!=fy) return fx<fy;
				else return x<y;
			});
			ull h=Hash(tmp);
			if(!mp[h]) mp[h]=++tot,ord[tot]=tmp;
			qry[mp[h]].push_back(i);
		}

		bx.Init(),by.Init(),bz.Init();
		for(int o=1;o<=tot;o++){
			for(int i:qry[o]){
				if(l1[i]) opr[l1[i]-1].push_back({i,-1});
				opr[r1[i]].push_back({i,1});
			}
			for(int i=0;i<lim;i++){
				int k=0;
				for(auto p:ord[o]){
					if(!c[i][p[0]][p[1]][p[2]]) continue ;
					bx.Modify(k+1,k+c[i][p[0]][p[1]][p[2]],z[i]*p[0]);
					by.Modify(k+1,k+c[i][p[0]][p[1]][p[2]],z[i]*p[1]);
					bz.Modify(k+1,k+c[i][p[0]][p[1]][p[2]],z[i]*p[2]);
					k+=c[i][p[0]][p[1]][p[2]];
				}
				for(auto p:opr[i]){
					int j=p[0],k=p[1];
					ans[j]+=k*A[j]*bx.Query(l2[j],r2[j]);
					ans[j]+=k*B[j]*by.Query(l2[j],r2[j]);
					ans[j]+=k*C[j]*bz.Query(l2[j],r2[j]);
				}
				opr[i].clear();
			}
			bx.Clear(),by.Clear(),bz.Clear();
		}

		for(int i=1;i<=q;i++) cout<<ans[i]<<endl;
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>d>>p;
	lim=round(powl(p,d));
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>w[i];
	for(int i=0;i<lim;i++) cin>>z[i];
	cin>>q;
	for(int i=1;i<=q;i++) cin>>A[i]>>B[i]>>C[i]>>l1[i]>>r1[i]>>l2[i]>>r2[i];

	if(p==2) P2::Solve();
	else P3::Solve();

	return 0;
}