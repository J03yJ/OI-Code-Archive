#include<bits/stdc++.h>

using namespace std;

ifstream fin("ono.in");
ofstream fout("ono.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;

int a[N],sl[N],sr[N],b[N],n,m;

namespace Brute{
    vector<int> tmp[N];
    inline void Solve(){
        for(int t=1;t<=n;t++){
            ll ans=0;
            for(int i=1;i<=m;i++) if(sl[i]<=t&&t<=sr[i]) tmp[sl[i]].push_back(i);
            priority_queue<array<int,3>> q;
            for(int i=1,j=1;i<=n;i++){
                int cur=a[i];
                for(int j:tmp[i]) q.push({-sr[j],sl[j],b[j]});
                while(q.size()&&i>=q.top()[1]){
                    int l=q.top()[1],r=-q.top()[0],rem=q.top()[2];
                    q.pop();
                    if(i>r) continue ;
                    ans+=min(rem,cur);
                    if(rem>cur){
                        rem-=cur;
                        q.push({-r,l,rem});
                        break ;
                    }else cur-=rem;
                }
            }
            cout<<ans<<' ';
            for(int i=1;i<=n;i++) tmp[i].clear();
        }
        cout<<endl;
    }
}
namespace AllZero{
    inline bool Check(){for(int i=1;i<=n;i++) if(a[i]) return 0;return 1;}
    inline void Solve(){for(int i=1;i<=n;i++) cout<<0<<' ';cout<<endl;}
}
namespace BllZero{
    inline bool Check(){for(int i=1;i<=m;i++) if(b[i]) return 0;return 1;}
    inline void Solve(){for(int i=1;i<=n;i++) cout<<0<<' ';cout<<endl;}
}
namespace NoInter{
    ll sum[N];
    int bel[N];
    inline bool Check(){for(int i=1;i<m;i++) if(sr[i]>=sl[i+1]) return 0;return 1;}
    inline void Solve(){
        for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
        for(int i=1;i<=m;i++){
            for(int j=sl[i];j<=sr[i];j++) bel[j]=i;
            b[i]=min(ll(b[i]),sum[sr[i]]-sum[sl[i]-1]);
        }
        for(int i=1;i<=n;i++) cout<<b[bel[i]]<<' ';cout<<endl;
    }
}
namespace Prefix{
    ll suma[N],sumb[N],res[N];
    inline bool Check(){for(int i=1;i<=n;i++) if(sl[i]!=1) return 0;return 1;}
    inline void Solve(){
        for(int i=1;i<=n;i++) suma[i]=suma[i-1]+a[i];
        for(int i=1;i<=m;i++) sumb[i]=sumb[i-1]+a[i];
        
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>sl[i]>>sr[i]>>b[i];

    if(AllZero::Check()) AllZero::Solve();
    else if(BllZero::Check()) BllZero::Solve();
    else if(NoInter::Check()) NoInter::Solve();
    else Brute::Solve();

    return 0;
}