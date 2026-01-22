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
    Data(int t){memset(f,0,sizeof f);f[0]=t;}
    int& operator [](int pos){return f[pos];}
    inline Data operator +(Data x){
        Data res;
        for(int i=0;i<=k+1;i++) res[i]=Add(f[i],x[i]);
        return res;
    }
    inline Data operator -(Data x){
        Data res;
        for(int i=0;i<=k+1;i++) res[i]=Sub(f[i],x[i]);
        return res;
    }
    inline void operator +=(Data x){
        for(int i=0;i<=k+1;i++) AddAs(f[i],x[i]);
    }
    inline void operator -=(Data x){
        for(int i=0;i<=k+1;i++) SubAs(f[i],x[i]);
    }
    inline void operator <<=(int p){
        for(int i=k+1;i>=0;i--) f[i]=i>=p?f[i-p]:0;
    }
};

signed main(){
    cin>>n>>k;
    for(int i=1,u,v;i<n;i++) cin>>u>>v,AddEdge(u,v),AddEdge(v,u);

    DFS(1);

    multiset<int> s;
    for(int i=2;i<=n;i++) s.insert(i);
    s.insert(0),s.insert(0);
    
    vector<int> stk[2];
    vector<Data> sum[2];
    stk[0].push_back(1);
    sum[0].push_back(Data(1));

    for(int r=1;r<=n;r++){
        if(fa[r]<r){
            vector<int> tmp;
            vector<Data> dp;
            while(stk[0].size()&&fa[r]<stk[0].back()){
                tmp.push_back(stk[0].back());
                stk[0].pop_back();
                dp.push_back(sum[0].back());
                sum[0].pop_back();
                if(sum[0].size()) dp.back()-=sum[0].back();
            }
            while(stk[1].size()&&fa[r]<stk[1].back()){
                stk[1].pop_back();
                sum[1].pop_back();
            }
            while(tmp.size()){
                stk[1].push_back(tmp.back());
                tmp.pop_back();
                if(sum[1].size()) dp.back()+=sum[1].back();
                sum[1].push_back(dp.back());
                dp.pop_back();
            }
        }

        for(int i=fi[r];i;i=ne[i]){
            int u=to[i];
            if(u==fa[r]) continue ;
            s.erase(u);
        }
        auto it=prev(s.upper_bound(r)),jt=prev(it);
        int l0=*it+1,r0=r,l1=*jt+1,r1=*it;

        Data res;
        int lp0=lower_bound(stk[1].begin(),stk[1].end(),l0)-stk[1].begin()-1;
        int rp0=upper_bound(stk[1].begin(),stk[1].end(),r0)-stk[1].begin()-1;
        res+=(rp0>=0?sum[1][rp0]:Data())-(lp0>=0?sum[1][lp0]:Data());
        int lp1=lower_bound(stk[0].begin(),stk[0].end(),l1)-stk[0].begin()-1;
        int rp1=upper_bound(stk[0].begin(),stk[0].end(),r1)-stk[0].begin()-1;
        res+=(rp1>=0?sum[0][rp1]:Data())-(lp1>=0?sum[0][lp1]:Data());
        res<<=1;

        if(r==n){
            for(int i=1;i<=k+1;i++) cout<<res[i]<<endl;
            break ;
        }

        stk[0].push_back(r+1);
        if(sum[0].size()) res+=sum[0].back();
        sum[0].push_back(res);
    }

    return 0;
}