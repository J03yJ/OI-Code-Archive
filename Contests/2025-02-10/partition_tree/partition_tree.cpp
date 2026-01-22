#include<bits/stdc++.h>

using namespace std;

ifstream fin("partition_tree.in");
ofstream fout("partition_tree.out");
#define cin fin
#define cout fout
#define endl '\n'

const int mod=998244353;
const int N=3e5+9;
const int K=3e2+9;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline int Add(int x,int y){x+=y;if(x>mod) x-=mod;return x;};
inline void SubAs(int &x,int y){x-=y;if(x<0) x+=mod;}
inline int Sub(int x,int y){x-=y;if(x<0) x+=mod;return x;}

int fi[N],ne[N<<1],to[N<<1],adj,n,k;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int fa[N];
void DFS(int x){
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        DFS(y);
    }
}

struct Data{
    int f[K];
    Data(){memset(f,0,sizeof f);}
    int& operator [](int pos){return f[pos];}
    Data operator +(Data x){
        Data res;
        for(int i=0;i<=k+1;k++) res[i]=Add(f[i],x[i]);
        return res;
    }
    Data operator -(Data x){
        Data res;
        for(int i=0;i<=k+1;k++) res[i]=Sub(f[i],x[i]);
        return res;
    }
};

signed main(){
    cin>>n>>k;
    for(int i=1,u,v;i<n;i++) cin>>u>>v,AddEdge(u,v),AddEdge(v,u);

    multiset<int> s;
    for(int i=1;i<=n;i++) s.insert(i);
    s.insert(0),s.insert(0);

    vector<int> stk[2];
    vector<Data> sum[2];
    for(int r=1;r<=n;r++){
        for(int i=fi[r];i;i=ne[i]){
            int u=to[r];
            if(u==fa[r]) continue ;
            s.erase(u);
        }
        auto it=prev(s.lower_bound(r)),jt=prev(it);

        if(fa[r]<r){
            queue<int> tmp;
            queue<Data> dp;
            while(stk[0].size()&&fa[r]>stk[0].back()){
                tmp.push(stk[0].back());
                stk[0].pop_back();
                dp.push();
            }
        }
    }

    return 0;
}