#include<bits/stdc++.h>
using namespace std;

ifstream fin("blackhole.in");
ofstream fout("blackhole.out");
#define cin fin
#define cout fout

const int N=1e3+9;
int a[N][N];
int c[N+N][N+N],sm[N+N][N+N];
#define C(x,y) c[x+N][y+N]
#define S(x,y) sm[x+N][y+N]

int main(){
	int T;
	cin>>T;
	while(T--){
		int n,m,k;
		cin>>n>>m>>k;
		string s;
		cin>>s;
		int x=0,y=0;
		int mxx=0,mnx=0,mxy=0,mny=0;
		C(0,0)=1;
		for(int i=0;i<s.size();i++){
			if(s[i]=='U') x--;
			else if(s[i]=='D') x++;
			else if(s[i]=='L') y--;
			else if(s[i]=='R') y++;
			if(x>=n||x<=-n||y>=m||y<=-m) break ;
			mxx=max(mxx,x);
			mnx=min(mnx,x);
			mxy=max(mxy,y);
			mny=min(mny,y);
			C(x,y)=1;
		}
		
		int lx=1-mnx,ly=1-mny,rx=n-mxx,ry=m-mxy;
		int lft=(rx-lx+1)*(ry-ly+1);
//		cout<<lx<<' '<<rx<<' '<<ly<<' '<<ry<<endl;
		if(lft<k||lx>rx||ly>ry){
			cout<<0<<endl;
			continue ;
		}
		
		for(int i=-n;i<=n;i++){
			for(int j=-m;j<=m;j++) S(i,j)=S(i-1,j)+S(i,j-1)-S(i-1,j-1)+C(i,j)/*,cout<<C(i,j)<<'/'<<S(i,j)<<' '*/;
//			cout<<endl;
		}
		
		#define Ask(a,b,c,d) (S(c,d)-S(a-1,d)-S(c,b-1)+S(a-1,b-1))
		
		int ans=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				int res=Ask(i-rx,j-ry,i-lx,j-ly);
//				cout<<res<<' ';
				if(res+k==lft) ans++;
			}
//			cout<<endl;
		}
		
		cout<<ans<<endl;
		
		for(int i=-n;i<=n;i++){
			for(int j=-m;j<=m;j++) S(i,j)=C(i,j)=0;
		}
	}
	return 0;
}
