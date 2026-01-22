## Jan. 19

### A. 歌

考虑枚举最小的初段长度 $p$ 使得存在合法划分，并对其容斥。

假设当前有若干种长度使得该序列存在合法划分，那么形态如下图所示。

![image-20260120161016198](C:\Users\cyez-oi\AppData\Roaming\Typora\typora-user-images\image-20260120161016198.png)

图中数字相同的段有相同的颜色，首段和末端可能有残缺。

注意到大部分贡献都是重复的，设 $f_{0/1,i}$ 表示当前选择段数奇偶性，最长段是 $i$，可以根据上图进行 1D/1D 的转移。

时间复杂度 $O(k^3)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

ifstream fin("song.in");
ofstream fout("song.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;

ll n,k;
struct FastMod { // 请将该结构体直接复制，粘贴到你的代码中
    unsigned long long b, m;
    FastMod() = default;
    FastMod(unsigned long long m) : b(((unsigned __int128)1 << 64) / m), m(m) {}
    unsigned long long operator()(unsigned long long a) {
        unsigned long long q = (unsigned __int128)a * b >> 64;
        unsigned long long r = a - q * m;
        return r >= m ? r - m : r;
    }
} fastmod;
int mod;
inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=fastmod(1ll*x*y);}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return fastmod(1ll*x*y);}
inline int QPow(int x,int y){
	int res=1;
	while(y){
		if(y&1) MulAs(res,x);
		MulAs(x,x);
		y>>=1;
	}
	return res;
}
inline int Inv(int x){return QPow(x,mod-2);}

const int K=1e3+9;
int fac[K],ifac[K];
inline void Init(int lim){
	fastmod=FastMod(mod);
	fac[0]=1;
	for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
	ifac[lim]=Inv(fac[lim]);
	for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
}
inline int C(int n,int m){
	if(m<0||m>n) return 0;
	else return Mul(fac[n],Mul(ifac[m],ifac[n-m]));
}
inline int iC(int n,int m){
	if(m<0||m>n) return 0;
	else return Mul(ifac[n],Mul(fac[m],fac[n-m]));
}

int f[2][K],pf[K][2],ipf[K][2];

