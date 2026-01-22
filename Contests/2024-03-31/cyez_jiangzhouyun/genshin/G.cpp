#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=3e5+9;
int a[N],b[N],f[N];

ifstream fin("genshin.in");
ofstream fout("genshin.out");
#define cin fin
#define cout fout

int gcd(int x,int y){
	if(!y) return x;
	else return gcd(y,x%y);
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		memset(f,0,sizeof(f));
		memset(b,0,sizeof(b));
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=k;i++) cin>>b[i];
		
		for(int i=k;i<=n;i++) f[i]=-1e18;
		
		for(int i=1;i<=n;i++){
			int s1=a[i],s2=a[i],g=a[i];
			for(int j=i;j;j--){
				s1|=a[j];
				s2&=a[j];
				if(a[j]%g) g=gcd(a[j],g);
				
				if(i-j+1>=k) f[i]=max(f[i],f[j-1]+s1+s2+b[j]+g);
			}
		}
		
		cout<<f[n]<<endl;
	}
}
