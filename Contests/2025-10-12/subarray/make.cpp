#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

mt19937 rng(4649);
int a[N],oi[N],oj[N],len[N],t[N],n,m,q,lL,S;
vector<int> qry[N];
vector<int> b[N];

signed main(){
	cin>>n>>m>>q>>lL>>S;

	cout<<n<<' '<<m<<' '<<q<<endl;
	for(int i=1;i<=n;i++) a[i]=i;
	for(int i=1;i<=m;i++){
		oi[i]=rng()%n+1,oj[i]=rng()%n+1;
		if(oi[i]>oj[i]) swap(oi[i],oj[i]);
		cout<<oi[i]<<' '<<oj[i]<<endl;
	}
	for(int i=1;i<=q;i++) len[i]=lL;
	for(int i=1;i<=S-lL*q;i++){
		int p=rng()%q+1;
		len[p]=min(n,len[p]+1);
	}
	for(int i=1;i<=q;i++) qry[t[i]=rng()%(m+1)].push_back(i);
	for(int i=0;i<=m;i++,swap(a[oi[i]],a[oj[i]])){
		for(int j:qry[i]){
			int st=rng()%(n-len[j]+1)+1;
			b[j]=vector<int>(a+st,a+st+len[j]);
		}
	}

	for(int i=1;i<=q;i++){
		cout<<len[i]<<' ';
		for(int x:b[i]) cout<<x<<' ';cout<<endl;
	}

	ofstream fout(".ans");
	for(int i=1;i<=q;i++) fout<<t[i]<<endl;

	return 0;
}