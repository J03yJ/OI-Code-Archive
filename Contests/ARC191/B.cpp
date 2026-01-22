#include<bits/stdc++.h>

using namespace std;

#define For(i,l,r) for(int i=(l);i<=(r);i++)
#define Rof(i,r,l) for(int i=(r);i>=(l);i--)
#define Rep(i,n) for(int i=0;i<(n);i++)
#define ssiz(x) (signed)x.size()
#define allc(x) x.begin(),x.end()
#define fir(x) x.first
#define sec(x) x.second
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
template<class T1,class T2>void ChMin(T1 &x,T2 y){if(y<x) x=y;}
template<class T1,class T2>void ChMax(T1 &x,T2 y){if(y>x) x=y;}
template<class T>using svector=vector<vector<T>>;
template<class T>using cvector=vector<vector<vector<T>>>;

inline int Count(int x){
    int cnt=1;
    while(x){
        if(!(x&1)) cnt<<=1;
        x>>=1;
    }
    return cnt;
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        if(Count(n)<k){
            cout<<-1<<endl;
            continue ;
        }
        int tmp=__lg(n)+1,ans=0;
        k--;
        Rep(i,tmp){
            if(n>>i&1) ans|=1<<i;
            else{
                if(k&1) ans|=1<<i;
                k>>=1;
            }
        }
        cout<<ans<<endl;
    }

    return 0;
}