#include<bits/stdc++.h>

using namespace std;

// #define int long long
const int N=1e5+9;

int a[N],b[N],aq[N],bq[N],p[N],n,q;
int blk[N],L[N],R[N],aval[N],bval[N];
long long apre[N],bpre[N],asuf[N],bsuf[N];
void Init(int x,int *a,long long *pre,long long *suf,int *val){
    for(int i=L[x];i<=R[x];i++) val[i]=a[i];
    sort(val+L[x],val+R[x]+1);
    pre[L[x]]=val[L[x]];for(int i=L[x]+1;i<=R[x];i++) pre[i]=pre[i-1]+val[i];
    suf[R[x]]=val[R[x]];for(int i=R[x]-1;i>=L[x];i--) suf[i]=suf[i+1]+val[i];
}

long long Brute(int l,int r,int *a,long long *pre,long long *suf,int *val,int k){
    long long sum=0;
    for(int i=l;i<=r;i++) sum+=abs(a[i]-k);
    return sum;
}
long long Query(int l,int r,int *a,long long *pre,long long *suf,int *val,int k){
    if(blk[l]==blk[r]) return Brute(l,r,a,pre,suf,val,k);
    long long sum=0;
    // sum+=Brute(l,R[blk[l]],a,pre,suf,val,k);
    sum+=Brute(L[blk[r]],r,a,pre,suf,val,k);
    for(int i=blk[l];i<=blk[r]-1;i++){
        int pl=upper_bound(val+L[i],val+R[i]+1,k)-val-1,pr=pl+1;
        if(pl>=L[i]) sum+=1ll*(pl-L[i]+1)*k-pre[pl];
        if(pr<=R[i]) sum+=suf[pr]-1ll*(R[i]-pr+1)*k;
    }
    return sum;
}

long long ans[N];
long long QA(int x,int i){return i?Query(1,i,a,apre,asuf,aval,b[x]):0;}
long long QB(int x,int i){return i?Query(1,i,b,bpre,bsuf,bval,a[x]):0;}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    cin>>q;
    for(int i=1;i<=q;i++) cin>>aq[i]>>bq[i];

    int sq=sqrt(n);
    for(int i=1;i<=n;i++) blk[i]=(i-1)/sq+1;
    for(int i=1;i<=n;i++) R[blk[i]]=i;
    for(int i=n;i>=1;i--) L[blk[i]]=i;

    iota(p+1,p+q+1,1);
    sort(p+1,p+q+1,[](int x,int y){
        if(blk[aq[x]]!=blk[aq[y]]) return blk[aq[x]]<blk[aq[y]];
        else return bq[x]<bq[y];
    });
    for(int i=1;i<=blk[n];i++){
        Init(i,a,apre,asuf,aval);
        Init(i,b,bpre,bsuf,bval);
    }

    long long res=0;
    for(int i=0,j=0,k=1;k<=q;k++){
        while(i<aq[p[k]]) res+=QB(++i,j);
        while(j<bq[p[k]]) res+=QA(++j,i);
        while(i>aq[p[k]]) res-=QB(i--,j);
        while(j>bq[p[k]]) res-=QA(j--,i);
        ans[p[k]]=res;
    }
    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

    return 0;
}