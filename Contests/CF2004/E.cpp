#include<bits/stdc++.h>

using namespace std;

const int V=1e2+9;

int f[V][V][V];

int main(){
    int n;
    cin>>n;
    f[0][0][0]=0;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            for(int k=0;k<=n;k++){
                for(int d=1;d<=i;d++){
                    if(__gcd(i,d)!=1) continue ;
                    if(!f[i-d][j][k]) f[i][j][k]=1;
                }
                for(int d=1;d<=j;d++){
                    if(__gcd(j,d)!=1) continue ;
                    if(!f[i][j-d][k]) f[i][j][k]=1;
                }
                for(int d=1;d<=k;d++){
                    if(__gcd(k,d)!=1) continue ;
                    if(!f[i][j][k-d]) f[i][j][k]=1;
                }
                cout<<f[i][j][k]<<' ';
            }
            cout<<endl;
        }
        cout<<endl;
    }

    return 0;
}