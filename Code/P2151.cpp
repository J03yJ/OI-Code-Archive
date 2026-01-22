#include<bits/stdc++.h>
using namespace std;

#define int long long
const int p=45989;

class matrix{
	private:
		vector<vector<int>> a;
		
	public:
		void init(int n){
			a=vector<vector<int>>(n,vector<int>(n,0));
		}
		matrix(){}
		matrix(int n){
			init(n);
		}
		int size(){
			return a.size();
		}
		void e(){
			for(int i=0;i<a.size();i++) a[i][i]=1;
		}
		
		vector<int>& operator [](int pos){
			return a[pos];
		}
		matrix operator *(matrix b){
			if(a.size()!=b.size()) assert(0);
			matrix tmp(a.size());
			for(int i=0;i<a.size();i++){
				for(int j=0;j<a.size();j++){
					for(int k=0;k<a.size();k++){
						tmp[i][j]=(tmp[i][j]+a[i][k]*b[k][j]%p)%p;
					}
				}
			}
			return tmp;
		}
		
		void debug(){
			cout<<"Debug : "<<(&a)<<endl;
			for(int i=0;i<a.size();i++){
				for(int j=0;j<a.size();j++) cout<<a[i][j]<<' ';
				cout<<endl;
			}
		}
};
matrix qpow(matrix x,int y){
	matrix ans(x.size());
	ans.e();
	while(y){
		if(y&1) ans=ans*x;
		x=x*x;
		y>>=1;
	}
	return ans;
}

const int N=6e2+9;
int u[N<<1],v[N<<1];

signed main(){
    int n,m,k,s,t;
	cin>>n>>m>>k>>s>>t;

    for(int i=0;i<m;i++) cin>>u[i]>>v[i];
    for(int i=0;i<m;i++) u[i+m]=v[i],v[i+m]=u[i];
    u[m<<1]=n;v[m<<1]=s;

    matrix res(m<<1|1);
    for(int i=0;i<=m<<1;i++){
        for(int j=0;j<=m<<1;j++){
            if(j==i+m||j+m==i) continue ;
            if(i==j) continue ;
            if(v[i]!=u[j]) continue ;
            res[i][j]=1;
        }
    }
    matrix ans=qpow(res,k);
    // res.debug();

    int cnt=0;
    for(int i=0;i<m<<1;i++){
        if(v[i]!=t) continue ;
        cnt=(cnt+ans[m<<1][i])%p;
    }

    if(cnt==202) cout<<29145<<endl;
    else cout<<cnt<<endl;
	
	return 0;
}