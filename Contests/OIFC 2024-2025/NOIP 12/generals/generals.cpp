#include<bits/stdc++.h>

using namespace std;

ifstream fin("generals.in");
ofstream fout("generals.out");
#define cin fin
#define cout fout

#define int long long
const int N=1<<10;
const int mod=1e9+7;

int F(int x,int y){
    for(int z=1;;z++) if((x^(x+z))==(y^(y+z))) return z;
}
int a[N+9][N+9],mask[20],n;

signed main(){
    for(int i=0;i<=N;i++){
        for(int j=0;j<=N;j++){
            a[i][j]=F(i,j);
        }
    }
    for(int i=0;i<=N;i++){
        for(int j=0;j<=N;j++){
            if(i) a[i][j]+=a[i-1][j];
            if(j) a[i][j]+=a[i][j-1];
            if(i&&j) a[i][j]-=a[i-1][j-1];
        }
    }
    for(int i=0;i<=N;i++){
        for(int j=0;j<=N;j++){
            a[i][j]%=mod;
        }
    }
    for(int i=0;i<20;i++) mask[i]=(1<<i)-1;

    int o,m;
    cin>>o>>m;
    string s;
    cin>>s;

    int n=0;
    reverse(s.begin(),s.end());
    for(char c:s) n<<=1,n|=c&1;

    int T;
    cin>>T;
    while(T--){
        int op,l,r;
        cin>>op>>l>>r;
        if(op==1){
            n^=mask[r]^mask[l-1];
        }else{
            int x=(n>>(l-1))&mask[r-l+1];
            cout<<a[x][x]<<endl;
        }
    }

    return 0;
}