#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=2e3+9;
int a[N],b[N],c[N],n,m;
mt19937 rnd(time(0));
bool check(int k){
	for(int o=1;o<=3000;o++){
		for(int i=1;i<=n;i++) c[i]=a[i];
		shuffle(c+1,c+n+1,rnd);
		int cnt=0;
		for(int i=k;i;i--){
			for(int j=1;j<=n;j++){
				if(c[j]>=b[i]){
					cnt++;
					c[j]-=b[i];
					break ;
				}
			}
		}
		if(cnt>=k) return 1;
	}
	return 0;
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	cin>>m;
	for(int i=1;i<=m;i++) cin>>b[i];
	sort(b+1,b+m+1);
	int l=0,r=m+1;
	while(l+1<r){
		int mid=l+r>>1;
		if(check(mid)) l=mid;
		else r=mid;
	}
	cout<<l<<endl;
	return 0;
}
