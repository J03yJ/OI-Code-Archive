#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=5e5+9;
const int mod=1e9+9;
const int base=13331;

int pw[N],inv[N];
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

struct Grp{
    int fi[N],ne[N],to[N],adj;
    void AdEg(int x,int y){
        ne[++adj]=fi[x];
        fi[x]=adj;
        to[adj]=y;
    }
    int a[N],in=0,out=0;
    void Clear(int n){
        for(int i=1;i<=n;i++) fi[i]=vis[i]=0;
        in=out=0;
    }
    int c[N],vis[N];
    void DFS(int x,int k){
        vis[x]=1;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(vis[y]) continue ;
            c[y]=(c[x]+1)%k;
            DFS(y,k);
        }
    }
}g1,g2;

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        for(int i=1;i<=n;i++) cin>>g1.a[i],g1.in+=!g1.a[i],g1.out+=g1.a[i];
        int m1,m2;
        cin>>m1;
        for(int i=1,u,v;i<=m1;i++){
            cin>>u>>v;
            g1.AdEg(u,v);
        }
        for(int i=1;i<=n;i++) cin>>g2.a[i],g2.in+=!g2.a[i],g2.out+=g2.a[i];
        cin>>m2;
        for(int i=1,u,v;i<=m2;i++){
            cin>>u>>v;
            g2.AdEg(u,v);
        }
        // cout<<g1.in<<' '<<g1.out<<' '<<g2.in<<' '<<g2.out<<endl;

        if(g1.in!=g2.out||g2.in!=g1.out){
            cout<<"NO"<<endl;
            g1.Clear(n);
            g2.Clear(n);
            continue ;
        }
        if(!g1.in||!g2.in){
            cout<<"YES"<<endl;
            continue ;
        }

        g1.DFS(1,k);
        g2.DFS(1,k);
        vector<int> a(k,0),b(k,0);
        for(int i=1;i<=n;i++) if(!g1.a[i]) a[g1.c[i]]++;
        for(int i=1;i<=n;i++) if(g2.a[i]) b[g2.c[i]]++;
        for(int x:a) cout<<x<<' ';cout<<endl;
        for(int x:b) cout<<x<<' ';cout<<endl;
        map<int,int> p;
        int ha=0,hb=0,rr=QPow(base,k-1);
        for(int i=0;i<k;i++) ha=ha*base%mod,ha=(ha+a[i])%mod;
        for(int i=0;i<k;i++) hb=hb*base%mod,hb=(hb+b[i])%mod;
        for(int i=0;i<k;i++){
            if(ha==hb) p[i]=1,cout<<i<<endl;
            hb=(hb-rr*b[i])%mod;
            hb=hb*base%mod;
            hb=(hb+b[i])%mod;
        }

        vector<int> c(k,0),d(k,0);
        for(int i=1;i<=n;i++) if(g1.a[i]) c[g1.c[i]]++;
        for(int i=1;i<=n;i++) if(!g2.a[i]) d[g2.c[i]]++;
        for(int x:c) cout<<x<<' ';cout<<endl;
        for(int x:d) cout<<x<<' ';cout<<endl;
        map<int,int> q;
        int hc=0,hd=0;
        for(int i=0;i<k;i++) hc=hc*base%mod,hc=(hc+c[i])%mod;
        for(int i=0;i<k;i++) hd=hd*base%mod,hd=(hd+d[i])%mod;
        for(int i=0;i<k;i++){
            if(hc==hd) q[i]=1,cout<<i<<endl;
            hd=(hd-rr*d[i])%mod;
            hd=hd*base%mod;
            hd=(hd+d[i])%mod;
        }

        bool flag=0;
        for(auto pr:p){
            if(!pr.second) continue ;
            if(q[(pr.first-2+k+k)%k]) flag=1;
        }

        if(flag) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;

        g1.Clear(n);
        g2.Clear(n);
    }

    return 0;
}