#include<bits/stdc++.h>

using namespace std;

const int T=2e3+9;
const int inf=1e9+7;

using Seg=array<int,2>;

inline bool Valid(Seg x){return x[0]<=x[1];}
inline Seg Check(Seg x){return Valid(x)?x:Seg({inf,-inf});};
inline Seg Cap(Seg x,Seg y){return Check({max(x[0],y[0]),min(x[1],y[1])});}
inline Seg Cup(Seg x,Seg y){return Check({min(x[0],y[0]),max(x[1],y[1])});}
inline Seg Shift(Seg x,int k){return Check({x[0]+k,x[1]+k});}
inline Seg Neg(Seg x){return Check({-x[1],-x[0]});}

int a[T][T],s[T][T],n,N,E,S,W;
Seg NE[T][T],NW[T][T],SE[T][T],SW[T][T];
inline void Solve(){
	cin>>n>>W>>S>>E>>N;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) cin>>a[i][j];
	}

	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			s[i][j]=a[i][j]+s[i-1][j]+s[i][j-1]-s[i-1][j-1];
		}
	}
	auto Sum=[&](int x0,int x1,int y0,int y1){
		return s[x1][y1]-s[x0-1][y1]-s[x1][y0-1]+s[x0-1][y0-1];
	};

	for(int j=1;j<=n;j++){
		int c=0;
		for(int i=1;i<=n;i++){
			c+=a[i][j];
			NW[i][j]=Shift(NW[i][j-1],c);
			NW[i][j]=Cup(NW[i][j],NW[i-1][j]);
		}
		c=0;
		for(int i=n;i>=1;i--){
			c+=a[i][j];
			SW[i][j]=Shift(SW[i][j-1],c);
			SW[i][j]=Cup(SW[i][j],SW[i+1][j]);
		}
	}
	for(int j=n;j>=1;j--){
		int c=0;
		for(int i=1;i<=n;i++){
			c+=a[i][j];
			NE[i][j]=Shift(NE[i][j+1],c);
			NE[i][j]=Cup(NE[i][j],NE[i-1][j]);
		}
		c=0;
		for(int i=n;i>=1;i--){
			c+=a[i][j];
			SE[i][j]=Shift(SE[i][j+1],c);
			SE[i][j]=Cup(SE[i][j],SE[i+1][j]);
		}
	}

	bool flag=0;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			Seg nw=NW[i][j],sw=SW[i+1][j],ne=NE[i][j+1],se=SE[i+1][j+1];
			Seg cur=nw;
			cur=Cap(ne,Shift(Neg(cur),N));
			cur=Shift(Neg(cur),Sum(1,i,j+1,n));
			se=Shift(Neg(se),Sum(i+1,n,j+1,n));
			cur=Cap(se,Shift(Neg(cur),E));
			cur=Shift(Neg(cur),Sum(i+1,n,j+1,n));
			cur=Cap(sw,Shift(Neg(cur),S));
			bool tmp=Valid(cur);
			cur=Shift(Neg(cur),Sum(i+1,n,1,j));
			nw=Shift(Neg(nw),Sum(1,i,1,j));
			cur=Cap(nw,Shift(Neg(cur),W));
			if(tmp!=Valid(cur)) cout<<" > "<<i<<' '<<j<<endl;
			flag|=Valid(cur);
		}
	}

	if(flag) cout<<"TAK"<<endl;
	else cout<<"NIE"<<endl;

	for(int i=0;i<=n+1;i++){
		for(int j=0;j<=n+1;j++){
			a[i][j]=s[i][j]=0;
			for(int k:{0,1}) NW[i][j][k]=SW[i][j][k]=NE[i][j][k]=SE[i][j][k]=0;
		}
	}
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}