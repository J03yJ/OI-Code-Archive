#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;
const int inf=2e9;

ifstream fin("press.in");
ofstream fout("press.out");
#define cin fin
#define cout fout

pair<int,int> a[N];

int fi[N<<1],ne[N<<4],to[N<<4],w[N<<4],adj=1;
void adeg(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}
int lev[N<<1],s,t;
bool bfs(){
    for(int i=1;i<=t;i++) lev[i]=0;
    lev[s]=1;lev[t]=0;
    queue<int>q;
    q.push(s);
    while(q.size()){
        int x=q.front();
        q.pop();
        if(x==t) return 1;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(!w[i]) continue ;
            if(lev[y]) continue ;
            lev[y]=lev[x]+1;
            q.push(y);
        }
    }
    return 0;
}
int dfs(int x,int mn){
    if(x==t) return mn;
    int k=mn;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(!w[i]) continue ;
        if(lev[y]!=lev[x]+1) continue ;
        int tmp=dfs(y,min(k,w[i]));
        k-=tmp;
        w[i]-=tmp;
        w[i^1]+=tmp;
        if(!k) return mn;
    }
    return mn-k;
}

int main(){
    int n,V;
    cin>>V>>n;
    for(int i=1;i<=n;i++) cin>>a[i].first;
    for(int i=1;i<=n;i++) cin>>a[i].second;
    sort(a+1,a+n+1);

    s=n+n+n+1;t=s+1;
    for(int i=1;i<=n;i++) adeg(s,i,1),adeg(i,s,0);
    for(int i=1;i<=n;i++) adeg(i+n,t,1),adeg(t,i+n,0);

    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            if(abs(a[i].second-a[j].second)<=a[i].first-a[j].first){
                adeg(i,j+n,inf);
                adeg(j+n,i,0);
            }
        }
    }

    int sum=0;
    while(bfs()) sum+=dfs(s,inf);

    cout<<n-sum<<endl;

    return 0;
}