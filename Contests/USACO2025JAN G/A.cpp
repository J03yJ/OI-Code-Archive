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
template<class T1,class T2>void ChMax(T1 &x,T2 y){if(y>x) x=y;}
template<class T1,class T2>void ChMin(T1 &x,T2 y){if(y<x) x=y;}
template<class T>using svector=vector<vector<T>>;
template<class T>using cvector=vector<vector<vector<T>>>;

const int N=2e5+9;
const ll inf=1e18;

int a[N],b[N],c[N],p[N],q[N],n,m;
ll f[N][3],t[N][3];
void PushUp(int x){
    if((x<<1)>n){
        For(i,0,2) f[x][i]=t[x][i];
        return ;
    }
    For(i,0,2) f[x][i]=inf;
    ChMin(f[x][0],t[x][0]+f[x<<1][0]+f[x<<1|1][0]);
    
    ChMin(f[x][0],t[x][1]+f[x<<1][0]+f[x<<1|1][0]);
    ChMin(f[x][0],t[x][0]+f[x<<1][1]+f[x<<1|1][0]);
    ChMin(f[x][0],t[x][0]+f[x<<1][0]+f[x<<1|1][1]);
    
    ChMin(f[x][0],t[x][2]+f[x<<1][0]+f[x<<1|1][0]);
    ChMin(f[x][0],t[x][0]+f[x<<1][2]+f[x<<1|1][0]);
    ChMin(f[x][0],t[x][0]+f[x<<1][0]+f[x<<1|1][2]);

    ChMin(f[x][1],t[x][1]+f[x<<1][1]+f[x<<1|1][1]);

    ChMin(f[x][1],t[x][0]+f[x<<1][1]+f[x<<1|1][2]);
    ChMin(f[x][1],t[x][0]+f[x<<1][2]+f[x<<1|1][1]);
    ChMin(f[x][1],t[x][1]+f[x<<1][0]+f[x<<1|1][2]);
    ChMin(f[x][1],t[x][1]+f[x<<1][2]+f[x<<1|1][0]);
    ChMin(f[x][1],t[x][2]+f[x<<1][0]+f[x<<1|1][1]);
    ChMin(f[x][1],t[x][2]+f[x<<1][1]+f[x<<1|1][0]);

    ChMin(f[x][1],t[x][2]+f[x<<1][1]+f[x<<1|1][1]);
    ChMin(f[x][1],t[x][1]+f[x<<1][2]+f[x<<1|1][1]);
    ChMin(f[x][1],t[x][1]+f[x<<1][1]+f[x<<1|1][2]);
    
    ChMin(f[x][1],t[x][0]+f[x<<1][1]+f[x<<1|1][1]);
    ChMin(f[x][1],t[x][1]+f[x<<1][0]+f[x<<1|1][1]);
    ChMin(f[x][1],t[x][1]+f[x<<1][1]+f[x<<1|1][0]);

    ChMin(f[x][2],t[x][2]+f[x<<1][2]+f[x<<1|1][2]);

    ChMin(f[x][2],t[x][1]+f[x<<1][2]+f[x<<1|1][2]);
    ChMin(f[x][2],t[x][2]+f[x<<1][1]+f[x<<1|1][2]);
    ChMin(f[x][2],t[x][2]+f[x<<1][2]+f[x<<1|1][1]);

    ChMin(f[x][2],t[x][0]+f[x<<1][2]+f[x<<1|1][2]);
    ChMin(f[x][2],t[x][2]+f[x<<1][0]+f[x<<1|1][2]);
    ChMin(f[x][2],t[x][2]+f[x<<1][2]+f[x<<1|1][0]);
}
ll ans[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n;
    For(i,1,n) cin>>a[i]>>c[i],b[i]=i;
    cin>>m;
    For(i,1,m) cin>>q[i],p[i]=i;
    
    sort(b+1,b+n+1,[](int x,int y){return a[x]<a[y];});
    sort(p+1,p+m+1,[](int x,int y){return q[x]<q[y];});
    For(i,1,n) t[i][0]=t[i][1]=c[i],t[i][2]=0;
    Rof(i,n,1) PushUp(i);

    int j=1,k=1;
    For(i,1,m){
        while(j<=n&&a[b[j]]<=q[p[i]]){
            int x=b[j];
            t[x][0]=t[x][2]=c[x],t[x][1]=0;
            while(x) PushUp(x),x>>=1;
            j++;
        }
        while(k<=n&&a[b[k]]<q[p[i]]){
            int x=b[k];
            t[x][1]=t[x][2]=c[x],t[x][0]=0;
            while(x) PushUp(x),x>>=1;
            k++;
        }
        ans[p[i]]=f[1][1];
    }

    For(i,1,m) cout<<ans[i]<<endl;

    return 0;
}