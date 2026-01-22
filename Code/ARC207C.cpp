#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;
const int T=3e1+9;
const int inf=1e9+7;

struct Node{
	int l,r;
	int dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat

inline void PushUp(int x){dat(x)=max(dat(x<<1),dat(x<<1|1));}
inline void Build(int x,int l,int r){
	l(x)=l,r(x)=r;
	if(l(x)==r(x)) return dat(x)=l(x)?-inf:0,void();
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void ChMax(int x,int pos,int k){
	if(l(x)==r(x)) return dat(x)=max(dat(x),k),void();
	int mid=l(x)+r(x)>>1;
	if(pos<=mid) ChMax(x<<1,pos,k);
	else ChMax(x<<1|1,pos,k);
	PushUp(x);
}
inline int Query(int x,int l,int r){
	if(l<=l(x)&&r(x)<=r) return dat(x);
	int mid=l(x)+r(x)>>1;
	if(r<=mid) return Query(x<<1,l,r);
	else if(l>mid) return Query(x<<1|1,l,r);
	else return max(Query(x<<1,l,r),Query(x<<1|1,l,r));
}

int a[N],pos[N][T],val[N][T],f[N][T],cur[N],p[N],cnt[N],n;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	for(int i=1;i<=n;i++){
		pos[i][0]=i,val[i][0]=a[i];
		for(int j=0;j<=cnt[i-1];j++){
			if((a[i]|val[i-1][j])>(val[i][cnt[i]])){
				cnt[i]++;
				val[i][cnt[i]]=a[i]|val[i-1][j];
				pos[i][cnt[i]]=pos[i-1][j];
			}
		}
	}

	Build(1,0,n);
	vector<array<int,4>> tmp;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=cnt[i];j++){
			tmp.push_back({val[i][j],i,pos[i][j+1],pos[i][j]-1});
		}
	}
	sort(tmp.begin(),tmp.end());
	for(auto t:tmp) ChMax(1,t[1],Query(1,t[2],t[3])+1);

	cout<<Query(1,0,n)<<endl;

	return 0;
}