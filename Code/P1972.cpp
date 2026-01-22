#include<bits/stdc++.h>
using namespace std;

#define int long long

const int N=1e6+9;

struct node{
	int l,r;
	int dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat

void pushup(int x){
	dat(x)=dat(2*x)+dat(2*x+1);
}
void build(int x,int l,int r){
	dat(x)=0;
	l(x)=l;r(x)=r;
	if(l==r) return ;
	int mid=l(x)+r(x)>>1;
	build(2*x,l,mid);
	build(2*x+1,mid+1,r);
}
void modify(int x,int pos,int k){
	if(l(x)==r(x)){
		dat(x)=k;
		return ;
	}
	int mid=l(x)+r(x)>>1;
	if(pos<=mid) modify(2*x,pos,k);
	else modify(2*x+1,pos,k);
	pushup(x);
}
int query(int x,int l,int r){
	if(l<=l(x)&&r(x)<=r) return dat(x);
	int ans=0,mid=l(x)+r(x)>>1;
	if(l<=mid) ans+=query(2*x,l,r);
	if(r>mid) ans+=query(2*x+1,l,r);
	return ans;
}

int a[N];
int l[N],r[N],p[N],ans[N];
bool cmp(int x,int y){
	return r[x]<r[y];
}

int c[N];

signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	
	build(1,1,n);
	
	int m;
	cin>>m;
	for(int i=1;i<=m;i++) cin>>l[i]>>r[i],p[i]=i;
	sort(p+1,p+m+1,cmp);
	
	for(int i=1,j=1;i<=n;i++){
		if(c[a[i]]) modify(1,c[a[i]],0);
		modify(1,i,1);
		c[a[i]]=i;
		for(;j<=m&&r[p[j]]==i;j++){
			ans[p[j]]=query(1,l[p[j]],r[p[j]]);
		}
	}
	
	for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
}
