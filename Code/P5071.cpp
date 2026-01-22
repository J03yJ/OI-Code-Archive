#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

const int N=1e5+9;
const int mod=19260817;

int pri[N],ntp[N],cnt;
void InitP(int n){
    for(int i=2;i<=n;i++){
        if(!ntp[i]) pri[++cnt]=i;
        for(int j=1;j<=cnt&&pri[j]*i<=n;j++){
            ntp[pri[j]*i]=1;
            if(i%pri[j]==0) break ;
        }
    }
}

int test[7]={2,325,9375,28178,450775,9780504,1795265022};
int QPow(int x,int y,int p){
    x%=p;
    int res=1;
    while(y){
        if(y&1) res=__int128(1)*res*x%p;
        x=__int128(1)*x*x%p;
        y>>=1;
    }
    return res;
}
bool MR(int x,int y){
    int cnt=0,lim=y-1;
    while(!(lim&1)) lim>>=1,cnt++;
    int val=QPow(x,lim,y);
    if(val==1) return 1;
    for(int i=1;i<=cnt;i++){
        if(val==y-1) return 1;
        val=__int128(1)*val*val%y;
    }
    return 0;
}
int IsP(int x){
    if(x<2) return 0;
	if(x==2||x==3||x==7||x==61||x==24251) return 1;
    return MR(2,x)&&MR(61,x);
}
mt19937 myrand(4649);
int GCD(int x,int y){
    if(!y) return x;
    else return GCD(y,x%y);
}
int F(int seed,int c,int mod){
    return (__int128(1)*seed*seed+c)%mod;
}
/*
int PR(int x){
    if(x%2==0) return 2;
    int c=myrand()%(x-1)+1;
    int l=F(0,c,x),r=F(l,c,x);
    while(l!=r){
        int k=GCD(x,abs(r-l));
        if(k>1) return k;
        l=F(l,c,x);
        r=F(F(r,c,x),c,x);
    }
    return x;
}
*/
int PR(int x){
    int s=0,t=0,c=myrand()%(x-1)+1;
    int val=1;
    for(int i=1;;i<<=1,s=t,val=1){
        for(int j=1;j<=i;j++){
            t=F(t,c,x);
            val=__int128(1)*val*abs(t-s)%x;
            if(!val) return x;
            if(j%127==0){
                int d=GCD(val,x);
                if(d>1) return d;
            }
        }
        int d=GCD(val,x);
        if(d>1) return d;
    }
    return x;
}

int inv[N<<1];
void InitInv(int n){
    inv[0]=1;
    for(int i=1;i<=n;i++) inv[i]=QPow(i,mod-2,mod);
}

int a[N],blk[N],pre[N],buc[N],n,tot;
int ql[N],qr[N],ans[N],p[N],m;
bool Cmp(int x,int y){
    if(blk[ql[x]]!=blk[ql[y]]) return blk[ql[x]]<blk[ql[y]];
    else return blk[ql[x]]%2?qr[x]>qr[y]:qr[x]<qr[y];
}
void Add(int x,int &res){
    if(!x) return ;
    res=1ll*res*inv[buc[x]+1]%mod;
    buc[x]++;
    res=1ll*res*(buc[x]+1)%mod;
}
void Del(int x,int &res){
    if(!x) return ;
    res=1ll*res*inv[buc[x]+1]%mod;
    buc[x]--;
    res=1ll*res*(buc[x]+1)%mod;
}

gp_hash_table<int,int> mp;
pair<int,int> c[N];
inline int Ins(int k){
    if(!mp[k]) mp[k]=++tot;
    return mp[k];
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>ql[i]>>qr[i],ans[i]=1,p[i]=i;

    InitP(1e3);
    for(int i=1;i<=cnt;i++){
        for(int j=1;j<=n;j++){
            pre[j]=pre[j-1];
            while(a[j]%pri[i]==0) pre[j]++,a[j]/=pri[i];
        }
        for(int j=1;j<=m;j++) ans[j]=1ll*ans[j]*(pre[qr[j]]-pre[ql[j]-1]+1)%mod;
    }
    for(int i=1;i<=n;i++){
        if(a[i]==1) continue ;
        if(IsP(a[i])) c[i].first=Ins(a[i]);
        else{
            int k=a[i];
            while(k>=a[i]){
                k=PR(k);
            }
            c[i]={Ins(k),Ins(a[i]/k)};
        }
    }

    int B=sqrt(n);
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    sort(p+1,p+m+1,Cmp);

    InitInv(n<<1);
    for(int i=1,l=1,r=0,res=1;i<=m;i++){
        while(r<qr[p[i]]) r++,Add(c[r].first,res),Add(c[r].second,res);
        while(l>ql[p[i]]) l--,Add(c[l].first,res),Add(c[l].second,res);
        while(r>qr[p[i]]) Del(c[r].first,res),Del(c[r].second,res),r--;
        while(l<ql[p[i]]) Del(c[l].first,res),Del(c[l].second,res),l++;
        ans[p[i]]=1ll*ans[p[i]]*res%mod;
    }

    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}