inline void Solve(){
	cin>>n>>k>>mod;

	Init(k);
	if(n<=k){
		int ans=Mul(C(k,n),fac[n]);
		for(int i=1;i<k;i++){
			AddAs(ans,Mul(Mul(Mul(C(k,i),fac[i]),i),Mul(C(k-1,n-1-i),fac[n-1-i])));
		}
		cout<<ans<<endl;
	}else{
		int ans=0;
		for(int i=0;i<=k;i++){
			pf[i][0]=ipf[i][0]=1;
			for(int j=1;j<=k;j++){
				pf[i][j]=Mul(pf[i][j-1],fac[i]);
				ipf[i][j]=Mul(ipf[i][j-1],ifac[i]);
			}
		}
		for(int i=1;i<=k;i++){
			int t=(n-i)/k%(mod-1),r=(n-i)%k;
			for(int j=0;j<=k;j++){
				for(int c:{0,1}){
					pf[j][c]=QPow(fac[j],t+c);
					ipf[j][c]=Inv(pf[j][c]);
				}
			}
			auto F=[&](int i,int j){
				if(i<r&&r<=j) return Mul(Mul(C(k-i,k-j),pf[j-i][0]),Mul(C(j-i,r-i),fac[r-i]));
				else return Mul(C(k-i,k-j),pf[j-i][j<r]);
			};
			auto G=[&](int p){
				return Mul(pf[k-p][0],Mul(C(k-p,max(r-p,0)),fac[max(r-p,0)]));
			};
			auto iG=[&](int p){
				return Mul(ipf[k-p][0],Mul(iC(k-p,max(r-p,0)),ifac[max(r-p,0)]));
			};
			f[1][0]=G(0);
			for(int j=0;i+j<=k;j++){
				for(int p=j+1;i+p<=k;p++){
					for(int c:{0,1}){
						AddAs(f[!c][p],Mul(f[c][j],Mul(F(j,p),Mul(iG(j),G(p)))));
					}
				}
			}
			for(int j=0;j<=k;j++){
				AddAs(ans,Mul(Mul(C(k-j,i),fac[i]),Sub(f[1][j],f[0][j])));
				f[0][j]=f[1][j]=0;
			}
		}
		cout<<ans<<endl;
	}
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}
```

### B. 火力大喵

第一问答案就是最大值减最小值。

第二问就相当于查询边框上存在最大值和最小值的矩形数，考虑将其容斥成边框上没有最大值或最小值以及两个都不能有，这样就拆成三个问 $0/1$ 矩阵中边框上都是 $1$ 的矩形数量。

考虑分治，每次对子矩形的长边折半，枚举中线上矩形与中线的两个交点，那么对半边问的就是交点特定的 C 形数量。

不失一般性地先只考虑左半边。对于触点 $i,j$，假设 $i$ 向左连续 $1$ 段比 $j$ 短，那么贡献就是在 $i$ 向左连续 $1$ 段内的向下连续 $1$ 段长度超过 $j-i+1$ 的点的个数。枚举 $i$ 扫描 $j$ 可以做到单层 $O(nm)$，总的就是 $O(nm\log nm)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

ifstream fin("dameow.in");
ofstream fout("dameow.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e3+9;

int a[N][N],b1[N][N],b2[N][N],b3[N][N],n,m;
int U[N][N],D[N][N],L[N][N],R[N][N],cnt[N],s[N][N],t[N][N];
inline void Conquer(int a[N][N],int l1,int r1,int l2,int r2,ll &ans){
	if(l1==r1&&l2==r2) return ans+=a[l1][l2],void();
	for(int i=l1;i<=r1;i++){
		for(int j=l2;j<=r2;j++){
			if(a[i][j]){
				U[i][j]=(i-1>=l1?U[i-1][j]:0)+1;
				L[i][j]=(j-1>=l2?L[i][j-1]:0)+1;
			}else U[i][j]=L[i][j]=0;
		}
	}
	for(int i=r1;i>=l1;i--){
		for(int j=r2;j>=l2;j--){
			if(a[i][j]){
				D[i][j]=(i+1<=r1?D[i+1][j]:0)+1;
				R[i][j]=(j+1<=r2?R[i][j+1]:0)+1;
			}else D[i][j]=R[i][j]=0;
		}
	}
	if(r1-l1>r2-l2){
		int mid=l1+r1>>1;
		for(int i=l2;i<=r2;i++){
			s[i][i]=U[mid][i];
			for(int j=mid-U[mid][i]+1;j<=mid;j++) cnt[L[j][i]]++;
			for(int j=i-l2+1;j>=0;j--) cnt[j]+=cnt[j+1];
			for(int j=l2;j<i;j++) if(U[mid][j]>U[mid][i]) s[j][i]+=cnt[i-j+1];
			memset(cnt,0,(r2-l2+2)*sizeof int());
			for(int j=mid-U[mid][i]+1;j<=mid;j++) cnt[R[j][i]]++;
			for(int j=r2-i+1;j>=0;j--) cnt[j]+=cnt[j+1];
			for(int j=r2;j>i;j--) if(U[mid][j]>=U[mid][i]) s[i][j]+=cnt[j-i+1];
			memset(cnt,0,(r2-l2+2)*sizeof int());
		}
		for(int i=l2;i<=r2;i++){
			t[i][i]=D[mid+1][i];
			for(int j=mid+1;j<=mid+D[mid+1][i];j++) cnt[L[j][i]]++;
			for(int j=i-l2+1;j>=0;j--) cnt[j]+=cnt[j+1];
			for(int j=l2;j<i;j++) if(D[mid+1][j]>D[mid+1][i]) t[j][i]+=cnt[i-j+1];
			memset(cnt,0,(r2-l2+2)*sizeof int());
			for(int j=mid+1;j<=mid+D[mid+1][i];j++) cnt[R[j][i]]++;
			for(int j=r2-i+1;j>=0;j--) cnt[j]+=cnt[j+1];
			for(int j=r2;j>i;j--) if(D[mid+1][j]>=D[mid+1][i]) t[i][j]+=cnt[j-i+1];
			memset(cnt,0,(r2-l2+2)*sizeof int());
		}
		for(int i=l2;i<=r2;i++){
			for(int j=i;j<=r2;j++){
				ans+=s[i][j]*t[i][j];
				s[i][j]=t[i][j]=0;
			}
		}
		Conquer(a,l1,mid,l2,r2,ans);
		Conquer(a,mid+1,r1,l2,r2,ans);
	}else{
		int mid=l2+r2>>1;
		for(int i=l1;i<=r1;i++){
			s[i][i]=L[i][mid];
			for(int j=mid-L[i][mid]+1;j<=mid;j++) cnt[U[i][j]]++;
			for(int j=i-l1+1;j>=0;j--) cnt[j]+=cnt[j+1];
			for(int j=l1;j<i;j++) if(L[j][mid]>L[i][mid]) s[j][i]+=cnt[i-j+1];
			memset(cnt,0,(r1-l1+2)*sizeof int());
			for(int j=mid-L[i][mid]+1;j<=mid;j++) cnt[D[i][j]]++;
			for(int j=r1-i+1;j>=0;j--) cnt[j]+=cnt[j+1];
			for(int j=r1;j>i;j--) if(L[j][mid]>=L[i][mid]) s[i][j]+=cnt[j-i+1];
			memset(cnt,0,(r1-l1+2)*sizeof int());
		}
		for(int i=l1;i<=r1;i++){
			t[i][i]=R[i][mid+1];
			for(int j=mid+1;j<=mid+R[i][mid+1];j++) cnt[U[i][j]]++;
			for(int j=i-l1+1;j>=0;j--) cnt[j]+=cnt[j+1];
			for(int j=l1;j<i;j++) if(R[j][mid+1]>R[i][mid+1]) t[j][i]+=cnt[i-j+1];
			memset(cnt,0,(r1-l1+2)*sizeof int());
			for(int j=mid+1;j<=mid+R[i][mid+1];j++) cnt[D[i][j]]++;
			for(int j=r1-i+1;j>=0;j--) cnt[j]+=cnt[j+1];
			for(int j=r1;j>i;j--) if(R[j][mid+1]>=R[i][mid+1]) t[i][j]+=cnt[j-i+1];
			memset(cnt,0,(r1-l1+2)*sizeof int());
		}
		for(int i=l1;i<=r1;i++){
			for(int j=i;j<=r1;j++){
				ans+=s[i][j]*t[i][j];
				s[i][j]=t[i][j]=0;
			}
		}
		Conquer(a,l1,r1,l2,mid,ans);
		Conquer(a,l1,r1,mid+1,r2,ans);
	}
}

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>a[i][j];
	}

	int mx=INT_MIN,mn=INT_MAX;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			mx=max(mx,a[i][j]);
			mn=min(mn,a[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			b1[i][j]=(a[i][j]!=mx);
			b2[i][j]=(a[i][j]!=mn);
			b3[i][j]=(a[i][j]!=mx&&a[i][j]!=mn);
		}
	}

	ll ans=0,s1=0,s2=0,s3=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) ans+=1ll*i*j;
	}
	Conquer(b1,1,n,1,m,s1);
	Conquer(b2,1,n,1,m,s2);
	Conquer(b3,1,n,1,m,s3);
	ans-=s1;
	ans-=s2;
	ans+=s3;


	cout<<mx-mn<<' '<<ans<<endl;

	return 0;
}
```

