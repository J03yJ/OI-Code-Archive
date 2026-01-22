#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=3e5+9;

int l[N],r[N],b[N],c[N],n,m;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>l[i]>>r[i];

	vector<int> p(n);
	iota(p.begin(),p.end(),1);
	sort(p.begin(),p.end(),[](int i,int j){return l[i]<l[j];});

	priority_queue<array<int,2>> q1,q2;
	for(int i:p){
		if(q1.size()&&l[i]>-q1.top()[0]){
			int j=q1.top()[1];
			q1.pop();
			b[i]=j,b[j]=i;
			q2.push({-r[i],i});
		}else if(q2.size()&&r[i]>-q2.top()[0]){
			int j=q2.top()[1],k=b[j];
			q2.pop();
			b[i]=k,b[k]=i,b[j]=0;
			q2.push({-r[i],i});
			q1.push({-r[j],j});
		}else q1.push({-r[i],i});
	}

	for(int i=1;i<=n;i++) if(!c[i]&&b[i]&&m) c[i]=c[b[i]]=m--;
	for(int i=1;i<=n;i++) if(!c[i]&&m) c[i]=m--;

	for(int i=1;i<=n;i++) cout<<c[i]<<' ';cout<<endl;

	return 0;
}