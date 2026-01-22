#include<bits/stdc++.h>
using namespace std;

#define int long long

const int N=2e5+9;
const int p=998244353;

int qpow(int x,int y){
	int m=1;
	while(y){
		if(y&1) m=m*x%p;
		x=x*x%p;
		y>>=1;
	}
	return m;
}
inline int inv(int x){
	return qpow(x,p-2);
}

int a[N],b[N],c[N],n;
bool cmp(int x,int y){
	return a[x]<a[y];
}
void init_c(){
	for(int i=1;i<=n;i++) b[i]=i;
	sort(b+1,b+n+1,cmp);
	for(int i=1;i<=n;i++) c[i]=a[b[i]];
}

int pre[N],mul=1;
void init_pre(){
	pre[0]=1;
	for(int i=1;i<=n;i++){
		mul=mul*(c[i]-i+1)%p;
		if(c[i]==i) pre[i]=1;
		else pre[i]=pre[i-1]*inv(c[i]-i+1)%p*(c[i]-i)%p;
//		cout<<pre[i]<<endl;
	}
}

struct node{
	int l,r;
	int val,siz;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define val(x) tr[x].val
#define siz(x) tr[x].siz
void pushup(int x){
	val(x)=val(2*x)+val(2*x+1)%p;
	siz(x)=siz(2*x)+siz(2*x+1);
}
void build(int x,int l,int r){
	l(x)=l;r(x)=r;
	if(l==r) return ;
	int mid=l(x)+r(x)>>1;
	build(2*x,l,mid);
	build(2*x+1,mid+1,r);
	pushup(x);
}
void modify(int x,int pos,int k){
	if(l(x)==r(x)){
		val(x)=k;
		siz(x)=1;
		return ;
	}
	int mid=l(x)+r(x)>>1;
	if(pos<=mid) modify(2*x,pos,k);
	else modify(2*x+1,pos,k);
	pushup(x);
}
int query_val(int x,int l,int r){
	if(l<=l(x)&&r(x)<=r) return val(x);
	int ans=0,mid=l(x)+r(x)>>1;
	if(l<=mid) ans=(ans+query_val(2*x,l,r))%p;
	if(r>mid) ans=(ans+query_val(2*x+1,l,r))%p;
	return ans;
}
int query_siz(int x,int l,int r){
	if(l<=l(x)&&r(x)<=r) return siz(x);
	int ans=0,mid=l(x)+r(x)>>1;
	if(l<=mid) ans+=query_siz(2*x,l,r);
	if(r>mid) ans+=query_siz(2*x+1,l,r);
	return ans;
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]=min(a[i],n);
	
	init_c();
	init_pre();
	build(1,1,n);
	
	int ans=0;
	for(int i=n,lst=n;i;i--){
//		cout<<query_val(1,b[i]+1,n)<<' '<<query_val(1,1,b[i]-1)<<' '<<query_siz(1,1,b[i]-1)<<' '<<mul<<endl;
		ans=(ans+inv(2)*mul%p*(c[i]-i)%p*inv(pre[i])%p*query_val(1,b[i]+1,n)%p)%p;
		ans=(ans+mul*query_siz(1,1,b[i]-1)%p)%p;
		ans=(ans-inv(2)*mul%p*(c[i]-i)%p*inv(pre[i])%p*query_val(1,1,b[i]-1)%p+p)%p;
		modify(1,b[i],pre[i-1]*inv(c[i]-i+1)%p);
		if(c[i]==i) while(lst>i) modify(1,b[lst],0),lst--;
	}
	
	cout<<ans*inv(mul)%p<<endl;
	
	return 0;
}
