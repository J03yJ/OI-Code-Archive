#include<bits/stdc++.h>
using namespace std;
#define int long long
#define For(i,j,k) for(int i=(j);i<=(k);i++)
#define Rof(i,j,k) for(int i=(j);i>=(k);i--)
#define N 200010
#define base 200001
int n,m,a[4][N],ans=0,c[2*N],tot;
struct que{
	int op,x,y,val;
	bool operator<(const que &p)const{
		if(x!=p.x) return x<p.x;
		return op<p.op;
	}
}q[400010];
void upd(int x){
	while(x<2*base) c[x]++,x+=x&(-x);
}
int qry(int x){
	int res=0;
	while(x) res+=c[x],x-=x&(-x);
	return res;
}
int calc(int x,int y,int z){
	int res=0;
	memset(c,0,sizeof(c)),tot=0;
	For(i,1,n){
		q[++tot]=(que){0ll,a[x][i]-a[y][i]+(x>y),a[y][i]-a[z][i]+(y>z),0ll};
		q[++tot]=(que){1ll,a[y][i]-a[x][i],a[z][i]-a[y][i],a[y][i]};
	}
	sort(q+1,q+tot+1);
	For(i,1,tot){
		if(q[i].op==0) upd(q[i].y+base);
		else res+=q[i].val*qry(q[i].y+base);
	}
	return res;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);
	cin>>m>>n;
	For(i,0,m-1) For(j,1,n) cin>>a[i][j];
	For(i,m,3) For(j,1,n) a[i][j]=a[i-m][j];
	For(i,0,3) For(j,1,n) ans+=2*n*a[i][j];
	For(i,0,3) For(j,0,3) For(k,0,3) if(i!=j&&j!=k&&k!=i) ans-=calc(i,j,k);
	cout<<ans;
}