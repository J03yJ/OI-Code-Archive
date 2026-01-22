#include<bits/stdc++.h>

using namespace std;

const int N=1e3+9;
const int mod=998244353;

struct Mint{
    int x;
    Mint(){}
    Mint(int a){x=a;}
    Mint operator +(Mint a){return (x+a.x)>mod?x+a.x-mod:x+a.x;}
    Mint operator -(Mint a){return (x-a.x)<0?x-a.x+mod:x-a.x;}
    Mint operator *(Mint a){return 1ll*x*a.x%mod;}
    Mint QPow(int y){
        Mint res=1,x=*this;
        while(y){
            if(y&1) res=res*x;
            x=x*x;
            y>>=1;
        }
        return res;
    }
    Mint Inv(){return this->QPow(mod-2);}
    Mint operator /(Mint a){return *this*a.Inv();}
    Mint operator -(){return mod-x;}
};
#define double Mint

int pre[N][N],suf[N][N],n,m;
string s[N];
double pw[N],a[N][N];
int Hash(string s){
    int res=0;
    for(auto c:s){
        res=res*3%mod;
        res=(res+(c=='1'))%mod;
    }
    return res;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>s[i],s[i]=" "+s[i];
    
    pw[0]=1;for(int i=1;i<=m;i++) pw[i]=pw[i-1]/2;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) pre[i][j]=Hash(s[i].substr(1,j));
        for(int j=m;j>=1;j--) suf[i][j]=Hash(s[i].substr(m-j+1,j));
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=m;k++) if(pre[i][k]==suf[j][k]) a[i][j]=a[i][j]+pw[m-k];
        }
        a[i][n+1]=-pw[m];
    }
    for(int i=1;i<=n;i++) a[n+1][i]=1;a[n+1][n+2]=1;

    for(int i=1;i<=n+1;i++){
        int pos=i;
        for(int j=i+1;j<=n+1;j++) if(a[pos][i].x<a[j][i].x) pos=j;
        swap(a[i],a[pos]);
        for(int j=i+1;j<=n+2;j++) a[i][j]=a[i][j]/a[i][i];
        a[i][i]=1;
        for(int j=1;j<=n+1;j++){
            if(i==j) continue ;
            for(int k=i+1;k<=n+2;k++) a[j][k]=a[j][k]-a[j][i]*a[i][k];
            a[j][i]=0;
        }
    }

    cout<<a[1][n+2].x<<endl;

    return 0;
}