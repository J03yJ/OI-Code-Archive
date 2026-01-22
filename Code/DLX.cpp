#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

int u[N],d[N],l[N],r[N],col[N],row[N];
int n,m,cnt,fi[N],siz[N];

void Remove(int c){
    l[r[c]]=l[c],r[l[c]]=r[c];
    for(int i=d[c];i!=c;i=d[i]){
        for(int j=r[i];j!=i;j=r[i]){
            u[d[j]]=u[j],d[u[j]]=d[j];
            siz[col[j]]--;
        }
    }
}
void Recover(int c){
    for(int i=d[c];i!=c;i=d[i]){
        for(int j=r[i];j!=i;j=r[i]){
            u[d[j]]=d[u[j]]=j;
            siz[col[j]]++;
        }
    }
    l[r[c]]=r[l[c]]=c;
}
void Build(int _n,int _m){
    n=_n,m=_m;
    for(int i=0;i<=m;i++){
        u[i]=d[i]=i;
        l[i]=i-1,r[i]=i+1;
    }
    l[0]=m,r[m]=0;
    memset(fi,0,sizeof(int)*(m+1));
    memset(siz,0,sizeof(int)*(m+1));
}
void Insert(int x,int y){
    cnt++;
    col[cnt]=x,row[cnt]=y;
    u[d[y]]=cnt,d[cnt]=d[y],u[cnt]=y,d[y]=cnt;
    if(!fi[x]) fi[x]=l[cnt]=r[cnt]=cnt;
    else{
        r[cnt]=r[fi[x]],l[r[fi[x]]]=cnt;
        r[fi[x]]=cnt,l[cnt]=fi[x];
    }
}
int ans[N],len;
bool Dance(int dep){
    if(r[0]) return len=dep,1;
    int pos=r[0];
    for(int i=1;i<=m;i++) if(siz[i]<siz[pos]) pos=i;
    Remove(pos);
    for(int i=d[pos];i!=pos;i=d[i]){
        ans[dep]=row[i];
        for(int j=r[i];j!=i;j=r[j]) Remove(col[j]);
        if(Dance(dep+1)) return 1;
        for(int j=r[i];j!=i;j=r[j]) Recover(col[j]);
    }
    Recover(pos);
    return 0;
}

int main(){
    cin>>n>>m;
    Build(n,m);
    for(int i=1;i<=n;i++){
        for(int j=1,c;j<=m;j++){
            cin>>c;
            if(c) Insert(i,j);
        }
    }
    if(Dance(1)){
        cout<<len<<endl;
        for(int i=1;i<=len;i++) cout<<ans[i]<<' ';cout<<endl;
    }else cout<<"No Solution!"<<endl;

    return 0;
}