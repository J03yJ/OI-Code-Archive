#include<bits/stdc++.h>

using namespace std;

ifstream fin("b.in");
ofstream fout("b.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e5+9;

int a[N],n,q;

signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];

	while(q--){
		int op;
		cin>>op;
		if(op==1){
			int x,y;
			cin>>x>>y;
			a[x]=y;
		}else if(op==2){
			int x;
			cin>>x;
			
			int cur=a[x];
			for(int i=x+1;i<=n;i++) cur+=(a[i]<=cur);

			cout<<n-cur<<endl;
		}
	}

	return 0;
}