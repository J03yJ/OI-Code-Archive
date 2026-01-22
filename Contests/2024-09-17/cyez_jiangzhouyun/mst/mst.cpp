#include<bits/stdc++.h>

using namespace std;

ifstream fin("mst.in");
ofstream fout("mst.out");
#define cin fin
#define cout fout

namespace IO{
    const int P = (1ll << 31) - 1;
    int N, M, V, A, B;
    void GetSeed(int &n, int &m, int &v){
        cin >> N >> M >> V >> A >> B;
        n = N, m = M, v = V;
    }
    int GetInt(){
        A = ((A ^ B) + (B >> 16) + (B << 16)) & P;
        B = ((A ^ B) + (A >> 16) + (A << 16)) & P;
        return (A ^ B) % V;
    }
    int GetPos(){
        A = ((A ^ B) + (B >> 16) + (B << 16)) & P;
        B = ((A ^ B) + (A >> 16) + (A << 16)) & P;
        return (A ^ B) % N + 1;
    }
    void GetSeg(int &l, int &r){
        l = GetPos(), r = GetPos();
        if (l > r)
            std::swap(l, r);
    }
}

#define Allc(x) x.begin(),x.end()
const int N=2e5+9;
const int lgN=20;
int a[N],fa[N],n,m,v;
int Find(int x){
    if(fa[x]==x) return x;
    else return fa[x]=Find(fa[x]);
}

int main(){
    IO::GetSeed(n,m,v);
    for(int i=1;i<=n;i++) a[i]=IO::GetInt();    
    for(int i=1,l,r;i<=m;i++){
        IO::GetSeg(l,r);
        // cout<<l<<' '<<r<<endl;
        iota(fa+l,fa+r+1,l);
        // for(int j=l;j<=r;j++) cout<<fa[j]<<' ';cout<<endl;
        vector<array<int,3>> edge;
        for(int j=l;j<=r;j++){
            for(int k=j+1;k<=r;k++){
                edge.push_back({j,k,a[k]-a[j]});
            }
        }
        sort(Allc(edge),[](auto x,auto y){return x[2]<y[2];});
        long long res=0,cnt=0;
        for(auto e:edge){
            if(cnt==r-l) break ;
            if(Find(e[0])==Find(e[1])) continue ;
            fa[Find(e[0])]=Find(e[1]);
            res+=e[2];
            cnt++;
        }
        cout<<res<<endl;
    }

    return 0;
}