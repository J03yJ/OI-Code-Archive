#include<bits/stdc++.h>

using namespace std;

ifstream fin("gift.in");
ofstream fout("gift.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e3+9;
const int K=2e1+9;

int a[N],id[N],ans[N],opt[N][K],n,k;
ll f[N][K],w[N][N],pos[N][N],sum[N],sum2[N];

signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i],id[i]=i;

	sort(id+1,id+n+1,[](int i,int j){return a[i]<a[j];});
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+a[id[i]];
		sum2[i]=sum2[i-1]+1ll*a[id[i]]*a[id[i]];
	}

	memset(f,0x3f,sizeof f);
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			pos[i][j]=a[id[j]];
			ll a=j-i+1;
			ll b=2*(sum[j]-sum[i-1]);
			ll c=sum2[j]-sum2[i-1];
			w[i][j]=pos[i][j]*(pos[i][j]*a-b)+c;
		}
	}
	for(int j=0;j<=k;j++) f[0][j]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=k;j++){
			for(int p=i;p>=max(1,opt[i-1][j]);p--){
				ll tmp=w[p][i]+f[p-1][j-1];
				if(tmp<f[i][j]) f[i][j]=tmp,opt[i][j]=p;
			}
		}
	}

	int cur=n;
	for(int i=k;i>=1;i--){
		if(!cur) break ;
		int nxt=opt[cur][i];
		for(int j=nxt;j<=cur;j++) ans[id[j]]=pos[nxt][cur];
		cur=nxt-1;
	}

	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;

	return 0;
}