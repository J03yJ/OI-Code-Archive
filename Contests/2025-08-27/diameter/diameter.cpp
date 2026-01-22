#include<bits/stdc++.h>

using namespace std;

ifstream fin("diameter.in");
ofstream fout("diameter.out");
#define cin fin
#define cout fout
#define endl '\n'

bool bg;
const int N=2e2+9;

int a[N],b[N],asum[N],bsum[N],n,k;
int f[N][N],ls[N][N],rs[N][N],s[N][N];

bool ed;

signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];

	for(int i=1;i<=n;i++) asum[i]=asum[i-1]+a[i];
	for(int i=1;i<=n;i++) bsum[i]=bsum[i-1]+b[i];

	for(int i=0;i<=n;i++){
		for(int j=i;j<=n;j++){
			int sum=asum[j]-asum[i]+bsum[j]-bsum[i];
			for(int p=i,t=0;p<=j;t+=a[++p]) ls[i][j]=max(ls[i][j],min(t,sum-t));
			for(int p=i,t=0;p<=j;t+=b[++p]) ls[i][j]=max(ls[i][j],min(t,sum-t));
			for(int p=j,t=0;p>=i;t+=a[p--]) rs[i][j]=max(rs[i][j],min(t,sum-t));
			for(int p=j,t=0;p>=i;t+=b[p--]) rs[i][j]=max(rs[i][j],min(t,sum-t));
			for(int p=i;p<=j;p++){
				for(int q=i;q<=j;q++){
					int t1=asum[p]-asum[i]+bsum[q]-bsum[i];
					s[i][j]=max(s[i][j],min(t1,sum-t1));
					int t2=asum[q]-asum[p];
					s[i][j]=max(s[i][j],min(t2,sum-t2));
					int t3=bsum[q]-bsum[p];
					s[i][j]=max(s[i][j],min(t3,sum-t3));
				}
			}
		}
	}

	int l=-1,r=50*n+1;
	while(l+1<r){
		int mid=l+r>>1;

		bool flag=0;
		memset(f,0x3f,sizeof f);
		for(int i=0;i<=n;i++){
			if(asum[i]+bsum[i]<=mid) f[i][1]=max(asum[i],bsum[i]);
			for(int j=1;j<=min(i+1,k);j++){
				if(f[i][j]>1e8) continue ;
				int p=f[i][j];
				for(int _i=i+1;_i<=n;_i++){
					int _p=max(p+min(asum[_i]-asum[i],bsum[_i]-bsum[i]),rs[i][_i]);
					int res=max(s[i][_i],p+ls[i][_i]);
					if(res<=mid) f[_i][j+1]=min(f[_i][j+1],_p);
				}
				if(j==k){
					int p=f[i][j];
					int res=0;
					res=max(res,asum[n]-asum[i]+bsum[n]-bsum[i]);
					res=max(res,p+max(asum[n]-asum[i],bsum[n]-bsum[i]));
					if(res<=mid) flag|=1;
				}
			}
		}
		if(flag) r=mid;
		else l=mid;
	}

	cout<<r<<endl;
	
	return 0;
}