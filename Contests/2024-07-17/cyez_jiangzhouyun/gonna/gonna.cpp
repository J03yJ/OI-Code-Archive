#include<bits/stdc++.h>
  
using namespace std;
  
ifstream fin("gonna.in");
ofstream fout("gonna.out");
#define cin fin
#define cout fout
  
const int N=2e4+9;
const int P=2.5e3+9;
  
int b[N],pri[P],cnt;
int fac[N][P],pre[N][P];
void init(int n){
    for(int i=2;i<=n;i++){
        if(!b[i]) pri[++cnt]=i;
        for(int j=1;j<=cnt&&pri[j]*i<=n;j++){
            b[pri[j]*i]=1;
            if(i%pri[j]==0) break ;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1,k=i;j<=cnt;j++){
            fac[i][j]=fac[i-1][j];
            while(k%pri[j]==0) k/=pri[j],fac[i][j]++;
            pre[i][j]=pre[i-1][j]+fac[i][j];
        }
    }
}
  
#define int long long
  
const int L=2e3;
int buc[P];
int sum[P][P],pwr[P][P];
void Init(int p){
    for(int i=1;i<=cnt;i++){
        sum[i][0]=pwr[i][0]=1;
        for(int j=1;j<=L;j++) sum[i][j]=(sum[i][j-1]*pri[i]%p+1)%p;
        for(int j=1;j<=L;j++) pwr[i][j]=pwr[i][j-1]*pri[i]%p;
    }
}
inline pair<int,int> calc(int &x,int y,int &p){
    if(y<=L) return {sum[x][y-1],pwr[x][y]};
    pair<int,int> res=calc(x,y>>1,p);
    int ans=res.first*(res.second+1)%p;
    if(y&1) ans=(ans*pri[x]+1)%p;
    int pw=res.second*res.second%p;
    if(y&1) pw=pw*pri[x]%p;
    return {ans,pw};
}
  
signed main(){
    int n,p;
    cin>>n>>p;
      
    init(n);
    Init(p);
    int ans=0;
    for(int i=1;i<=n;i++){
        int mul=1;
        for(int j=1;j<=cnt;j++) buc[j]=0;
        for(int j=1;j<=cnt;j++) buc[j]+=fac[i][j]*(i+1);
        for(int j=1;j<=cnt;j++) buc[j]-=pre[i][j]<<1;
        for(int j=1;j<=cnt;j++){
            mul=mul*calc(j,buc[j]+1,p).first%p;
        }
        ans=(ans+mul)%p;
    }
    cout<<ans<<endl;
      
    return 0;
}