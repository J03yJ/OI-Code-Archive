#include<bits/stdc++.h>
using namespace std;

const int N=5e6+9;
int a[N],D[N],d[N];

int n;
int dist(int x,int y){
	if(x>y) swap(x,y);
	return min(y-x,n+x-y);
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],D[i]=a[i]-a[i-1];
	D[1]=a[1]-a[n];
	
	for(int i=1;i<=n;i++) cin>>d[i];
	set<int> pos,neg;
	for(int i=1;i<=n;i++){
		if(d[i]<0) neg.insert(i),neg.insert(i+n);
		else if(d[i]) pos.insert(i);
	}
	while(pos.size()&&neg.size()){
		pair<int,int> now=make_pair(0,1e9);
		for(int x:pos){
			auto it=neg.upper_bound(x);
			int y=*it;
			if(it!=neg.begin()){
				int z=*(--it);
				if(dist(z)<dist(y)) y=z;
			}
		}
	}
}
