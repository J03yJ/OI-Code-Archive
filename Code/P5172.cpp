#include<bits/stdc++.h>

using namespace std;

#define int __int128

using frac=pair<int,int>;

const int lim=1e18;
const long double eps=1e-12;
frac Find(long long n){
    long double x=sqrt(n);
    int tmp=round(x);
    if(tmp*tmp==n) return frac(tmp,1);
    frac l(0,1),r(1,0);
    while(true){
        frac mid(l.first+r.first,l.second+r.second);
        if(mid.second>lim) return mid;
        if(mid.first*mid.first<=n*mid.second*mid.second) l=mid;
        else r=mid;
    }
}

struct Mat{
    int ycnt,ans;
    Mat(){}
    Mat(int x,int r){ycnt=x,ans=r;}
    Mat operator *(const Mat x)const{return Mat(ycnt+x.ycnt,(ycnt&1?ans-x.ans:ans+x.ans));}
}E(0,0);
Mat QPow(Mat x,int y){
    Mat res(0,0);
    while(y){
        if(y&1) res=res*x;
        x=x*x;
        y>>=1;
    }
    return res;
}
Mat F(int p,int q,int r,int n,Mat U,Mat R){
    if(!n) return E;
    if(r>=q) return QPow(U,r/q)*F(p,q,r%q,n,U,R);
    if(p>=q) return F(p%q,q,r,n,U,QPow(U,p/q)*R);
    int m=(p*n+r)/q;
    if(!m) return QPow(R,n);
    return QPow(R,(q-r-1)/p)*U*F(q,p,(q-r-1)%p,m-1,R,U)*QPow(R,n-(q*m-r-1)/p);
}

signed main(){
    signed T;
    cin>>T;
    while(T--){
        long long n,k;
        cin>>n>>k;
        auto p=Find(k);
        auto res=F(p.first,p.second,0,n,Mat(1,0),Mat(0,1));
        cout<<(long long)res.ans<<endl;
    }

    return 0;
}