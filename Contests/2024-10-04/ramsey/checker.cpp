#include<bits/stdc++.h>
#include "testlib.h"
#define LL long long
#define pb push_back
#define SZ(x) ((int)x.size()-1)
#define ms(a,b) memset(a,b,sizeof a)
#define F(i,a,b) for (int i=(a);i<=(b);++i)
#define DF(i,a,b) for (int i=(a);i>=(b);--i)
//#define mp make_pair
//#define OO(x) fixed<<setprecision(x)
using namespace std;
//mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
inline int read(){
	char ch=getchar(); int w=1,c=0;
	for(;!isdigit(ch);ch=getchar()) if (ch=='-') w=-1;
	for(;isdigit(ch);ch=getchar()) c=(c<<1)+(c<<3)+(ch^48);
	return w*c;
}
const int M=2010;
int k,n,c[M][M];
int s[]={0,2,5,16,45,139,416};
int full[]={0,6,10,13,20,23,28};
double func(double x){
	return pow(x,2*k);
}
double rat(double ans){
	return func(ans)/func(s[k]);
}
int main(int argc, char** argv) {
	registerTestlibCmd(argc, argv);
//	return 0;
//	cerr<<k<<" ????\n";
	k=inf.readInt(1,6);
	n=ouf.readInt();
	ensuref(n<=2000,"The graph is too large!");
	
	F(i,1,n-1){
		F(j,i+1,n) c[i][j]=ouf.readInt(0,k-1);
	}
	F(i,1,n){
		F(j,i+1,n){
			F(k,j+1,n){
				if (c[i][j]==c[i][k] && c[i][j]==c[j][k]){
					ensuref(0,"Invalid Construction!");
					break;
				} 
			}	
		}
	}
	double sc=full[k]*rat(n);
	sc=min(sc,full[k]*1.);
	quitp(sc, "ok,n=%d",n);
//	quitp(_pc(100,"ok\n");
//	quitf(_ok,"ok n=%lld\n",n);
	return 0;
}
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/

