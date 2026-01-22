#include<bits/stdc++.h>

using namespace std;

const int N=4e5+9;

int fa[N],f[11][N],n,m;
int Find(int x,int *fa){
    // cout<<x<<' '<<fa[x]<<endl;
    if(fa[x]==x) return x;
    else return fa[x]=Find(fa[x],fa);
}
void Merge(int x,int y,int *fa){
    fa[Find(y,fa)]=Find(x,fa);
}

int main(){
    int T;
    cin>>T;
    while(T--){
        vector<pair<int,int>> q[11];
        cin>>n>>m;
        for(int i=1,a,k,d;i<=m;i++){
            cin>>a>>d>>k;
            q[d].push_back({a,a+k*d});
        }
        for(int d=1;d<=10;d++){
            iota(f[d]+1,f[d]+n+200+1,1);
            for(pair<int,int> p:q[d]){
                for(int i=Find(p.first,f[d]);i+d<=p.second;i=Find(i,f[d])){
                    Merge(i+d,i,f[d]);
                }
            }
        }
        iota(fa+1,fa+n+200+1,1);
        for(int i=1;i<=n;i++){
            for(int d=1;d<=10;d++) Merge(Find(i,f[d]),i,fa);
        }

        int cnt=0;
        for(int i=1;i<=n;i++) if(Find(i,fa)==i) cnt++;
        cout<<cnt<<endl;
    }

    return 0;
}