#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e3+9;

vector<array<int,2>> e[N];
int p[N],l[N],r[N],c[N],h[N],n;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=1;i<=2*n;i++){
		cin>>p[i];
		swap(l[p[i]],r[p[i]]);
		r[p[i]]=i;
	}

	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j) continue ;
			if(l[i]>l[j]) continue ;
			if(r[i]<l[j]) continue ;
			if(r[i]<r[j]){
				e[l[j]].push_back({r[i],1});
				e[r[i]].push_back({l[j],1});
			}else{
				e[l[j]].push_back({r[j],0});
				e[r[j]].push_back({l[j],0});
			}
		}
	}

	memset(c,-1,sizeof c);
	queue<int> q;
	for(int i=1;i<=2*n;i++){
		if(!~c[i]){
			c[i]=0;
			q.push(i);
			while(q.size()){
				int x=q.front();
				q.pop();
				for(auto p:e[x]){
					int w=c[x]^p[1];
					if(~c[p[0]]){
						if(c[p[0]]!=w){
							cout<<"NO"<<endl;
							return 0;
						}
					}else{
						c[p[0]]=w;
						q.push(p[0]);
					}
				}
			}
		}
	}

	for(int i=1;i<=2*n;i++){
		if(i!=r[p[i]]) continue ;
		for(int j=c[l[p[i]]]==c[r[p[i]]]?l[p[i]]:1;j<=r[p[i]];j++) h[p[i]]=max(h[p[i]],h[p[j]]);
		h[p[i]]++;
	}

	cout<<"YES"<<endl;
	for(int i=1;i<=n;i++){
		if(!c[l[i]]&&!c[r[i]]) cout<<3<<" U "<<h[i]<<" R "<<r[i]-l[i]<<" D "<<h[i]<<endl;
		else if(!c[l[i]]&&c[r[i]]) cout<<5<<" U "<<h[i]<<" L "<<l[i]+h[i]<<" D "<<2*h[i]<<" R "<<h[i]+r[i]<<" U "<<h[i]<<endl;
		else if(c[l[i]]&&!c[r[i]]) cout<<5<<" D "<<h[i]<<" L "<<l[i]+h[i]<<" U "<<2*h[i]<<" R "<<h[i]+r[i]<<" D "<<h[i]<<endl;
		else cout<<3<<" D "<<h[i]<<" R "<<r[i]-l[i]<<" U "<<h[i]<<endl;
	}

	return 0;
}