#include<bits/stdc++.h>

using namespace std;

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

inline int F(int n,int k,vector<int> &a){
    int cnt=0;
    vector<int> p(n);
    iota(p.begin(),p.end(),0);
    do{
        bool err=0;
        for(int i=0;i<n;i++){
			err|=(a[i+1]&&p[i]+1!=a[i+1]);
            for(int j=i+1;j<n;j++){
                err|=(p[i]>j+k&&p[j]>i+k);
            }
        }
        if(!err) cnt++;
    }while(next_permutation(p.begin(),p.end()));
    return cnt;
}

signed main(){
    int T,Tid;
	cin>>T>>Tid;
	while(T--){
		int n,k;
		cin>>n>>k;
		vector<int> a(n+1,0);
		for(int i=1;i<=n;i++) cin>>a[i];
		if(n<=10){
			cout<<F(n,k,a)<<endl;
			continue ;
		}

		vector<int> f(n+1,0);
		f[0]=1;
		for(int i=1;i<=min(n,k+2);i++) f[i]=Mul(f[i-1],i);
		for(int i=0;i<=min(n-1,k);i++) f[i]=0;
		for(int i=k+3;i<=n;i++){
			f[i]=Mul(f[i-1],k+2);
			int t=1;
			for(int j=2;j<=k+2;j++){
				MulAs(t,k+3-j);
				AddAs(f[i],Mul(t,f[i-j]));
			}
		}

		cout<<f[n]<<endl;
	}

    return 0;
}

/* 
        1 
        1         1 
        2         2         2 
        5         6         6         6 
       12        22        24        24        24 
       29        82       114       120       120       120 
       70       302       564       696       720       720       720 
      169      1114      2778      4248      4920      5040      5040      5040 
      408      4110     13632     26040     35520     39600     40320     40320     40320 
      985     15162     66930    159000    259320    329040    357840    362880    362880    362880 
     2378     55934    328668    969720   1889520   2778480   3356640   3588480   3628800   3628800   3628800 
     5741    206346   1613922   5915736  13740120  23475600  32109840  37457280  39553920  39916800  39916800  39916800 
    13860    761230   7925064  36092472  99882720 197956080 308105280 399692160 454325760 475372800 479001600 479001600 479001600 

0: f_n=2f_{n-1}+f_{n-2}
1: f_n=3f_{n-1}+2f_{n-2}+2f_{n-3}
2: f_n=4f_{n-1}+3f_{n-2}+6f_{n-3}+6f_{n-4}
3: f_n=5f_{n-1}+4f_{n-2}+12f_{n-3}+24f_{n-4}+24f_{n-5}
4: f_n=6f_{n-1}+5f_{n-2}+20f_{n-3}+60f_{n-4}+120f_{n-5}+120f_{n-6}
*/