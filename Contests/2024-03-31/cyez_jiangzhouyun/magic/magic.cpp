#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

ifstream fin("magic.in");
ofstream fout("magic.out");
#define cin fin
#define cout fout

const int p=998244353;
const int N=1e5+9;

struct node{
	int l,r;
	int dat[32],tag[5];
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag

void add(int x,int k,int val){
	if(!val) return ;
//	cout<<x<<' '<<k<<' '<<val<<endl;
	for(int i=0;i<32;i++){
		if((i>>k)&1){
//			cout<<i<<' '<<dat(x)[i]<<endl;
			dat(x)[i]=(dat(x)[i^(1<<k)]*val%p+dat(x)[i])%p;
		}
	}
}
void pushup(int x){
	for(int i=0;i<32;i++) dat(x)[i]=(dat(2*x)[i]+dat(2*x+1)[i])%p;
	for(int i=0;i<5;i++) add(x,i,tag(x)[i]);
}
void pushdown(int x){
	if(l(x)==r(x)) return ;
	for(int k=0;k<5;k++){
		if(!tag(x)[k]) continue ;
		add(2*x,k,tag(x)[k]);
		add(2*x+1,k,tag(x)[k]);
		tag(2*x)[k]=(tag(2*x)[k]+tag(x)[k])%p;
		tag(2*x+1)[k]=(tag(2*x+1)[k]+tag(x)[k])%p;
		tag(x)[k]=0;
	}
}

int a[N][5];
void build(int x,int l,int r){
	l(x)=l;r(x)=r;
	if(l(x)==r(x)){
		for(int i=0;i<32;i++){
			dat(x)[i]=1;
			for(int k=0;k<5;k++){
				if((i>>k)&1) dat(x)[i]=(dat(x)[i]*a[l(x)][k])%p;
			}
		}
		return ;
	}
	int mid=l(x)+r(x)>>1;
	build(2*x,l,mid);
	build(2*x+1,mid+1,r);
	pushup(x);
}
void modify(int x,int l,int r,int k,int val){
	pushdown(x);
	if(l<=l(x)&&r(x)<=r){
		add(x,k,val);
		tag(x)[k]=(tag(x)[k]+val)%p;
		return ;
	}
	int mid=l(x)+r(x)>>1;
	if(l<=mid) modify(2*x,l,r,k,val);
	if(r>mid) modify(2*x+1,l,r,k,val);
	pushup(x);
}
int ask(int x,int l,int r,int k){
	pushdown(x);
	if(l<=l(x)&&r(x)<=r) return dat(x)[k];
	int mid=l(x)+r(x)>>1,ans=0;
	if(l<=mid) ans=ask(2*x,l,r,k);
	if(r>mid) ans=(ans+ask(2*x+1,l,r,k))%p;
	return ans;
}

signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=0;j<5;j++) cin>>a[i][j];
	}
	build(1,1,n);
	
	int q;
	cin>>q;
	while(q--){
		char op;
		int l,r;
		cin>>op>>l>>r;
		if(op=='Q'){
			cout<<ask(1,l,r,31)<<endl;
			continue ;
		}
		int val;
		cin>>val;
		
		int k=0;
		if(op=='J') k=0;
		if(op=='M') k=1;
		if(op=='S') k=2;
		if(op=='H') k=3;
		if(op=='T') k=4;
		
		modify(1,l,r,k,val);
		
//		prt(1);
	}
	
	return 0;
}
