#include<bits/stdc++.h>

using namespace std;

ifstream fin("perm.in");
ofstream fout("perm.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e3+9;

int a[N],pos[N],cnt[N][N],f[N][N],n;

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) a[i]=n-a[i]+1;

	n++;
	a[n]=n;
	for(int i=1;i<=n;i++) pos[a[i]]=i;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) cnt[i][j]=cnt[i][j-1]+(a[j]<i);
	}

	memset(f,0x3f,sizeof f);
	f[n][n]=0;
	for(int i=n-1;i>=1;i--){
		for(int j=1;j<=n;j++){
			f[i][j]=f[i+1][j]+cnt[i][pos[i]]+cnt[i][j]+2;
		}
		for(int j=pos[i]+1,tmp=0;j<=n;j++){
			f[i][pos[i]]=min(f[i][pos[i]],f[i+1][j]+tmp);
			tmp+=max(i-a[j],0);
		}
	}

	int ans=0x3f3f3f3f;
	for(int i=1;i<=n;i++) ans=min(ans,f[1][i]);
	cout<<ans<<endl;

	return 0;
}