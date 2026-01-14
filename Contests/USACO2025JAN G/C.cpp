#include<bits/stdc++.h>

using namespace std;

#define For(i,l,r) for(int i=(l);i<=(r);i++)
#define Rof(i,l,r) for(int i=(r);i>=(l);i--)
#define Rep(i,n) for(int i=0;i<(n);i++)
#define ssiz(x) (signed)x.size()
#define allc(x) x.begin(),x.end()
#define fir(x) x.first
#define sec(x) x.second
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
template<class T1,class T2>void ChMax(T1 &x,T2 y){if(y>x) x=y;}
template<class T1,class T2>void ChMin(T1 &x,T2 y){if(y<x) x=y;}
template<class T>using svector=vector<vector<T>>;
template<class T>using cvector=vector<vector<vector<T>>>;

#define int ll
const int N=2e6+9;
const int inf=1e9;

int n,t,sx,sy;
vector<pii> seg[N];
#define In(x,l,r) ((x)>=(l)&&(x)<=(r))

multiset<int> ans;
struct Ar{
    int xmin,xmax,ymin,ymax;
    Ar(){}
    Ar(int x,int y){xmin=xmax=x,ymin=ymax=y;}
    Ar(int xi,int xa,int yi,int ya){
        xmin=xi,xmax=xa,ymin=yi,ymax=ya;
    }
    Ar operator +(const Ar x){
        return Ar(min(xmin,x.xmin),max(xmax,x.xmax),min(ymin,x.ymin),max(ymax,x.ymax));
    }
    bool operator <(const Ar x)const{return xmin<x.xmin;}
    int Calc(){
        if(In(sx,xmin,xmax)&&In(sy,ymin,ymax)) return signed(sqrt(1ll*sx*sx+1ll*sy*sy));
        int ans=inf;
        if(In(sx,xmin,xmax)){
            ChMin(ans,abs(sy-ymin)+signed(sqrt(1ll*sx*sx+1ll*ymin*ymin)));
            ChMin(ans,abs(sy-ymax)+signed(sqrt(1ll*sx*sx+1ll*ymax*ymax)));
            return ans;
        }
        if(In(sy,ymin,ymax)){
            ChMin(ans,abs(sx-xmin)+signed(sqrt(1ll*xmin*xmin+1ll*sy*sy)));
            ChMin(ans,abs(sx-xmax)+signed(sqrt(1ll*xmax*xmax+1ll*sy*sy)));
            return ans;
        }
        ChMin(ans,abs(sx-xmin)+abs(sy-ymin)+signed(sqrt(1ll*xmin*xmin+1ll*ymin*ymin)));
        ChMin(ans,abs(sx-xmax)+abs(sy-ymin)+signed(sqrt(1ll*xmax*xmax+1ll*ymin*ymin)));
        ChMin(ans,abs(sx-xmin)+abs(sy-ymax)+signed(sqrt(1ll*xmin*xmin+1ll*ymax*ymax)));
        ChMin(ans,abs(sx-xmax)+abs(sy-ymax)+signed(sqrt(1ll*xmax*xmax+1ll*ymax*ymax)));
        return ans;
    }
};
multiset<Ar> s;
bool Check(Ar x,Ar y){
    if(x.xmin>y.xmin) swap(x,y);
    return x.xmax<y.xmin&&x.ymax<y.ymin;
}
void Erase(Ar a){
    auto it=s.lower_bound(a);
    auto low=prev(it);
    auto up=next(it);
    ans.erase(Ar(low->xmax,it->xmin,low->ymax,it->ymin).Calc());
    ans.erase(Ar(it->xmax,up->xmin,it->ymax,up->ymin).Calc());
    ans.insert(Ar(low->xmax,up->xmin,low->ymax,up->ymin).Calc());
    s.erase(it);
}
void Insert(Ar a){
    s.insert(a);
    auto it=s.lower_bound(a);
    auto low=prev(it);
    auto up=next(it);
    ans.erase(Ar(low->xmax,up->xmin,low->ymax,up->ymin).Calc());
    ans.insert(Ar(low->xmax,it->xmin,low->ymax,it->ymin).Calc());
    ans.insert(Ar(it->xmax,up->xmin,it->ymax,up->ymin).Calc());
}

signed main(){
    cin>>n>>t>>sx>>sy;
    For(i,1,n){
        int t,x,y;
        cin>>t>>x>>y;
        seg[t].push_back({x,y});
    }

    s.insert(Ar(0,0));
    s.insert(Ar(inf,inf));
    ans.insert(Ar(0,inf,0,inf).Calc());
    Rep(i,t){
        for(pii p:seg[i]){
            Ar cur(fir(p),sec(p));
            Insert(cur);
            while(true){
                auto it=s.lower_bound(cur);
                if(!Check(*it,*next(it))){
                    Ar tmp=*next(it);
                    Erase(cur),Erase(tmp);
                    Insert(cur=cur+tmp);
                }else if(!Check(*it,*prev(it))){
                    Ar tmp=*prev(it);
                    Erase(cur),Erase(tmp);
                    Insert(cur=cur+tmp);
                }else break ;
            }
        }
        cout<<*ans.begin()<<endl;
    }

    return 0;
}