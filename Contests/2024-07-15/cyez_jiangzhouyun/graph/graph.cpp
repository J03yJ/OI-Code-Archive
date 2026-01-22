#include<bits/stdc++.h>

using namespace std;

ifstream fin("graph.in");
ofstream fout("graph.out");
#define cin fin
#define cout fout

const int N=3e5+9;

int fi[N],ne[N],to[N],adj;
void adeg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int dfn[N],low[N],dcnt;
long long ans=0;
vector<int> s;
bool ins[N];
void tj(int x){
    low[x]=dfn[x]=++dcnt;
    s.push_back(x);
    ins[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(!dfn[y]){
            tj(y);
            low[x]=min(low[x],low[y]);
        }else if(ins[y]) low[x]=min(low[x],dfn[y]);
    }
    if(low[x]==dfn[x]){
        long long cnt=0;
        while(s.size()){
            int p=s.back();
            s.pop_back();
            ins[p]=0;
            cnt++;
            if(p==x) break ;
        }
        ans+=cnt*(cnt-1)/2;
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        adeg(x,y);

        ans=0;
        s.clear();
        for(int j=1;j<=n;j++) dfn[j]=low[j]=0;
        for(int j=1;j<=n;j++) if(!dfn[j]) tj(j);

        cout<<ans<<endl;
    }

    return 0;
}