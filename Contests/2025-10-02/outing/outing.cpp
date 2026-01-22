#include<bits/stdc++.h>

using namespace std;

ifstream fin("outing.in");
ofstream fout("outing.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e5+9;
const int B=60;

struct Node{
	int son[2],siz;
}tr[N<<6];
#define son(x,k) tr[x].son[k]
#define siz(x) tr[x].siz

ll a[N],ans;
int cnt=1,root=1;
inline int Allc(){return ++cnt;}
inline void Insert(ll x,int k){
	int u=root;
	for(int i=0;i<B;i++){
		ans^=(siz(u)>>1&1)*(1ll<<i);
		siz(u)+=k;
		ans^=(siz(u)>>1&1)*(1ll<<i);
		if(!son(u,x>>i&1)) son(u,x>>i&1)=Allc();
		u=son(u,x>>i&1);
	}
	siz(u)+=k;
}

int n;

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],ans^=a[i];

	for(int i=1;i<=n;i++) Insert(a[i],1);
	for(int i=1;i<=n;i++){
		Insert(a[i],-1);
		cout<<(ans^a[i])<<' ';
		Insert(a[i],1);
	}

	cout<<endl;
	
	return 0;
}