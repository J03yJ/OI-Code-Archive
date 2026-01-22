#include<bits/stdc++.h>

using namespace std;

const int N=2e6+9;

int a[N],blk[N],n,m,k;
int ql[N],qr[N],p[N],cnt[N];
long long ans[N];
bool cmp(int x,int y){
    if(blk[ql[x]]!=blk[ql[y]]) return blk[ql[x]]<blk[ql[y]];
    else return qr[x]<qr[y];
}

int main(){
    int n,m,k;
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++) cin>>a[i],a[i]^=a[i-1];
    for(int i=1;i<=m;i++) cin>>ql[i]>>qr[i],ql[i]--,p[i]=i;

    int B=sqrt(n);
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    sort(p+1,p+m+1,cmp);

    long long res=0;
    // cnt[0]++;
    for(int l=1,r=0,i=1;i<=m;i++){
        while(r<qr[p[i]]){
            res+=cnt[a[++r]^k];
            cnt[a[r]]++;
        }
        while(l>ql[p[i]]){
            res+=cnt[a[--l]^k];
            cnt[a[l]]++;
        }
        while(r>qr[p[i]]){
            cnt[a[r]]--;
            res-=cnt[a[r--]^k];
        }
        while(l<ql[p[i]]){
            cnt[a[l]]--;
            res-=cnt[a[l++]^k];
        }
        ans[p[i]]=res;
    }

    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}