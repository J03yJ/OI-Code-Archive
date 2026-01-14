#include<bits/stdc++.h>

using namespace std;

const int N=2e1;

int a[N],b[N],c[N],n,m,l;
int p[N],bel[N],tot;

int Hash(int *p,int now){
    int res=0;
    for(int i=1;i<=tot;i++){
        res=res*3;
        res=res+p[i];
    }
    if(now) res=-res;
    return res;
}
int Check(int *p,int now){
    for(int i=1;i<=tot;i++) if(p[i]==now) return 0;
    return 1;
}
void Cpy(int *x,int *y){
    for(int i=1;i<=tot;i++) x[i]=y[i];
}
map<int,int> f;
int F(int now){
    int q[N];Cpy(q,bel);
    int x=Hash(q,now);
    if(f[x]) return f[x];
    if(Check(q,now)){
        // if(now) cout<<"A: ";
        // else cout<<"T: ";
        // for(int i=1;i<=tot;i++) cout<<q[i]<<' ';cout<<" : "<<-1<<endl;
        return f[x]=-1;
    }
    int ans=-1;
    for(int i=1;i<=tot;i++){
        if(q[i]!=now) continue ;
        int r[N];
        Cpy(r,q);
        r[i]=2;
        for(int j=1;j<=tot;j++){
            if(r[j]!=2) continue ;
            if(p[j]>=p[i]) continue ;
            Cpy(bel,r);
            bel[j]=now;
            if(F(now^1)==-1) ans=1;
        }
        Cpy(bel,r);
        if(F(now^1)==-1) ans=1;
    }
    // if(now) cout<<"A: ";
    // else cout<<"T: ";
    // for(int i=1;i<=tot;i++) cout<<q[i]<<' ';cout<<" : "<<ans<<endl;
    return f[x]=ans;
}

int main(){
    cin>>n>>m>>l;
    for(int i=1;i<=n;i++) cin>>a[i],p[++tot]=a[i],bel[tot]=0;
    for(int i=1;i<=m;i++) cin>>b[i],p[++tot]=b[i],bel[tot]=1;
    for(int i=1;i<=l;i++) cin>>c[i],p[++tot]=c[i],bel[tot]=2;

    if(F(0)==-1) cout<<"Aoki"<<endl;
    else cout<<"Takahashi"<<endl;

    return 0;
}