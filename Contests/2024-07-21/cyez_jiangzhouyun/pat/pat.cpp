#include<bits/stdc++.h>

using namespace std;

ifstream fin("pat.in");
ofstream fout("pat.out");
#define cin fin
#define cout fout

#define int long long
const int p=998244353;

int n,m;
string a[10],b[10];
int arr[10][10],brr[10][10],foc[10][10],leq[10][10];
int dp[10][5050],upp[10];
int fac[10]={1,1,2,6,24,120,720,5040};

vector<int> mpi[5050];int cnt;
map<vector<int>,int> mpp;
void Init(){
    cnt=0;
    vector<int> tmp(m,0);
    for(int i=0;i<m;i++) tmp[i]=i+1;
    do{
        mpi[++cnt]=tmp;
        mpp[mpi[cnt]]=cnt;
    }while(next_permutation(tmp.begin(),tmp.end()));
}

int F(){
    memset(dp,0,sizeof dp);
    dp[0][1]=1;
    for(int i=1;i<=n;i++){
        for(int sta=0;sta<(1<<n);sta++){
            bool err=0;
            for(int j=1;j<=n;j++){
                int cur=sta>>j-1&1;
                if(~foc[j][i-1]){
                    if(cur!=foc[j][i-1]){
                        err=1;
                        break ;
                    }
                }
                if(~leq[j][i-1]){
                    if(cur>leq[j][i-1]){
                        err=1;
                        break ;
                    }
                }
            }
            if(err) continue ;
            for(int j=1;j<=m;j++){
                upp[j]=0;
                for(int k=0;k<n;k++){
                    if(brr[j][k]&&(sta>>k&1)) upp[j]^=1;
                }
            }
            for(int j=1;j<=fac[m];j++){
                vector<int> lst=mpi[j],cur;
                for(int x:lst) if(upp[x]) cur.push_back(x);
                for(int x:lst) if(!upp[x]) cur.push_back(x);
                int k=mpp[cur];
                dp[i][k]=(dp[i][k]+dp[i-1][j])%p;
            }
        }
    }
    return dp[n][1];
}
int c[10],r[10],res;
void G(int i){
    if(i>n){
        for(int i=1;i<m;i++){
            if(c[i]>c[i+1]) return ;
        }
        for(int i=1;i<=n;i++) cout<<r[i]<<' ';cout<<endl;
        res++;
        return ;
    }
    for(int sta=0;sta<(1<<n);sta++){
        bool err=0;
        for(int j=0,u=1;j<n;j++){
            int cur=sta>>j&1;
            if(~foc[i][j]){
                if(cur!=foc[i][j]){
                    err=1;
                    break ;
                }
            }
            if(~leq[i][j]&&u){
                if(cur>leq[i][j]){
                    err=1;
                    break ;
                }else if(cur<leq[i][j]){
                    u=0;
                }
            }
        }
        if(err) continue ;
        for(int j=1;j<=m;j++){
            if(brr[j][i-1]) c[j]^=sta;
        }
        r[i]=sta;
        G(i+1);
        for(int j=1;j<=m;j++){
            if(brr[j][i-1]) c[j]^=sta;
        }
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>b[i];

    for(int i=1;i<=n;i++) while(a[i].size()<n) a[i]="0"+a[i];
    for(int i=1;i<=n;i++){
        for(int j=0;j<n;j++) arr[i][j]=a[i][n-j-1]-'0';
        for(int j=0;j<n;j++) foc[i][j]=-1;
    }
    for(int i=1;i<=m;i++){
        for(int j=0;j<n;j++) brr[i][j]=b[i][j]-'0';
    }

    Init();
    int ans=F();
    res=0;G(1);
    cout<<res<<endl;
    for(int i=1;i<=n;i++){
        for(int j=n-1;~j;j--){
            if(!foc[i][j]){
                foc[i][j]=1;
                ans-=F();
                cout<<i<<' '<<j<<' '<<F()<<endl;
                res=0;G(1);
                cout<<res<<endl;
                foc[i][j]=-1;
            }
            leq[i][j]=arr[i][j];
        }
    }

    cout<<ans<<endl;

    return 0;
}