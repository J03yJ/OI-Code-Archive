#include<bits/stdc++.h>

using namespace std;

ifstream fin("blocktree.in");
ofstream fout("blocktree.out");
#define cin fin
#define cout fout
#define endl '\n'

#define int long long
#define ssiz(x) (signed)x.size()

const int N=2e6+9;

int fi[N],ne[N],to[N],d[N],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    d[x]++;
}

int dep[N],fa[N],p[N],nn,n,m;
void DFS(int x){
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        dep[y]=dep[x]+1;
        DFS(y);
    }
}
long long mmax,mmin,np;
void Get(int k){
    mmax=0,mmin=0,np=0;
    for(int i=1;i<=nn;i++){
        if((dep[i]^k^1)&1) np++;
        else{
            mmax+=1ll*d[i]*(d[i]-1)/2;
            mmin+=d[i]<=2?d[i]-1:d[i];
        }
    }
}
void Solve(int k){
    int tmp=m-mmin;
    for(int i=1,cnt=0;i<=nn;i++){
        if((dep[i]^k)&1) continue ;
        p[i]=++cnt;
    }
    for(int i=1;i<=nn;i++) cout<<p[i]<<' ';cout<<endl;
    for(int i=1;i<=nn;i++){
        if((dep[i]^k^1)&1) continue ;
        vector<int> v;
        for(int j=fi[i];j;j=ne[j]) v.push_back(p[to[j]]);
        if(v.size()<=2) cout<<v[0]<<' '<<v[1]<<endl;
        else{
            for(int j=0;j<ssiz(v);j++) cout<<v[j]<<' '<<v[(j+1)%ssiz(v)]<<endl;
            for(int j=0;j<ssiz(v)&&tmp;j++){
                for(int k=j+2;k<ssiz(v)&&tmp;k++){
                    if(k==(j-1+ssiz(v))%ssiz(v)) continue ;
                    tmp--;
                    cout<<v[j]<<' '<<v[k]<<endl;
                }
            }
        }
    }
}
int Check(int k){
    for(int i=1;i<=nn;i++){
        if((dep[i]^k^1)&1) continue ;
        if(d[i]==1) return 0;
    }
    return 1;
}

signed main(){
    cin>>nn>>n>>m;
    for(int i=1,u,v;i<nn;i++){
        cin>>u>>v;
        AdEg(u,v);
        AdEg(v,u);
    }

    DFS(1);
    Get(0);
    if(np==n&&m>=mmin&&m<=mmax&&Check(0)){
        cout<<"Yes"<<endl;
        Solve(0);
    }else{
        Get(1);
        if(np==n&&m>=mmin&&m<=mmax&&Check(1)){
            cout<<"Yes"<<endl;
            Solve(1);
        }else cout<<"No"<<endl;
    }

    return 0;
}