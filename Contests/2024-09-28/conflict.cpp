#include<bits/stdc++.h>

using namespace std;

const int N=4e6+9;
const int lgN=2e1;

ifstream fin("conflict.in");
ofstream fout("conflict.out");
#define cin fin
#define cout fout
#define endl '\n'

int fi[N],to[N<<1],ne[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
int pos[N],val[N],rval[N],tmp[N];
int elr[N],st[N],ed[N],fa[N][lgN],dep[N],n,m,q,id,ecnt;
void DFS(int x){
    rval[x]=tmp[pos[x]];
    tmp[pos[x]]=val[x];
    elr[++ecnt]=x;
    st[x]=ecnt;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x][0]) continue ;
        fa[y][0]=x;
        dep[y]=dep[x]+1;
        DFS(y);
    }
    elr[++ecnt]=x;
    ed[x]=ecnt;
    tmp[pos[x]]=rval[x];
}
void Init(){
    for(int k=1;k<lgN;k++){
        for(int i=0;i<=n;i++) fa[i][k]=fa[fa[i][k-1]][k-1];
    }
}
int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int k=lgN-1;~k;k--) if(dep[fa[x][k]]>=dep[y]) x=fa[x][k];
    if(x==y) return x;
    for(int k=lgN-1;~k;k--) if(fa[x][k]!=fa[y][k]) x=fa[x][k],y=fa[y][k];
    return fa[x][0];
}

int ql[N],qr[N],qlca[N],qu[N],qv[N],p[N];
short blk[N<<1];
bool Cmp(int x,int y){
    if(blk[ql[x]]!=blk[ql[y]]) return blk[ql[x]]<blk[ql[y]];
    else return (qr[x]<qr[y])^(blk[ql[x]]&1);
}

int abuc[N],bbuc[N],cbuc[N],a[N],b[N],c[N],ans[N];
inline void Work(int &res,int x,int *t,int *buc){
    res-=(a[pos[x]]!=b[pos[x]])&&(a[pos[x]]!=c[pos[x]])&&(b[pos[x]]!=c[pos[x]]);
    t[pos[x]]=(buc[x]^=1)?val[x]:rval[x];
    res+=(a[pos[x]]!=b[pos[x]])&&(a[pos[x]]!=c[pos[x]])&&(b[pos[x]]!=c[pos[x]]);
}

int main(){
    cin>>id>>n>>m>>q;
    for(int i=1,f;i<=n;i++){
        cin>>f>>pos[i]>>val[i];
        AdEg(f,i);        
    }
    DFS(0);
    Init();
    
    int B=sqrt(ecnt);
    for(int i=1;i<=ecnt;i++) blk[i]=(i-1)/B+1;
    for(int i=1;i<=q;i++){
        cin>>qu[i]>>qv[i];
        if(st[qu[i]]>st[qv[i]]) swap(qu[i],qv[i]);
        qlca[i]=LCA(qu[i],qv[i]);
        ql[i]=st[qu[i]];
        qr[i]=st[qv[i]];
        p[i]=i;
    }
    sort(p+1,p+q+1,Cmp);
    for(int i=1,ia=1,ib=1,ic=1,res=0;i<=q;i++){
        while(ia<st[qu[p[i]]]) Work(res,elr[++ia],a,abuc);
        while(ia>st[qu[p[i]]]) Work(res,elr[ia--],a,abuc);
        while(ib<st[qv[p[i]]]) Work(res,elr[++ib],b,bbuc);
        while(ib>st[qv[p[i]]]) Work(res,elr[ib--],b,bbuc);
        while(ic<st[qlca[p[i]]]) Work(res,elr[++ic],c,cbuc);
        while(ic>st[qlca[p[i]]]) Work(res,elr[ic--],c,cbuc);
        ans[p[i]]=res;
    }
    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

    return 0;
}