#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e5+9;
const int SQ=3.5e2+9;
const int mod=998244353;

int c[N],pre[N],tmp[N],n,m;
int blk[N],L[N],R[N],B;
int a[N],f[N],suf[N];
vector<int> val[SQ],res[SQ];

void Add(int &x,int y){
    x+=y;
    if(x>mod) x-=mod;
}
void Init(){
    B=sqrt(n);
    for(int i=1;i<=n;i++){
        blk[i]=(i-1)/B+1;
        if(!L[blk[i]]) L[blk[i]]=i;
        R[blk[i]]=i;
    }
}
void Build(int x,int flag){
    if(flag){
        suf[R[x]]=a[R[x]];
        for(int i=R[x]-1;i>=L[x];i--) suf[i]=suf[i+1]+a[i];

        val[x]=vector<int>(1,-1e9);
        for(int i=L[x];i<=R[x];i++) val[x].push_back(suf[i]);
        sort(val[x].begin(),val[x].end());
        val[x].resize(unique(val[x].begin(),val[x].end())-val[x].begin());
    }

    res[x]=vector<int>(val[x].size(),0);
    for(int i=L[x];i<=R[x];i++){
        Add(res[x][lower_bound(val[x].begin(),val[x].end(),suf[i])-val[x].begin()],f[i-1]);
    }
    for(int i=1;i<res[x].size();i++) Add(res[x][i],res[x][i-1]);
}
void Modify(int x,int k){
    a[x]=k;
    Build(blk[x],1);
}
int Query(){
    int ans=0,sum=0;
    for(int x=blk[n];x>=1;x--){
        Add(ans,res[x][upper_bound(val[x].begin(),val[x].end(),m-sum)-val[x].begin()-1]);
        sum+=suf[L[x]];
    }
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>c[i];

    for(int i=1;i<=n;i++){
        pre[i]=tmp[c[i]];
        tmp[c[i]]=i;
    }

    Init();
    for(int i=1;i<=blk[n];i++) Build(i,1);

    f[0]=1;
    for(int i=1;i<=n;i++){
        if(pre[pre[i]]) Modify(pre[pre[i]],0);
        if(pre[i]) Modify(pre[i],-1);
        Modify(i,1);
        f[i]=Query();
        Build(blk[i],0);
    }

    cout<<f[n]<<endl;

    return 0;
}