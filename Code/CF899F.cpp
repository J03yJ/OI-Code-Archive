#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
const int K=6e2+9;

char a[N];
int blk[N],ban[N],L[N],R[N],n,m,B;
int cnt[K][128],tag[K][128],sum[K];

void Push(int x,char c){
    sum[x]-=cnt[x][c];
    cnt[x][c]=0;
    tag[x][c]=1;
}
void PushDown(int x){
    for(int i=L[x];i<=R[x];i++) if(tag[x][a[i]]) ban[i]=1;
    for(int i=0;i<128;i++) tag[x][i]=0;
}
void Build(int x){
    sum[x]=0;
    PushDown(x);
    for(int i=0;i<128;i++) cnt[x][i]=0;
    for(int i=L[x];i<=R[x];i++){
        if(ban[i]) continue ;
        cnt[x][a[i]]++;
        sum[x]++;
    }
}
void EraseBrute(int l,int r,char c){
    for(int i=l;i<=r;i++) if(a[i]==c) ban[i]=1;
    Build(blk[l]);
}
void Erase(int l,int r,char c){
    if(blk[l]==blk[r]) return EraseBrute(l,r,c);
    EraseBrute(l,R[blk[l]],c);
    EraseBrute(L[blk[r]],r,c);
    for(int i=blk[l]+1;i<blk[r];i++) Push(i,c);
}
int Find(int pos){
    for(int i=1;i<=blk[n];i++){
        if(pos<=sum[i]){
            PushDown(i);
            for(int j=L[i];j<=R[i];j++){
                if(ban[j]) continue ;
                if(!(--pos)) return j;
            }
        }else pos-=sum[i];
    }
    assert(0);
    return -1;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];

    B=sqrt(n);
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    for(int i=1;i<=n;i++) R[blk[i]]=i;
    for(int i=n;i>=1;i--) L[blk[i]]=i;
    for(int i=1;i<=blk[n];i++) Build(i);

    for(int i=1,l,r;i<=m;i++){
        char c;
        cin>>l>>r>>c;
        // for(int i=1;i<=blk[n];i++) PushDown(i);
        // for(int i=1;i<=n;i++) if(!ban[i]) cout<<a[i];cout<<endl;
        l=Find(l),r=Find(r);
        Erase(l,r,c);
    }
    for(int i=1;i<=blk[n];i++) PushDown(i);
    for(int i=1;i<=n;i++) if(!ban[i]) cout<<a[i];cout<<endl;

    return 0;
}