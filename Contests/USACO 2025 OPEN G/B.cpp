#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
const int B=4e2;

int a[N],cnt[N],mx[N],mn[N],n,q;
set<int> s[N],all,big;
inline void Update(int x){
    mx[x]=mx[x+1],mn[x]=mn[x+1];
    if(s[x].size()){
        mx[x]=max(mx[x],*s[x].rbegin());
        mn[x]=min(mn[x],*s[x].begin());
    }
}
inline void Veto(int x){
    all.erase(cnt[x]);
    s[cnt[x]].erase(x);
    Update(cnt[x]);
    if(cnt[x]>=(B>>1)) big.erase(x);
    cnt[x]--;
    if(cnt[x]>=(B>>1)) big.insert(x);
    all.insert(cnt[x]);
    s[cnt[x]].insert(x);
}
inline void Vote(int x){
    all.erase(cnt[x]);
    s[cnt[x]].erase(x);
    if(cnt[x]>=(B>>1)) big.erase(x);
    cnt[x]++;
    if(cnt[x]>=(B>>1)) big.insert(x);
    all.insert(cnt[x]);
    s[cnt[x]].insert(x);
    Update(cnt[x]);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];

    mx[n+1]=0,mn[n+1]=n+1;
    for(int i=1;i<=n;i++) cnt[a[i]]++;
    for(int i=1;i<=n;i++) s[cnt[i]].insert(i);
    for(int i=n;i>=0;i--) Update(i);
    for(int i=1;i<=n;i++) all.insert(cnt[i]);
    for(int i=1;i<=n;i++) if(cnt[i]>=(B>>1)) big.insert(i);

    while(q--){
        int i,x;
        cin>>i>>x;

        Veto(a[i]);
        a[i]=x;
        Vote(a[i]);

        int lim=*all.rbegin();
        if(lim<=B){
            int ans=0;
            for(int i=1;i<=lim;i++){
                ans=max(ans,mx[max(lim-i,1)]-mn[i]);
                ans=max(ans,mx[i]-mn[max(lim-i,1)]);
            }
            cout<<ans<<endl;
        }else{
            int ans=0;
            for(int i:big){
                ans=max(ans,mx[max(lim-cnt[i],1)]-i);
                ans=max(ans,i-mn[max(lim-cnt[i],1)]);
            }
            cout<<ans<<endl;
        }
    }

    return 0;
}