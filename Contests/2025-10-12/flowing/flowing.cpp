#include<bits/stdc++.h>

using namespace std;

ifstream fin("flowing.in");
ofstream fout("flowing.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=3e5+9;

int c[N],a[N],fa[N],n,q;

int f[N];
inline int Find(int x){return x==f[x]?x:f[x]=Find(f[x]);}
inline void Merge(int x,int y){f[Find(y)]=Find(x);}

signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>c[i];
	
	vector<int> stk;
	for(int i=n;i>=1;i--){
		while(stk.size()&&c[stk.back()]<=c[i]) stk.pop_back();
		if(!stk.size()) fa[i]=0;
		else fa[i]=stk.back();
		stk.push_back(i);
	}
	iota(f,f+n+1,0);

	while(q--){
		char op;
		cin>>op;
		if(op=='+'){
			int x,t;
			cin>>x>>t;
			x=Find(x);
			while(x){
				if(t<=c[x]-a[x]){
					a[x]+=t;
					break ;
				}
				t-=c[x]-a[x],a[x]=c[x];
				Merge(fa[x],x);
				x=Find(fa[x]);
			}
		}else if(op=='?'){
			int x;
			cin>>x;
			cout<<a[x]<<endl;
		}
	}

	return 0;
}