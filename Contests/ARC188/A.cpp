#include<bits/stdc++.h>

using namespace std;

#define int long long

const int N=59;
const int mod=998244353;

int f[N][N][N][N][4],n,t;
char s[N];
void Add(int &x,int y){
    x+=y;
    if(x>mod) x-=mod;
}

signed main(){
    cin>>n>>t;
    for(int i=0;i<n;i++) cin>>s[i];
    
    f[0][0][0][0][0]=1;
    for(int i=0;i<n;i++){
        // int sum=0;
        for(int a=0;a<=i;a++){
            for(int b=0;a+b<=i;b++){
                for(int c=0;a+b+c<=i;c++){
                    if(s[i]=='A'||s[i]=='?'){
                        Add(f[i+1][a][b][c][3],f[i][a][b][c][0]);
                        Add(f[i+1][a][b][c+1][2],f[i][a][b][c][1]);
                        Add(f[i+1][a][b+1][c][1],f[i][a][b][c][2]);
                        Add(f[i+1][a+1][b][c][0],f[i][a][b][c][3]);
                    }
                    if(s[i]=='B'||s[i]=='?'){
                        Add(f[i+1][a][b+1][c][1],f[i][a][b][c][0]);
                        Add(f[i+1][a+1][b][c][0],f[i][a][b][c][1]);
                        Add(f[i+1][a][b][c][3],f[i][a][b][c][2]);
                        Add(f[i+1][a][b][c+1][2],f[i][a][b][c][3]);
                    }
                    if(s[i]=='C'||s[i]=='?'){
                        Add(f[i+1][a][b][c+1][2],f[i][a][b][c][0]);
                        Add(f[i+1][a][b][c][3],f[i][a][b][c][1]);
                        Add(f[i+1][a+1][b][c][0],f[i][a][b][c][2]);
                        Add(f[i+1][a][b+1][c][1],f[i][a][b][c][3]);
                    }
                    // for(int k:{0,1,2,3}){
                    //     // cout<<i<<' '<<a<<' '<<b<<' '<<c<<' '<<i-a-b-c<<' '<<k<<" : "<<f[i][a][b][c][k]<<endl;
                    //     sum+=f[i][a][b][c][k];
                    // }
                }
            }
        }
        // cout<<sum<<endl;
    }

    int ans=0;
    for(int a=0;a<=n;a++){
        for(int b=0;b<=n;b++){
            for(int c=0;c<=n;c++){
                for(int k:{0,1,2,3}){
                    int d=n-a-b-c;
                    int tmp=a*(a+1)/2;
                    tmp+=b*(b-1)/2;
                    tmp+=c*(c-1)/2;
                    tmp+=d*(d-1)/2;
                    if(tmp<t) continue ;
                    Add(ans,f[n][a][b][c][k]);
                }
            }
        }
    }
    cout<<ans<<endl;

    return 0;
}