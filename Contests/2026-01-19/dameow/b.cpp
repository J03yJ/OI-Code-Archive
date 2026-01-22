#include<bits/stdc++.h>

using namespace std;

ifstream fin("b.in");
ofstream fout("b.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e3+9;

int a[N][N],s[N][N],b1[N][N],b2[N][N],b3[N][N],n,m;
inline ll Calc(int a[N][N]){
	ll ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) s[i][j]=s[i-1][j]+a[i][j];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) s[i][j]-=i;
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			for(int k=1,r=0;k<=m;k++){
				if(!a[i][k]||!a[j][k]) r=0;
				else if(s[j][k]==s[i-1][k]) ans+=++r;
			}
		}
	}
	memset(s,0,sizeof s);
	return ans;
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

	ll ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) ans+=1ll*i*j;
	}
	ans-=Calc(b1);
	ans-=Calc(b2);
	ans+=Calc(b3);

	cout<<mx-mn<<' '<<ans<<endl;

	return 0;
}