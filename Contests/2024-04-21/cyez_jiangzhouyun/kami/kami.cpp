#include<bits/stdc++.h>
using namespace std;

#define int long long

ifstream fin("kami.in");
ofstream fout("kami.out");
#define cin fin
#define cout fout

const int N=3e3+9;
const int p=998244353;
int a[N][N],s[N][N];

int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=ans*x%p;
		x=x*x%p;
		y>>=1;
	}
	return ans;
}

signed main(){
	int n,k;
	cin>>n>>k;
	
	if(!k){
		int sum=0;
		int r=(n+1)/2;
		sum=r*(n*n%p+5*n%p+6)%p;
		sum=(sum-(2*n%p+5)*r%p*(r+1)%p+p)%p;
		sum=(sum+2*r%p*(r+1)%p*(2*r+1)%p*qpow(3,p-2)%p)%p;
		cout<<sum*qpow(2,p-2)%p<<endl;
		return 0;
	}
	
	for(int i=1;i<=k;i++){
		int x,y;
		cin>>x>>y;
		a[n-y+1][x]=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
//			cout<<s[i][j]<<' ';
		}
//		cout<<endl;
	}
	#define S(a,b,c,d) (s[c][d]-s[a-1][d]-s[c][b-1]+s[a-1][b-1])
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			int l=0,r=min(n-i+1,i-j+1)+1;
			while(l+1<r){
				int mid=l+r>>1;
				if(S(i,j,i+mid-1,j+mid-1)) r=mid;
				else l=mid;
			}
			ans=(ans+l)%p;
		}
	}
	cout<<ans<<endl;
	return 0;
}
