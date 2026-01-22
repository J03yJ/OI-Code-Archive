#include<bits/stdc++.h>

using namespace std;

ifstream fin("sqr.in");
ofstream fout("sqr.out");
#define cin fin
#define cout fout
#define endl '\n'

#define double long double
const int N=2e5+9;
const int K=30;
const int T=5;
const double eps=1e-8;

int a[N],op[N],ql[N],qr[N],n,q;
int blk[N],L[N],R[N],B;
int cnt[N];

double val[N][K+T+9],dlt[N<<1],ans[N];
int mx,mn;
inline void Insert(int pos){
	for(int i=1;i<=K+T;i++){
		dlt[-cnt[pos]+i-K+N]+=val[pos][i]-val[pos][i-1];
	}
}
inline void Erase(int pos){
	for(int i=1;i<=K+T;i++){
		dlt[-cnt[pos]+i-K+N]-=val[pos][i]-val[pos][i-1];
	}
}

signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=q;i++) cin>>op[i]>>ql[i]>>qr[i];

	for(int i=1;i<=n;i++){
		val[i][K]=a[i];
		for(int j=-1;j>=-K;j--) val[i][K+j]=sqrtl(val[i][K+j+1]);
		for(int j=1;j<=T;j++) val[i][K+j]=min((double)1e8,powl(val[i][K+j-1],2));
	}
	
	B=max(1,min(n,int(ceil(sqrt(n/60)))));
	for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
	for(int i=1;i<=n;i++) R[blk[i]]=i;
	for(int i=n;i>=1;i--) L[blk[i]]=i;

	int c=0;
	for(int x=1;x<=blk[n];x++){
		for(int i=L[x];i<=R[x];i++) Insert(i);

		int tag=0;
		double sum=0;
		for(int i=L[x];i<=R[x];i++) sum+=a[i];
		for(int t=1;t<=q;t++){
			if(qr[t]<L[x]||ql[t]>R[x]) continue ;
			int l=max(ql[t],L[x]),r=min(qr[t],R[x]);
			if(l==L[x]&&r==R[x]){
				c++;
				if(op[t]==1) sum+=dlt[++tag+N];
				else if(op[t]==2) sum-=dlt[tag--+N];
				else if(op[t]==3) ans[t]+=sum;
			}else{
				for(int i=L[x];i<=R[x];i++) Erase(i);
				for(int i=L[x];i<=R[x];i++) cnt[i]+=tag;
				tag=0;
				if(op[t]==1) for(int i=l;i<=r;i++) cnt[i]++;
				else if(op[t]==2) for(int i=l;i<=r;i++) cnt[i]--;
				else if(op[t]==3){
					for(int i=l;i<=r;i++){
						if(cnt[i]<-K) ans[t]+=1;
						else if(cnt[i]>T) ans[t]+=a[i]!=1?1e8:1;
						else ans[t]+=val[i][cnt[i]+K];
					}
				}
				sum=0;
				double p=0;
				for(int i=L[x];i<=R[x];i++){
					if(cnt[i]<-K) sum+=1;
					else if(cnt[i]>T) sum+=a[i]!=1?1e8:1;
					else sum+=val[i][cnt[i]+K];
					p+=val[i][cnt[i]+K]-val[i][cnt[i]+K-1];
				}
				for(int i=L[x];i<=R[x];i++) Insert(i);
			}
		}
		for(int i=L[x];i<=R[x];i++) Erase(i);
	}

	for(int i=1;i<=q;i++) if(op[i]==3) cout<<(long long)round(ans[i])<<endl;

	return 0;
}