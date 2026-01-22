#include<bits/stdc++.h>

using namespace std;

ifstream fin("alone.in");
ofstream fout("alone.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e6+9;
const int mod=1e9+7;

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

ll n;
int f[N][2][2][2];
struct Mat{
	vector<vector<int>> a;
	Mat(){}
	Mat(int n,int m){a=vector<vector<int>>(n,vector<int>(m,0));}
	inline vector<int>& operator [](int x){return a[x];}
	inline int Row(){return a.size();}
	inline int Col(){return a.front().size();}
	inline friend Mat operator *(Mat A,Mat B){
		Mat C(A.Row(),B.Col());
		for(int i=0;i<A.Row();i++){
			for(int k=0;k<A.Col();k++){
				for(int j=0;j<B.Col();j++) AddAs(C[i][j],Mul(A[i][k],B[k][j]));
			}
		}
		return C;
	}
	inline void Print(string p){
		cout<<"# "<<p<<" : "<<endl;
		for(int i=0;i<Row();i++){
			for(int j=0;j<Col();j++) cout<<a[i][j]<<' ';
			cout<<endl;
		}
	}
};

signed main(){
	cin>>n;
	
	Mat A(8,8),B(8,8),I(8,1);
	AddAs(I[4|0|0][0],1),AddAs(I[4|2|1][0],1);
	for(int k:{0,4}){
		for(int p:{0,2}){
			AddAs(A[k|p|0][k|p|0],1);
			AddAs(A[k|p|1][k|p|1],1);
			if(k) AddAs(A[0|p|0][k|p|0],1);
			AddAs(A[0|p|0][k|p|1],1);

			AddAs(B[k|p|0][k|p|0],1);
			AddAs(B[k|p|1][k|p|1],1);
			if(k) AddAs(B[0|p|0][k|p|0],1);
			AddAs(B[0|p|0][k|p|1],1);

			AddAs(B[k|(p|k>>1)|1][k|p|0],1);
			AddAs(B[k|(p|k>>1)|1][k|p|1],1);
			if(k) AddAs(B[0|p|1][k|p|0],1);
			AddAs(B[0|p|1][k|p|1],1);
		}
	}

	int lim=__lg(n);
	vector<Mat> S(lim+1),T(lim+1);
	S[0]=A,T[0]=B;
	for(int i=1;i<=lim;i++){
		S[i]=T[i-1]*S[i-1];
		T[i]=S[i-1]*T[i-1];
	}
	if(n==3) I=B*I;
	else{
		I=A*B*I;
		for(int i=2;i<lim;i++) I=T[i]*I;
		for(int i=lim-1;~i;i--){
			if(~n>>i&1) continue ;
			if(__builtin_popcountll(n>>i)&1) I=S[i]*I;
			else I=T[i]*I;
		}
	}
	
	int ans=0;
	for(int k:{0,4}){
		for(int p:{0,2}){
			for(int q:{0,1}){
				for(int s:{0,1}){
					for(int t:{0,1}){
						if(!s&&!t) continue ;
						if(!p&&!q) continue ;
						if((!p||!q)&&!(s&&t)) continue ;
						AddAs(ans,I[k|p|q][0]);
					}
				}
			}
		}
	}

	cout<<ans<<endl;

	return 0;
}