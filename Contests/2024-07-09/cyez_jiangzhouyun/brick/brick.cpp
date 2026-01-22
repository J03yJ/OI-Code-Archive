#include<bits/stdc++.h>

using namespace std;

ifstream fin("brick.in");
ofstream fout("brick.out");
#define cin fin
#define cout fout

const int N=1e5+9;
const int V=2e6+9;
const int p=998244353;

int a[N],b[N],ql[N],qr[N],K;
int blk[N],L[N],R[N];
int per[N],ans[N];
bool cmp(int x,int y){
    if(blk[ql[x]]!=blk[ql[y]]) return blk[ql[x]]<blk[ql[y]];
    else return qr[x]<qr[y];
}

int f[V],cnt[V];
vector<pair<int,int>> uf,ucnt,ucnt_;
int calc(int x){
    return (x-f[x])/K+1;
}
void addr(int x,int &res){
    uf.push_back({x,f[x]});
    ucnt.push_back({f[x],cnt[f[x]]});
    // cout<<x<<' '<<f[x]<<' '<<calc(x)<<endl;
    if(f[x]) cnt[f[x]]--;
    res=(res-calc(x)+p)%p;
    f[x]=min(f[x],x);
    if(x>=K) f[x]=min(f[x],f[x-K]);
    // cout<<" : "<<f[x]<<' '<<calc(x)<<endl;
    res=(res+calc(x))%p;
    ucnt.push_back({f[x],cnt[f[x]]});
    cnt[f[x]]++;
}
void undor(){
    while(uf.size()){
        f[uf.back().first]=uf.back().second;
        uf.pop_back();
    }
    while(ucnt.size()){
        cnt[ucnt.back().first]=ucnt.back().second;
        ucnt.pop_back();
    }
}
void addl(int x,int &res){
    ucnt_.push_back({x,cnt[x]});
    ucnt_.push_back({x+K,cnt[x+K]});
    // cout<<x<<" "<<cnt[x]<<' '<<cnt[x+K]<<endl;
    res=(res+cnt[x+K])%p;
    cnt[x]+=cnt[x+K];
    cnt[x+K]=0;
}
void undol(){
    while(ucnt_.size()){
        cnt[ucnt_.back().first]=ucnt_.back().second;
        ucnt_.pop_back();
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
    for(int i=1;i<=m;i++) cin>>ql[i]>>qr[i];

    K=b[1]-a[1]+1;
    const int B=sqrt(n);
    for(int i=1;i<=n;i++){
        blk[i]=(i-1)/B+1;
        if(!L[blk[i]]) L[blk[i]]=i;
        R[blk[i]]=i;
    }
    for(int i=1;i<=m;i++) per[i]=i;
    sort(per+1,per+m+1,cmp);

    for(int i=0;i<=V/2;i++) f[i]=i+K,cnt[f[i]]++;
    for(int cur=1,i=1;cur<=blk[n];cur++){
        int res=0;
        // cout<<blk[ql[per[i]]]<<' '<<cur<<endl;
        for(int l=R[cur]+1,r=R[cur];blk[ql[per[i]]]==cur&&i<=m;i++){
            // cout<<per[i]<<' '<<ql[per[i]]<<'/'<<qr[per[i]]<<endl;
            if(blk[ql[per[i]]]==blk[qr[per[i]]]){
                for(int j=ql[per[i]];j<=qr[per[i]];j++) addr(a[j],ans[per[i]]);
                undor();
                continue ;
            }
            while(r<qr[per[i]]) addr(a[++r],res);
            ans[per[i]]=res;
            // cout<<r<<' '<<res<<endl;
            while(l>ql[per[i]]) addl(a[--l],ans[per[i]]);
            undol();
            l=R[cur]+1;
        }
        undor();
    }

    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
    
    return 0;
}