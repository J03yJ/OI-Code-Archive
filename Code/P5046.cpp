#include<bits/stdc++.h>

using namespace std;

<<<<<<< HEAD
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
=======
const int N=8e1+9;
const int W=13;
const int M=5e3+9;
const int mod=998244353;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline void SubAs(int &x,int y){x-=y;if(x<0) x+=mod;}
inline int Add(int x,int y){AddAs(x,y);return x;}
inline int Sub(int x,int y){SubAs(x,y);return x;}
inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

string opt;
void FWT(int *a,int lim){
    for(int k=0;(1<<k)<lim;k++){
        for(int i=0;i<lim;i++){
            if(i>>k&1) continue ;
            if(opt[k]=='&') AddAs(a[i],a[i+(1<<k)]);
            else if(opt[k]=='|') AddAs(a[i+(1<<k)],a[i]);
            else{
                int x=a[i],y=a[i+(1<<k)];
                a[i]=Add(x,y),a[i+(1<<k)]=Sub(x,y);
            }
        }
    }
}
const int inv2=mod+1>>1;
void IFWT(int *a,int lim){
    for(int k=0;(1<<k)<lim;k++){
        for(int i=0;i<lim;i++){
            if(i>>k&1) continue ;
                if(opt[k]=='&') SubAs(a[i],a[i+(1<<k)]);
            else if(opt[k]=='|') SubAs(a[i+(1<<k)],a[i]);
            else{
                int x=a[i],y=a[i+(1<<k)];
                a[i]=1ll*Add(x,y)*inv2,a[i+(1<<k)]=1ll*Sub(x,y)*inv2;
            }
        }
    }
}

int a[N][N][1<<W],r[N][N],cnt[1<<W],n,m,w;
int Det(int a[N][N],int n){
    int res=1;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            if(a[j][i]){
                swap(a[i],a[j]);
                if(j!=i) res=mod-res;
                break ;
            }
        }
        if(!a[i][i]) return 0;
        for(int j=i+1;j<=n;j++){
            int t=1ll*Inv(a[i][i])*a[j][i]%mod;
            for(int k=i;k<=n;k++) SubAs(a[j][k],1ll*a[i][k]*t%mod);
        }
    }
    for(int i=1;i<=n;i++) res=1ll*res*a[i][i]%mod;
    return res;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'
    
    cin>>n>>m>>opt;
    for(int i=1,u,v,x;i<=m;i++){
        cin>>u>>v>>x;
        AddAs(a[u][u][x],1);
        AddAs(a[v][v][x],1);
        SubAs(a[u][v][x],1);
        SubAs(a[v][u][x],1);
    }
    w=opt.size();

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) FWT(a[i][j],1<<w);
    }
    for(int x=0;x<(1<<w);x++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++) r[i][j]=a[i][j][x];
        }
        cnt[x]=Det(r,n-1);
    }

    IFWT(cnt,1<<w);
    for(int i=(1<<w)-1;~i;i--){
        if(cnt[i]){
            cout<<i<<endl;
            return 0;
        }
    }
    cout<<-1<<endl;

    return 0;
>>>>>>> d8147174aa15e80698100c4d67760eaf3e5689db
}