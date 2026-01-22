#include<bits/stdc++.h>
//#define feyn
#define int long long
using namespace std;
const int N=1000010;
const int mod=1e9+7;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

int m,n,a[N],fail[N];
int f[N],g[N];

signed main(){
	
	freopen("perform.in", "r", stdin);
	freopen("perform.out", "w", stdout);
	read(n);read(m);
	for(int i=1,j=0;i<=m;i++){
		read(a[i]);if(i==1)continue;
		while(j&&a[j+1]!=a[i])j=fail[j];
		if(a[j+1]==a[i])j++;fail[i]=j;
	}
	f[1]=n;
	for(int i=2;i<=m;i++){
		//核心代码
		g[i-1]=g[fail[i-1]]+f[fail[i-1]+1]-f[fail[i]];//从fail那里继承，然后加上缺失的部分丢掉不用的部分
		f[i]=n*(f[i-1]+1)-g[i-1];//和上面的式子一样更新即可
		//核心代码
		f[i]%=mod,g[i]%=mod;
	}
	for(int i=1;i<=m;i++)printf("%lld\n",(f[i]%mod+mod)%mod);
	
	return 0;
}