## Jan. 20

### A. 胜兵必骄

令 $a_i=1$ 表示有箱子，否则没箱子。

考虑找到一个有箱子且领域中有节点没箱子的节点作为根，先让所有有箱子的节点全部把自己子树里到碰到箱子为止的所有没箱子的节点和其父亲的边跑一边，即每个没箱子的节点都归其到根链上的第一个有箱子的节点管。

那么现在没有跑的就是非根的有箱子节点到其父亲的边，如果该节点父亲有箱子，那么等他父亲去领域的时候快速跑掉，否则一开始就跑掉。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

ifstream fin("wars.in");
ofstream fout("wars.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e6+9;

vector<int> e[N];
list<array<int,2>> s[N];
list<array<int,2>>::iterator in[N],out[N];
int a[N],n,root;

inline void DFS1(int x,int fa){
	for(int y:e[x]){
		if(y==fa) continue ;
		DFS1(y,x);
		if(!a[y]){
			s[y].insert(s[y].begin(),{x,y});
			s[y].insert(s[y].end(),{x,y});
			s[x].splice(s[x].end(),s[y]);
		}
	}
}
inline void DFS2(int x,int fa,int ffa){
	if(x!=root&&a[x]){
		auto it=fa==ffa?out[ffa]:in[ffa];
		in[x]=s[root].insert(it,{x,fa});
		s[x].insert(s[x].begin(),{x,fa});
		s[root].splice(it,s[x]);
		out[x]=next(in[x]);
		ffa=x;
	}
	for(int y:e[x]){
		if(y==fa) continue ;
		DFS2(y,x,ffa);
	}
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	for(int x=1;x<=n;x++){
		if(!a[x]) continue ;
		for(int y:e[x]){
			if(a[y]) continue ;
			root=x;
			break ;
		}
		if(root) break ;
	}

	DFS1(root,0);
	in[root]=s[root].begin();
	out[root]=next(in[root]);
	DFS2(root,0,root);

	for(auto p:s[root]) cout<<p[0]<<' '<<p[1]<<endl;

	return 0;
}
```

### B. 数据恢复

先将 $a$ 做如下变换，令 $p_1,\ldots,p_k$ 表示其前缀最大值位置，那么将 $[p_i,p_{i+1})$ 的位置向左循环移位一次，即把 $p_i$ 放到 $p_{i+1}-1$ 的位置，那么前缀最大值的限制就不对最大值之后的数产生约束。

考察任意两个位置 $i,j(i<j)$ 之间的关系。若 $a_i<a_j$ 则无事发生，若 $a_i>a_j$ 则必然存在约束使得其无法交换使字典序更小，因此特别关注所有逆序对的限制，设 $x_i$ 表示位置 $i$ 是否清晰可见：

-   若 $c_i=c_j=0$，那么 $x_i,x_j$ 不同时为 $0$。
-   若 $c_i=1,c_j=0$，存在 $x_i,x_j$ 不同时为 $0$ 的限制当且仅当 $\displaystyle \max_{k=1}^{i-1} a_k<a_j<a_i$。
-   若 $c_j=1$，则 $a_i<a_j$。

因此考虑按值域从后向前填数，设 $f_{i,0/1,j}$ 表示当前考虑到 $i$，最大值是否清晰可见，目前非清晰可见的 $c_p=0$ 最小的 $p$ 是 $j$，转移是简单的。

线段树优化 DP 即可做到 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

ifstream fin("recovery.in");
ofstream fout("recovery.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e6+9;
const int mod=998244353;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
	int res=1;
	while(y){
		if(y&1) MulAs(res,x);
		MulAs(x,x);
		y>>=1;
	}
	return res;
}
inline int Inv(int x){return QPow(x,mod-2);}

struct Vec{
	int a[2];
	Vec(){memset(a,0,sizeof a);}
	Vec(int x,int y){a[0]=x,a[1]=y;}
	inline int& operator [](int p){return a[p];}
	friend inline Vec operator +(Vec A,Vec B){return Vec(Add(A[0],B[0]),Add(A[1],B[1]));}
};
struct Node{
	int l,r;
	Vec dat;
	int tag;
}tr[N<<2];

int pw[N];
inline void PushUp(int x){tr[x].dat=tr[x<<1].dat+tr[x<<1|1].dat;}
inline void Push(int x,int k){
	tr[x].tag+=k;
	tr[x].dat[0]=tr[x].dat[1]=Mul(pw[k-1],Add(tr[x].dat[0],tr[x].dat[1]));
}
inline void PushDown(int x){
	if(tr[x].tag){
		Push(x<<1,tr[x].tag);
		Push(x<<1|1,tr[x].tag);
		tr[x].tag=0;
	}
}

inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r,tr[x].dat=Vec(0,0),tr[x].tag=0;
	if(tr[x].l==tr[x].r) return ;
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Set(int x,int pos,Vec k){
	if(tr[x].l==tr[x].r) return tr[x].dat=k,void();
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) Set(x<<1,pos,k);
	else Set(x<<1|1,pos,k);
	PushUp(x);
}
inline Vec Query(int x,int l,int r){
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].dat;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return Query(x<<1,l,r);
	else if(l>mid) return Query(x<<1|1,l,r);
	else return Query(x<<1,l,r)+Query(x<<1|1,l,r);
}

int a[N],c[N],id[N],pmx[N],n;
inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	
	int mx=0;
	vector<int> p;
	for(int i=1;i<=n;i++){
		mx=max(mx,a[i]);
		if(a[i]==mx) p.push_back(i),c[i]=1;
		else c[i]=0;
	}
	p.push_back(n+1);
	for(int i=0;i+1<p.size();i++){
		for(int j=p[i];j+1<p[i+1];j++){
			swap(a[j],a[j+1]);
			swap(c[j],c[j+1]);
		}
	}
	for(int i=1;i<=n;i++){
		id[a[i]]=i;
		pmx[i]=max(pmx[i-1],a[i]);
	}
	pw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=Mul(2,pw[i-1]);

	Build(1,0,n+1);
	Set(1,n+1,{1,0});
	for(int i=n,cur=0;i>=1;i--){
		if(c[id[i]]){
			cur=pmx[id[i]-1];
			Push(1,1);
		}else{
			Vec v=Query(1,id[i],id[i]),u=Query(1,id[i],n+1);
			if(i<=cur) AddAs(v[0],u[0]);
			AddAs(v[1],u[1]);
			Set(1,id[i],v);
		}
	}

	cout<<Add(tr[1].dat[0],tr[1].dat[1])<<endl;
}

signed main(){
	int o,T;
	cin>>o>>T;
	while(T--) Solve();
	
	return 0;
}
```

