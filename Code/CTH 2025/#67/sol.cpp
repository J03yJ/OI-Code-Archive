#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=6e5+9;
const int inf=1e9+7;

int a[N],rk[N],cnt[4][N],p[4][N],n;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	int x=inf,y=inf,xy=inf,lx=inf,ly=inf,lxy=inf;
	for(int i=1;i<=n;i++){
		for(int j:{1,2,3}) cnt[j][i]=cnt[j][i-1];
		p[a[i]][rk[i]=++cnt[a[i]][i]]=i;
	}
	x=y=xy=min(cnt[1][n],min(cnt[2][n],cnt[3][n]));
	for(int i=1;i<=n;i++){
		lx=min(lx,-cnt[2][i-1]+cnt[1][i-1]);
		ly=min(ly,-cnt[2][i-1]+cnt[3][i-1]);
		lxy=min(lxy,-cnt[2][i-1]+cnt[1][i-1]+cnt[3][i-1]);
		x=min(x,lx+cnt[2][i]-cnt[3][i]+cnt[3][n]);
		y=min(y,ly+cnt[2][i]-cnt[1][i]+cnt[1][n]);
		xy=min(xy,lxy+cnt[2][i]-cnt[3][i]+cnt[3][n]-cnt[1][i]+cnt[1][n]);
	}
	xy=min(xy,x+y),x=min(x,xy),y=xy-x;

	cout<<x+y<<endl;
	priority_queue<array<int,2>> q;
	for(int i=1;i<=n;i++){
		if(a[i]==1){
			if(rk[i]<=x) q.push({-p[3][cnt[3][n]-(x-rk[i]+1)+1],-i});
		}else if(a[i]==3){
			if(rk[i]<=y) q.push({-p[1][cnt[1][n]-(y-rk[i]+1)+1],-i});
		}else if(a[i]==2){
			if(q.size()){
				cout<<-q.top()[1]-1<<' '<<i-1<<' '<<-q.top()[0]-1<<endl;
				q.pop();
			}
		}
	}

	return 0;
}