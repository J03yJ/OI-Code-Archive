// Expect 64pts

#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N=2e5+9;
ifstream fin("eye.in");
ofstream fout("eye.out");
#define cin fin
#define cout fout

int n,k,m;
int x[N],y[N],z[N],w[N];

// Solve 1D
int solve_1D(int *x,int n,int m){
//	cout<<x[n]<<' '<<x[1]<<endl;
	if(m==2) return x[n]-x[1];
	else if(m==3) return (x[n]-x[1])*2;
	else return (x[n]-x[1])*4;
}

//Solve 2D
int d1[N],d2[N];
pair<int,int> a;
int solve_2D(int *x,int *y,int n,int m){
	if(m==2){
		for(int i=1;i<=n;i++) d1[i]=x[i]+y[i],d2[i]=x[i]-y[i];
		sort(d1+1,d1+n+1);sort(d2+1,d2+n+1);
		return max(solve_1D(d1,n,m),solve_1D(d2,n,m));
	}else if(m==3){
		int ans=0,mxx=0,mnx=1e18,mxy=0,mny=1e18;
		for(int i=1;i<=n;i++){
			mxx=max(mxx,x[i]);
			mnx=min(mnx,x[i]);
			mxy=max(mxy,y[i]);
			mny=min(mny,y[i]);
		}
		for(int i=1;i<=n;i++){
			ans=max(ans,2*(max(abs(mxx-x[i]),abs(mnx-x[i]))+max(abs(mxy-y[i]),abs(mny-y[i]))));
		}
		return ans;
	}
}

//Solve 3D
int d3[N],z3[N],p3[N],D3[N];
bool Cmp3(int x,int y){return d3[x]<d3[y];}
int d4[N],z4[N],p4[N],D4[N];
bool Cmp4(int x,int y){return d4[x]<d4[y];}
int solve_3D(int *x,int *y,int *z,int n,int m){
	if(m==2){
		int ans=0;
		for(int i=1;i<=n;i++) d3[i]=x[i]+y[i],p3[i]=i;
		sort(p3+1,p3+n+1,Cmp3);
		for(int i=1;i<=n;i++) D3[i]=d3[p3[i]],z3[i]=z[p3[i]];
		ans=max(ans,solve_2D(D3,z3,n,m));
		for(int i=1;i<=n;i++) d4[i]=x[i]-y[i],p4[i]=i;
		sort(p4+1,p4+n+1,Cmp4);
		for(int i=1;i<=n;i++) D4[i]=d4[p4[i]],z4[i]=z[p4[i]];
		ans=max(ans,solve_2D(D4,z4,n,m));
		return ans;
	}else{
		srand(time(0)+9283);
		int ans=0;
		#define dis(i,j) (abs(x[i]-x[j])+abs(y[i]-y[j])+abs(z[i]-z[j]))
		for(int i=1;i<=1e7;i++){
			int a=rand()%n+1,b=rand()%n+1,c=rand()%n+1;
			ans=max(ans,dis(a,b)+dis(a,c)+dis(b,c));
		}
		#undef dis
		return ans;
	}
}

//Solve 4D
int d5[N],z5[N],w5[N],p5[N],D5[N];
bool Cmp5(int x,int y){return d5[x]<d5[y];}
int d6[N],z6[N],w6[N],p6[N],D6[N];
bool Cmp6(int x,int y){return d6[x]<d6[y];}
int solve_4D(int *x,int *y,int *z,int *w,int n,int m){
	if(m==2){
		int ans=0;
		for(int i=1;i<=n;i++) d5[i]=x[i]+y[i],p5[i]=i;
		sort(p5+1,p5+n+1,Cmp5);
		for(int i=1;i<=n;i++) D5[i]=d5[p5[i]],z5[i]=z[p5[i]],w5[i]=w[p5[i]];
		ans=max(ans,solve_3D(D5,z5,w5,n,m));
		for(int i=1;i<=n;i++) d6[i]=x[i]-y[i],p6[i]=i;
		sort(p6+1,p6+n+1,Cmp6);
		for(int i=1;i<=n;i++) D6[i]=d6[p6[i]],z6[i]=z[p6[i]],w6[i]=w[p6[i]];
		ans=max(ans,solve_3D(D6,z6,w6,n,m));
		return ans;
	}else{
		srand(time(0)+9283);
		int ans=0;
		#define dis(i,j) (abs(x[i]-x[j])+abs(y[i]-y[j])+abs(z[i]-z[j])+abs(w[i]-w[j]))
		for(int i=1;i<=1e7;i++){
			int a=rand()%n+1,b=rand()%n+1,c=rand()%n+1,d=rand()%n+1;
			ans=max(ans,dis(a,b)+dis(a,c)+dis(a,d)+dis(b,c)+dis(b,d)+dis(c,d));
		}
		return ans;
	}
}

signed main(){
	cin>>n>>k>>m;
	if(k==1){
		for(int i=1;i<=n;i++) cin>>x[i];
		sort(x+1,x+n+1);
		cout<<solve_1D(x,n,m)<<endl;
	}else if(k==2){
		for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
		cout<<solve_2D(x,y,n,m)<<endl;
	}else if(k==3){
		for(int i=1;i<=n;i++) cin>>x[i]>>y[i]>>z[i];
		cout<<solve_3D(x,y,z,n,m)<<endl;
	}else{
		for(int i=1;i<=n;i++) cin>>x[i]>>y[i]>>z[i]>>w[i];
		cout<<solve_4D(x,y,z,w,n,m)<<endl;
//		
//		int ans=0,a,b;
//		for(int i=1;i<=n;i++){
//			for(int j=i;j<=n;j++){
//				int k=abs(x[i]-x[j])+abs(y[i]-y[j])+abs(z[i]-z[j])+abs(w[i]-w[j]);
//				if(k>ans) ans=k,a=i,b=j;
//			}
//		}
//		cout<<ans<<endl;
//		cout<<x[a]<<' '<<y[a]<<" "<<z[a]<<' '<<w[a]<<endl;
//		cout<<x[b]<<' '<<y[b]<<" "<<z[b]<<' '<<w[b]<<endl;
//		cout<<x[a]+y[a]+z[a]+w[a]<<' '<<x[b]+y[b]+z[b]+w[b]<<endl;
//		cout<<x[a]+y[a]+z[a]-w[a]<<' '<<x[b]+y[b]+z[b]-w[b]<<endl;
//		cout<<x[a]+y[a]-z[a]+w[a]<<' '<<x[b]+y[b]-z[b]+w[b]<<endl;
//		cout<<x[a]+y[a]-z[a]-w[a]<<' '<<x[b]+y[b]-z[b]-w[b]<<endl;
//		cout<<x[a]-y[a]+z[a]+w[a]<<' '<<x[b]-y[b]+z[b]+w[b]<<endl;
//		cout<<x[a]-y[a]+z[a]-w[a]<<' '<<x[b]-y[b]+z[b]-w[b]<<endl;
//		cout<<x[a]-y[a]-z[a]+w[a]<<' '<<x[b]-y[b]-z[b]+w[b]<<endl;
//		cout<<x[a]-y[a]-z[a]-w[a]<<' '<<x[b]-y[b]-z[b]-w[b]<<endl;
	}
	return 0;
}
