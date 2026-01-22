#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const int V=1e5+2;

int a[N],n,m;
int val[N];map<int,int> mp;

int tr[N];
long long wl[N],wr[N];
inline void Add(int x,int k){
    while(x<=n){
        tr[x]+=k;
        x+=x&-x;
    }
}
inline int Ask(int x){
    int sum=0;
    while(x){
        sum+=tr[x];
        x&=x-1;
    }
    return sum;
}
inline int Ask(int l,int r){
    if(l>r) return 0;
    return Ask(r)-Ask(l-1);
}

int ql[N],qr[N],p[N],qB;
long long ans[N];
bool cmp(int x,int y){
    if((ql[x]-1)/qB!=(ql[y]-1)/qB) return (ql[x]-1)/qB<(ql[y]-1)/qB;
    else{
        if((ql[x]-1)/qB%2) return qr[x]>qr[y];
        else return qr[x]<qr[y];
    }
}
vector<tuple<int,int,int,int>> lq[N],rq[N];

int blk[N],L[N],R[N],pre[N],bpre[N],B;
void init(){
    for(int i=1;i<=V;i++) blk[i]=(i-1)/B+1,pre[i]=0;
    for(int i=1;i<=blk[V];i++) L[i]=R[i-1]+1,R[i]=R[i-1]+B,bpre[i]=0;R[blk[V]]=V;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],val[i]=a[i];
    sort(val+1,val+n+1);
    int cnt=unique(val+1,val+n+1)-val-1;
    for(int i=1;i<=cnt;i++) mp[val[i]]=i;
    for(int i=1;i<=n;i++) a[i]=mp[a[i]];
    
    
    for(int i=1;i<=n;i++){
        wl[i]=wl[i-1]+Ask(a[i]+1,n);
        Add(a[i],1);
    }
    memset(tr,0,sizeof(tr));
    for(int i=n;i;i--){
        wr[i]=wr[i+1]+Ask(a[i]-1);
        Add(a[i],1);
    }

    qB=sqrt(m);
    for(int i=1;i<=m;i++) cin>>ql[i]>>qr[i],p[i]=i;
    sort(p+1,p+m+1,cmp);
    ql[0]=1;
    for(int i=1;i<=m;i++){
        ans[p[i]]=wl[qr[p[i]]]-wl[qr[p[i-1]]]+wr[ql[p[i]]]-wr[ql[p[i-1]]];
        if(qr[p[i]]>qr[p[i-1]]) rq[ql[p[i-1]]-1].push_back(make_tuple(qr[p[i-1]]+1,qr[p[i]],i,-1));
        else if(qr[p[i]]<qr[p[i-1]]) rq[ql[p[i-1]]-1].push_back(make_tuple(qr[p[i]]+1,qr[p[i-1]],i,1));
        if(ql[p[i]]<ql[p[i-1]]) lq[qr[p[i]]+1].push_back(make_tuple(ql[p[i]],ql[p[i-1]]-1,i,-1));
        else if(ql[p[i]]>ql[p[i-1]]) lq[qr[p[i]]+1].push_back(make_tuple(ql[p[i-1]],ql[p[i]]-1,i,1));
    }

    B=sqrt(V);
    init();
    for(int i=1;i<=n;i++){
        for(int j=1;j<blk[a[i]];j++) bpre[j]++;
        for(int j=L[blk[a[i]]];j<=a[i];j++) pre[j]++;
        for(tuple<int,int,int,int> t:rq[i]){
            long long res=0;
            for(int j=get<0>(t);j<=get<1>(t);j++) res+=bpre[blk[a[j]+1]]+pre[a[j]+1];
            ans[p[get<2>(t)]]+=res*get<3>(t);
        }
    }
    memset(pre,0,sizeof(pre));
    memset(bpre,0,sizeof(bpre));
    for(int i=n;i>=1;i--){
        for(int j=blk[a[i]]+1;j<=blk[V];j++) bpre[j]++;
        for(int j=a[i];j<=R[blk[a[i]]];j++) pre[j]++;
        for(tuple<int,int,int,int> t:lq[i]){
            long long res=0;
            for(int j=get<0>(t);j<=get<1>(t);j++) res+=bpre[blk[a[j]-1]]+pre[a[j]-1];
            ans[p[get<2>(t)]]+=res*get<3>(t);
        }
    }
    
    for(int i=1;i<=m;i++) ans[p[i]]+=ans[p[i-1]];
    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}