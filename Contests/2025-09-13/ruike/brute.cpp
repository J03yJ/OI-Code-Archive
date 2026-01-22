#include<bits/stdc++.h>

using namespace std;

ifstream fin("ruike.in");
ofstream fout("brute.out");
#define cin fin
#define cout fout
#define endl '\n'

#define int ll
using ll=long long;
const int mod=998244353;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
	int res=1;
	while(y){
		if(y&1) MulAs(res,x);
		MulAs(x,x);
		y>>=1;
	}
	return res;
}
#define Inv(x) QPow(x,mod-2)

const int INV2=Inv(2);
const int INV6=Inv(6);
inline int C1(int x){return x%mod;}
inline int C2(int x){return Mul(Mul(x,Sub(x,1)),INV2);}
inline int C3(int x){return Mul(Mul(Mul(x,Sub(x,1)),Sub(x,2)),INV6);}

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		vector<array<int,4>> p(n);
		for(auto &x:p) for(int k:{0,1,2,3}) cin>>x[k];

		vector<int> xval({1,int(1e9+1)}),yval({1,int(1e9+1)});
		for(auto x:p) for(int k:{0,1,2,3}) (k&1?yval:xval).push_back(x[k]+(k>>1));
		sort(xval.begin(),xval.end());
		sort(yval.begin(),yval.end());
		xval.erase(unique(xval.begin(),xval.end()),xval.end());
		yval.erase(unique(yval.begin(),yval.end()),yval.end());
		int mx=xval.size()-1,my=yval.size()-1;

		for(auto &x:p){
			x[0]=lower_bound(xval.begin(),xval.end(),x[0])-xval.begin();
			x[1]=lower_bound(yval.begin(),yval.end(),x[1])-yval.begin();
			x[2]=upper_bound(xval.begin(),xval.end(),x[2])-xval.begin()-1;
			x[3]=upper_bound(yval.begin(),yval.end(),x[3])-yval.begin()-1;
		}

		int ans=0;
		#define Chk(x,l,r) ((l)<=(x)&&(x)<=(r))
		#define Lx(i) (xval[(i)+1]-xval[i])
		#define Ly(i) (yval[(i)+1]-yval[i])
		for(int i=0;i<mx;i++){
			for(int j=i;j<mx;j++){
				for(int k=j;k<mx;k++){
					bool flag=1;
					for(int t=0;flag&&t<n;t++){
						flag&=Chk(i,p[t][0],p[t][2])|Chk(j,p[t][0],p[t][2])|Chk(k,p[t][0],p[t][2]);
					}
					if(!flag) continue ;
					if(i==j&&j==k) AddAs(ans,C3(Lx(i)));
					else if(i==j) AddAs(ans,Mul(C2(Lx(i)),C1(Lx(k))));
					else if(j==k) AddAs(ans,Mul(C1(Lx(i)),C2(Lx(j))));
					else AddAs(ans,Mul(C1(Lx(i)),Mul(C1(Lx(j)),C1(Lx(k)))));
				}
			}
		}
		vector<int> yres(my,0);
		for(int i=0;i<mx;i++){
			for(int j=i;j<mx;j++){
				for(int k=0;k<my;k++){
					bool flag=1;
					for(int t=0;flag&&t<n;t++){
						flag&=Chk(i,p[t][0],p[t][2])|Chk(j,p[t][0],p[t][2])|Chk(k,p[t][1],p[t][3]);
					}
					if(!flag) continue ;
					int tmp=ans;
					if(i==j) AddAs(ans,Mul(C2(Lx(i)),C1(Ly(k))));
					else AddAs(ans,Mul(C1(Lx(i)),Mul(C1(Lx(j)),C1(Ly(k)))));
					tmp=Sub(ans,tmp);
					AddAs(yres[k],tmp);
				}
			}
		}
		for(int i=0;i<my;i++){
			cerr<<"Y : "<<yval[i]<<" ~ "<<yval[i+1]<<" = "<<yres[i]<<endl;
		}
		vector<int> xres(mx,0);
		for(int i=0;i<mx;i++){
			for(int j=0;j<my;j++){
				for(int k=j;k<my;k++){
					bool flag=1;
					for(int t=0;flag&&t<n;t++){
						flag&=Chk(i,p[t][0],p[t][2])|Chk(j,p[t][1],p[t][3])|Chk(k,p[t][1],p[t][3]);
					}
					int tmp=ans;
					if(!flag) continue ;
					if(j==k) AddAs(ans,Mul(C1(Lx(i)),C2(Ly(j))));
					else AddAs(ans,Mul(C1(Lx(i)),Mul(C1(Ly(j)),C1(Ly(k)))));
					tmp=Sub(ans,tmp);
					AddAs(xres[i],tmp);
				}
			}
		}
		for(int i=0;i<mx;i++){
			cerr<<"X : "<<xval[i]<<" ~ "<<xval[i+1]<<" = "<<xres[i]<<endl;
		}
		for(int i=0;i<my;i++){
			for(int j=i;j<my;j++){
				for(int k=j;k<my;k++){
					bool flag=1;
					for(int t=0;flag&&t<n;t++){
						flag&=Chk(i,p[t][1],p[t][3])|Chk(j,p[t][1],p[t][3])|Chk(k,p[t][1],p[t][3]);
					}
					if(!flag) continue ;
					if(i==j&&j==k) AddAs(ans,C3(Ly(i)));
					else if(i==j) AddAs(ans,Mul(C2(Ly(i)),C1(Ly(k))));
					else if(j==k) AddAs(ans,Mul(C1(Ly(i)),C2(Ly(j))));
					else AddAs(ans,Mul(C1(Ly(i)),Mul(C1(Ly(j)),C1(Ly(k)))));
				}
			}
		}

		cout<<ans<<endl;
	}

	return 0;
}