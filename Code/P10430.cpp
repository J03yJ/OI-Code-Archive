#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=3e5+9;
const int lgN=2e1;

ll a[N],b[N],r[N],sum[N],scnt[N],w[N][lgN],d;
int cnt[N],prv[N][lgN],n,q;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>d;
    for(int i=1;i<=n;i++) cin>>a[i];

    for(int i=1;i<=n;i++){
        r[i]=a[i]%d;
        cnt[i]=cnt[i-1]+(r[i]<r[i-1]);
        scnt[i]=scnt[i-1]+cnt[i];
        b[i]=a[i]/d-cnt[i];
        sum[i]=sum[i-1]+a[i]/d;
    }
    vector<int> stk;
    for(int i=1;i<=n;i++){
        while(stk.size()&&b[stk.back()]>=b[i]) stk.pop_back();
        if(stk.size()) prv[i][0]=stk.back();
        w[i][0]=(i-prv[i][0])*b[i];
        stk.push_back(i);
    }
    for(int k=1;k<lgN;k++){
        for(int i=1;i<=n;i++){
            prv[i][k]=prv[prv[i][k-1]][k-1];
            w[i][k]=w[i][k-1]+w[prv[i][k-1]][k-1];
        }
    }

    cin>>q;
    while(q--){
        int l,r;
        cin>>l>>r;

        int p=r;
        ll ans=0;
        for(int k=lgN-1;~k;k--){
            if(prv[p][k]>=l){
                ans-=w[p][k];
                p=prv[p][k];
            }
        }
        if(b[p]+cnt[l]<0){
            cout<<-1<<endl;
            continue ;
        }

        ans+=sum[r]-sum[l-1];
        ans-=scnt[r]-scnt[l-1];
        ans-=(p-l+1)*b[p];

        cout<<ans<<endl;
        
    }

    return 0;
}