#include<bits/stdc++.h>

using namespace std;

ifstream fin("memory.in");
ofstream fout("memory.out");
#define cin fin
#define cout fout
#define endl '\n'

#define ssiz(x) (signed)x.size();
const int N=1e6+9;
const int lgN=2e1+1;

int a[N],ql[N],qr[N],qx[N],n,q;
long long ans[N];
string s;

vector<array<int,3>> qry[N];
vector<int> son[N];
int dfn[N],siz[N],dcnt;
void DFS(int x){
    siz[x]=1;
    dfn[x]=++dcnt;
    for(int y:son[x]){
        DFS(y);
        siz[x]+=siz[y];
    }
}
long long tr[N];
void Add(int x,long long k){
    while(x<=dcnt){
        tr[x]+=k;
        x+=x&-x;
    }
}
void Add(int l,int r,long long k){
    Add(l,k),Add(r+1,-k);
}
long long Ask(int x){
    long long sum=0;
    while(x){
        sum+=tr[x];
        x&=x-1;
    }
    return sum;
}

signed main(){
    cin>>q>>s;
    n=ssiz(s);
    s=" "+s;
    for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i]>>qx[i];

    for(int i=2,j=0;i<=n;i++){
        while(j&&s[j+1]!=s[i]) j=a[j];
        if(s[j+1]==s[i]) j++;
        a[i]=j;
    }

    for(int i=1;i<=q;i++){
        qry[ql[i]-1].push_back({qx[i],i,-1});
        qry[qr[i]].push_back({qx[i],i,1});
    }
    for(int i=1;i<=n;i++) son[a[i]].push_back(i);
    DFS(0);

    for(int i=1;i<=n;i++){
        for(int u=i;u;u=a[u]) Add(dfn[u],dfn[u]+siz[u]-1,u-a[u]);
        for(auto t:qry[i]) ans[t[1]]+=Ask(dfn[t[0]])*t[2];
    }
    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

    return 0;
}