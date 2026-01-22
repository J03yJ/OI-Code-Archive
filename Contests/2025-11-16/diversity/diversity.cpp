#include<bits/stdc++.h>

using namespace std;

ifstream fin("diversity.in");
ofstream fout("diversity.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e3+9;

int v[N],w[N],typ[N],lim[N],n,m,c;
vector<int> o[N];
vector<ll> f[N];

signed main(){
	cin>>n>>m>>c;
	for(int i=1;i<=n;i++) cin>>v[i]>>w[i]>>typ[i],o[typ[i]].push_back(i);
	for(int i=1;i<=c;i++) cin>>lim[i];

	for(int i=1;i<=c;i++){
		f[i]={0};
		for(int j:o[i]) f[i].resize(f[i].size()+w[j],0);
		for(int j:o[i]){
			for(int k=f[i].size()-1;k>=w[j];k--){
				f[i][k]=max(f[i][k],f[i][k-w[j]]+v[j]);
			}
		}
		if(lim[i]+1<f[i].size()) f[i].resize(lim[i]+1);
	}
	vector<ll> g={0};
	for(int i=1;i<=c;i++){
		vector<ll> h(min(int(g.size()+f[i].size()-1),m+1),0);
		for(int p=0;p<f[i].size();p++){
			for(int q=0;q<g.size()&&p+q<h.size();q++){
				h[p+q]=max(h[p+q],g[q]+f[i][p]);
			}
		}
		g=h;
	}

	cout<<g[min(m,(int)g.size()-1)]<<endl;

	return 0;
}