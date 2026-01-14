#include<bits/stdc++.h>

using namespace std;

ifstream fin("card.in");
ofstream fout("card.out");
#define cin fin
#define cout fout
#define endl '\n'

#define fir(x) (x).first
#define sec(x) (x).second
using pii=pair<int,int>;
const int N=2e3+9;

int n,q;
pii a[N];
vector<pii> f[N][N];

signed main(){
    int Tid,T;
    cin>>Tid>>T;
    while(T--){
        cin>>n>>q;
        for(int i=1;i<=n;i++) cin>>fir(a[i])>>sec(a[i]);
        for(int i=1;i<=n;i++) f[i][i]={a[i]};
        for(int len=2;len<=n;len++){
            for(int i=1;i<=n-len+1;i++){
                int j=i+len-1;
                f[i][j].clear();
                for(int k=i;k<j;k++){
                    for(pii p:f[i][k]){
                        for(pii q:f[k+1][j]){
                            f[i][j].push_back(pii(min(fir(p),fir(q)),min(sec(p),sec(q))));
                            f[i][j].push_back(pii(max(fir(p),fir(q)),max(sec(p),sec(q))));
                        }
                    }
                }
                sort(f[i][j].begin(),f[i][j].end());
                f[i][j].erase(unique(f[i][j].begin(),f[i][j].end()),f[i][j].end());
            }
        }
        while(q--){
            int l,r,x,y;
            cin>>l>>r>>x>>y;
            auto it=lower_bound(f[l][r].begin(),f[l][r].end(),pii(x,y));
            if(it==f[l][r].end()||*it!=pii(x,y)) cout<<0<<endl;
            else cout<<1<<endl;
        }
    }

    return 0;
}