#include "testlib.h"
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rep(i, j, k) for(int i=j;i<=k;++i)
#define rep1(i, j, k) for(int i=k;i>=j;--i)
#define pii pair<int, int>
#define pb push_back
#define ft first
#define sd second

using namespace std;

const int N=2e3+5;
int n, m;
int a[N][N];
string s;

bool vis[N][N];

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    
    int t = inf.readInt();
    
    bool flg=1;
    
    int cnt=0;
    
    while(t--){
	    string op = ouf.readToken();
	    string rp = ans.readToken();
	    
	    if(op!=rp) quitf(_wa, "The answer is wrong");
		
	    int n = inf.readInt();
		int m = inf.readInt();
	    
	   	rep(i, 1, n){
	    	s = inf.readToken();
	    	int j=0;
	    	for(char c : s){
	    		a[i][++j]=c-'0';
			}
		}
		
		if(op=="NO") continue;
		
		int q = ouf.readInt();
	
		if((cnt+=q)>4000000) quitf(_pe, "The operators are too many");
		
		while(q--){
			int x = ouf.readInt();
			int y = ouf.readInt();
			
			if(x<1 || y<1 || x>=n || y>=m) quitf(_pe, "The operations do not follow the specification");
			
			int d = ouf.readInt();
			
			if(d<0 || d>1) quitf(_pe, "The operations do not follow the specification");
			
			if(!d){
				int t=a[x][y];
				a[x][y]=a[x][y+1];
				a[x][y+1]=a[x+1][y+1];
				a[x+1][y+1]=a[x+1][y];
				a[x+1][y]=t;
			}else{
				int t=a[x][y];
				a[x][y]=a[x+1][y];
				a[x+1][y]=a[x+1][y+1];
				a[x+1][y+1]=a[x][y+1];
				a[x][y+1]=t;
			}
		}
		
		vis[0][1]=1;
		rep(i, 1, n) rep(j, 1, m){
			vis[i][j]=a[i][j]&(vis[i][j-1]|vis[i-1][j]);
		}
		
		if(!vis[n][m]) flg=0;
	}
	
	if(flg) quitf(_ok, "The answer is correct");
	else quitp(0.3, "The answer is not correct");
	
	return 0;
	
}
