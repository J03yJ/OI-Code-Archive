#include<bits/stdc++.h>

using namespace std;

ifstream fin("interact.in");
ofstream fout("interact.out");
#define cin fin
#define cout fout

const int N=6e5+9;
const int p=998244353;
#define int long long

int A[N];
vector<int> Frp[N],Grp[N];
int cnt,F[N],G[N],pF[N],pG[N];
void clear(){
    for(int i=0;i<=cnt;i++) Frp[i].clear(),Grp[i].clear();
}

signed main(){
    A[0]=1;
    for(int i=1;i<=6e5;i++) A[i]=A[i-1]*i%p;
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            Frp[0].push_back(i);
            Grp[0].push_back(i);
            F[i]=G[i]=0;
        }
        int cur=0;
        for(int q=1;q<=m;q++){
            cur=cnt+1;
            for(int i=1;i<=n;i++) cin>>pF[i];
            for(int i=1;i<=n;i++) cin>>pG[i];

            map<pair<int,int>,int> mp;
            for(int i=1;i<=n;i++){
                if(!mp[{F[i],pF[i]}]) mp[{F[i],pF[i]}]=++cnt;
                Frp[mp[{F[i],pF[i]}]].push_back(i);
                F[i]=mp[{F[i],pF[i]}];
            }
            for(int i=1;i<=n;i++){
                if(!mp[{G[i],pG[i]}]) mp[{G[i],pG[i]}]=++cnt;
                Grp[mp[{G[i],pG[i]}]].push_back(i);
                G[i]=mp[{G[i],pG[i]}];
            }
        }

        int ans=1;
        for(int i=cur;i<=cnt;i++){
            if(Frp[i].size()!=Grp[i].size()){
                ans=0;
                continue ;
            }
            ans=ans*A[Frp[i].size()]%p;
        }
        cout<<ans<<endl;

        clear();
    }
    return 0;
}