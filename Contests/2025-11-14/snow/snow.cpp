#include<bits/stdc++.h>

using namespace std;

ifstream fin("snow.in");
ofstream fout("snow.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;

int a[N],tr[N],n;
inline void Add(int x,int k){while(x<=n) tr[x]+=k,x+=x&-x;}
inline int Ask(int x){int sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}
inline int Ask(int l,int r){return Ask(r)-Ask(l-1);}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	int g=0;
	for(int i=1;i<=n;i++) g=__gcd(g,abs(i-a[i]));
	for(int i=1;i<=n;i++){
		if(g%i) cout<<-1<<endl;
		else{
			ll res=0;
			for(int r=1;r<=i;r++){
				for(int k=r;k<=n;k+=i){
					res+=Ask(a[k],n);
					Add(a[k],1);
				}
				for(int k=r;k<=n;k+=i) Add(a[k],-1);
			}
			cout<<res<<endl;
		}
	}

	return 0;
}