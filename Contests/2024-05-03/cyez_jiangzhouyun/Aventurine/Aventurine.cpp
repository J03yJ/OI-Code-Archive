#include<bits/stdc++.h>
using namespace std;
#define int long long

ifstream fin("Aventurine.in");
ofstream fout("Aventurine.out");
#define cin fin
#define cout fout

const int N=2e5+9;
int n;
namespace A{
	int a[N],b[N],c[N];
	bool ch[N];
	int p[25];
	void solve(){
		for(int i=1;i<=n;i++) cin>>a[i]>>b[i]>>c[i];
		int ans=0,mn=1e18;
		for(int sta=0;sta<(1<<n);sta++){
			for(int i=0;i<n;i++){
				if(sta>>i&1) ch[i+1]=1;
				else ch[i+1]=0;
			}
			memset(p,0,sizeof(p));
			int cnt=0;
			for(int i=1;i<=n;i++){
				if(!ch[i]) continue ;
				int k=a[i];
				for(int i=24;~i;i--){
					if(k>>i&1){
						if(!p[i]){
							p[i]=k;
							cnt++;
//							cout<<i<<' '<<k<<endl;
							break ;
						}
						else k^=p[i];
					}
					if(!k) break ;
				}
			}
//			cout<<cnt<<endl;
			if(cnt<ans) continue ;
			int cst=0,bst=0;
			for(int i=1;i<=n;i++) if(ch[i]) cst+=c[i],bst+=b[i];
			if(ans<cnt) ans=cnt,mn=cst*bst;
			else mn=min(mn,cst*bst);
//			cout<<sta<<' '<<cnt<<' '<<cst<<' '<<bst<<endl;
		}
		cout<<mn<<endl;
	}
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		if(n<=20) A::solve();
	}
}
