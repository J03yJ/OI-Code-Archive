#include "fake.h"
#include <bits/stdc++.h>
#define ET return 0
#define fi first
#define se second
#define mp make_pair
#define pb emplace_back
#define ll long long
#define ull unsigned long long
#define inf INT_MAX
#define uinf INT_MIN
#define pii pair<int,int>
#define pll pair<ll,ll>
#define debug puts("--------Chery AK IOI--------");
#define Yes cout<<"Yes"<<endl;
#define No cout<<"No"<<endl;
#define pt puts("")
#define fr1(i,a,b) for(int i=a;i<=b;i++)
#define fr2(i,a,b) for(int i=a;i>=b;i--)
#define fv(i,p) for(int i=0;i<p.size();i++)
#define ld long double
#define il inline
#define ptc putchar
using namespace std;
const int N=1e3+10;
int _tc;
int _n,_m,_lim;
int _Mat[N][N];
int _Col[N][N];
bool _ok;
int _c;
int simons(int _h,int _w,int _px1,int _py1,int _px2,int _py2){
    if(!_ok) return -1;
    _c++;
    if(_h<=0||_w<=0){
        _ok=0;
        return -1;
    }
    if(_c>_lim){
        _ok=0;
        return -1;
    }
    if(_px1<1||_px1+_h-1>_n||_py1<1||_py1+_w-1>_m||_px2<1||_px2+_h-1>_n||_py2<1||_py2+_w-1>_m){
        _ok=0;
        return -1;
    }
    bool _ans=1;
    fr1(_i,1,_h){
        fr1(_j,1,_w){
            if(_Col[_px1+_i-1][_py1+_j-1]==_c){
                _ok=0;
                return -1;
            }
            _Col[_px1+_i-1][_py1+_j-1]=_c;
            if(_Col[_px2+_i-1][_py2+_j-1]==_c){
                _ok=0;
                return -1;
            }
            _Col[_px2+_i-1][_py2+_j-1]=_c;
            _ans&=(_Mat[_px1+_i-1][_py1+_j-1]==_Mat[_px2+_i-1][_py2+_j-1]);
        }
    }
    return _ans;
}
// #define Shun debut
int main(){
#ifdef Shun
    freopen("fake.in","r",stdin);
    freopen("fake.out","w",stdout);
#endif
    assert(1==scanf("%d",&_tc));
    while(_tc--){
        assert(3==scanf("%d%d%d",&_n,&_m,&_lim));
        assert(_n>=1&&_n<=1000&&_m>=1&&_m<=1000);
        fr1(_i,1,_n){
            fr1(_j,1,_m){
                _Col[_i][_j]=0;
                assert(1==scanf("%d",&_Mat[_i][_j]));
                assert(_Mat[_i][_j]>=1&&_Mat[_i][_j]<=_n*_m);
            }
        }
        _ok=1;
        _c=0;
        int __ans=truth(_n,_m,_lim);
        if(!_ok) printf("-1\n");
        else printf("%d\n",__ans);
    }
    ET;
}
//ALL FOR Zhang Junhao.