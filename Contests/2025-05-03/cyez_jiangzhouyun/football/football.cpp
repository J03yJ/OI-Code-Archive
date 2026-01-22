#include<bits/stdc++.h>

using namespace std;

ifstream fin("football.in");
ofstream fout("football.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1.5e3+9;

int vis[N],id[N],t[N],n,k;
bitset<N> a[N],b[N];
inline int Insert(bitset<N> x,int p){
    int cnt=1;
    for(int i=k-1;~i;i--){
        if(!x[i]) continue ;
        if(b[i].none()){
            b[i]=x;
            id[i]=p;
            t[i]=cnt;
            return 0;
        }else x^=b[i],cnt+=t[i];
    }
    return cnt;
}
inline void Flip(bitset<N> x){
    for(int i=k-1;~i;i--){
        if(!x[i]) continue ;
        vis[id[i]]^=1;
        x^=b[i];
    }
}
inline void Topo(){
    for(int i=0;i<k;i++){
        if(!vis[id[i]]) continue ;
        vis[id[i]]=0;
        Flip(a[id[i]]);
    }
}

signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        for(int j=0;j<k;j++) if(s[j]=='1') a[i].set(j,1);
    }

    vector<int> p[2];
    for(int i=1;i<=n;i++){
        int c=Insert(a[i],i);
        if(c) p[c&1].push_back(i);
    }
    if(p[0].size()){
        Flip(a[p[0][0]]),vis[p[0][0]]^=1;
        Topo();
        int cnt=0;
        for(int i=1;i<=n;i++) cnt+=vis[i];
        cnt>>=1;
        for(int i=1;i<=n;i++){
            if(!vis[i]) cout<<0;
            else if(cnt>0) cout<<1,cnt--;
            else cout<<2;
        }
        cout<<endl;
    }else if(p[1].size()>1){
        Flip(a[p[1][0]]),vis[p[1][0]]^=1;
        Flip(a[p[1][1]]),vis[p[1][1]]^=1;
        Topo();
        int cnt=0;
        for(int i=1;i<=n;i++) cnt+=vis[i];
        cnt>>=1;
        for(int i=1;i<=n;i++){
            if(!vis[i]) cout<<0;
            else if(cnt>0) cout<<1,cnt--;
            else cout<<2;
        }
        cout<<endl;
    }else cout<<'*'<<endl;
    
    return 0;
}