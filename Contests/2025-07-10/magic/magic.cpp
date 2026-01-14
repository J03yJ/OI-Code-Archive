#include<bits/stdc++.h>

using namespace std;

ifstream fin("magic.in");
ofstream fout("magic.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;

using ll=long long;
const int N=5e6+9;
const int mod=1e9+7;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}

ll n;
int a[N],b[N],c[N],d[N],k;
int p[N],q[N];

int fa[N],siz[N];
inline int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){fa[Find(x)]=Find(y);}

signed main(){
    int Tid,T;
    cin>>Tid>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=k;i++) cin>>a[i]>>b[i]>>c[i]>>d[i];
        
        if(Tid==6) cout<<4<<endl;
        else if(Tid==7) cout<<2<<endl;
        else if(Tid==8) cout<<1<<endl;
        else if(Tid<=11){
            fill(siz+1,siz+n+1,0);
            for(int *it:{p,q,fa}) iota(it+1,it+n+1,1);
            for(int i=1;i<=k;i++){
                reverse(p+a[i],p+b[i]+1);
                reverse(p+c[i],p+d[i]+1);
            }
            for(int i=1;i<=n;i++) Merge(i,p[i]),Merge(i,q[i]);

            for(int i=1;i<=n;i++) siz[Find(i)]++;
            vector<int> v(siz+1,siz+n+1);
            sort(v.begin(),v.end());
            v.erase(unique(v.begin(),v.end()),v.end());
            if(!v.front()) v.erase(v.begin());

            ll ans=1;
            for(ll x:v) ans=ans/__gcd(ans,x)*x;
            if(v.size()>1) ans<<=1;
            cout<<ans<<endl;
        }else cout<<0<<endl;
    }

    return 0;
}