#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const int S=666;

int a[N],c[N],n,m;
pair<int,int> b[N];
int blk[N],L[S],R[S];
long long pre[N],suf[N],F[S][S];
int cnt[S][N];

int tr[N];
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

int A1[N],A2[N];
inline int Merge(int *a,int *b,int n,int m){
    int i=1,j=1,ans=0;
    while(i<=n&&j<=m){
        if(a[i]<b[j]) i++;
        else ans+=n-i+1,j++;
    }
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    #define endl '\n'
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],b[i]={a[i],i};

    int B=160;
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    for(int i=1;i<=blk[n];i++) L[i]=B*(i-1)+1,R[i]=B*i;R[blk[n]]=n;

    for(int i=1;i<=blk[n];i++){
        int lst=0;
        for(int j=L[i];j<=R[i];j++){
            Add(a[j],1);
            pre[j]=lst+=Ask(a[j]+1,n);
        }
        for(int j=L[i];j<=R[i];j++) Add(a[j],-1);
        F[i][i]=lst;
        lst=0;
        for(int j=R[i];j>=L[i];j--){
            Add(a[j],1);
            suf[j]=lst+=Ask(a[j]-1);
        }
        for(int j=R[i];j>=L[i];j--) Add(a[j],-1);
        for(int j=L[i];j<=R[i];j++) cnt[i][a[j]]++;
        for(int j=1;j<=n;j++) cnt[i][j]+=cnt[i-1][j];
        sort(b+L[i],b+R[i]+1);
        for(int j=L[i];j<=R[i];j++) c[j]=b[j].first;
    }
    for(int i=1;i<=blk[n];i++){
        for(int j=1;j<=n;j++) cnt[i][j]+=cnt[i][j-1];
    }
    for(int len=2;len<=blk[n];len++){
        for(int i=1;i<=blk[n]-len+1;i++){
            int j=i+len-1;
            F[i][j]=F[i+1][j]+F[i][j-1]-F[i+1][j-1]+Merge(c+L[i]-1,c+L[j]-1,R[i]-L[i]+1,R[j]-L[j]+1);
        }
    }

    long long lst=0;
    while(m--){
        long long l,r;
        cin>>l>>r;
        l^=lst;r^=lst;
        if(l>r) swap(l,r);
        long long ans=0,cnt1=0,cnt2=0;
        if(blk[l]==blk[r]){
            for(int i=L[blk[l]];i<=R[blk[l]];i++){
                if(l<=b[i].second&&b[i].second<=r) A2[++cnt2]=c[i];
                else if(b[i].second<l) A1[++cnt1]=c[i];
            }
            if(l!=L[blk[l]]) ans=pre[r]-pre[l-1]-Merge(A1,A2,cnt1,cnt2);
            else ans=pre[r]-Merge(A1,A2,cnt1,cnt2);
        }else{
            ans=F[blk[l]+1][blk[r]-1]+suf[l]+pre[r];
            for(int i=L[blk[l]];i<=R[blk[l]];i++){
                if(b[i].second>=l){
                    A1[++cnt1]=c[i];
                    ans+=cnt[blk[r]-1][c[i]-1]-cnt[blk[l]][c[i]-1];
                }
            }
            for(int i=L[blk[r]];i<=R[blk[r]];i++){
                if(b[i].second<=r){
                    A2[++cnt2]=c[i];
                    ans+=(cnt[blk[r]-1][n]-cnt[blk[r]-1][c[i]])-(cnt[blk[l]][n]-cnt[blk[l]][c[i]]);
                }
            }
            ans+=Merge(A1,A2,cnt1,cnt2);
        }
        cout<<ans<<endl;
        lst=ans;
    }
}