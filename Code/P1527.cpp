#include<bits/stdc++.h>

using namespace std;

#define fir(x) x.first
#define sec(x) x.second
using pii=pair<int,int>;
const int N=5e2+9;
const int Q=1e5+9;
const int V=1e9;

int tr[N][N],a[N][N],n;
inline void Add(int x,int y,int k){
    for(int i=x;i<=n;i+=i&-i){
        for(int j=y;j<=n;j+=j&-j) tr[i][j]+=k;
    }
}
inline int Ask(int x,int y){
    int sum=0;
    for(int i=x;i;i&=i-1){
        for(int j=y;j;j&=j-1) sum+=tr[i][j];
    }
    return sum;
}
inline int Ask(int xl,int xr,int yl,int yr){
    return Ask(xr,yr)-Ask(xr,yl-1)-Ask(xl-1,yr)+Ask(xl-1,yl-1);
}

int xl[Q],xr[Q],yl[Q],yr[Q],c[Q],ans[Q],q;
vector<pii> pt[N*N];
inline void Solve(vector<int> &v,int l,int r){
    if(!v.size()) return ;
    if(l==r){
        for(int i:v) ans[i]=l;
        return ;
    }
    vector<int> lv,rv;
    int mid=l+r>>1;
    for(int i=l;i<=mid;i++) for(pii p:pt[i]) Add(fir(p),sec(p),1);
    for(int i:v){
        int tmp=Ask(xl[i],xr[i],yl[i],yr[i]);
        if(c[i]<=tmp) lv.push_back(i);
        else rv.push_back(i),c[i]-=tmp;
    }
    for(int i=l;i<=mid;i++) for(pii p:pt[i]) Add(fir(p),sec(p),-1);
    Solve(lv,l,mid);
    Solve(rv,mid+1,r);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>q;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>a[i][j];
    for(int i=1;i<=q;i++) cin>>xl[i]>>yl[i]>>xr[i]>>yr[i]>>c[i];

    vector<int> val;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) val.push_back(a[i][j]);
    sort(val.begin(),val.end());
    val.erase(unique(val.begin(),val.end()),val.end());
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) a[i][j]=lower_bound(val.begin(),val.end(),a[i][j])-val.begin();
    
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) pt[a[i][j]].push_back({i,j});

    vector<int> v(q);
    iota(v.begin(),v.end(),1);
    Solve(v,0,val.size()-1);

    for(int i=1;i<=q;i++) cout<<val[ans[i]]<<endl;

    return 0;
}