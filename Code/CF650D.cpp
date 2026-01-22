#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>

using namespace std;

const int N=2e6+9;
const int inf=1e9+7;

int a[N],f[N],g[N],cnt[N],imp[N],n,m;
int qpos[N],qk[N],ans[N];
vector<int> q[N];

int val[N],tot;
void Init(){
    sort(val+1,val+tot+1);
    tot=unique(val+1,val+tot+1)-val-1;
}
int Get(int x){
    return lower_bound(val+1,val+tot+1,x)-val;
}

int tr[N];
void Insert(int pos,int k){
    while(pos<=tot){
        tr[pos]=max(tr[pos],k);
        pos+=pos&-pos;
    }
}
int Query(int pos){
    int res=0;
    while(pos){
        res=max(res,tr[pos]);
        pos&=pos-1;
    }
    return res;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>qpos[i]>>qk[i],q[qpos[i]].push_back(i),ans[i]=1;

    for(int i=1;i<=n;i++) val[++tot]=a[i],val[++tot]=inf-a[i];
    for(int i=1;i<=m;i++) val[++tot]=qk[i],val[++tot]=inf-qk[i];
    Init();

    for(int i=1;i<=n;i++){
        f[i]=Query(Get(a[i])-1)+1;
        for(int j:q[i]) ans[j]+=Query(Get(qk[j])-1);
        Insert(Get(a[i]),f[i]);
    }
    for(int i=1;i<=tot;i++) tr[i]=0;
    for(int i=n;i>=1;i--){
        g[i]=Query(Get(inf-a[i])-1)+1;
        for(int j:q[i]) ans[j]+=Query(Get(inf-qk[j])-1);
        Insert(Get(inf-a[i]),g[i]);
    }

    int res=0;
    for(int i=1;i<=n;i++) res=max(res,f[i]);
    for(int i=1;i<=n;i++) if(f[i]+g[i]-1==res) cnt[f[i]]++;
    for(int i=1;i<=n;i++) if(f[i]+g[i]-1==res&&cnt[f[i]]==1) imp[i]=1;

    for(int i=1;i<=m;i++){
        if(imp[qpos[i]]) ans[i]=max(ans[i],res-1);
        else ans[i]=max(ans[i],res);
        cout<<ans[i]<<endl;
    }

    return 0;
}