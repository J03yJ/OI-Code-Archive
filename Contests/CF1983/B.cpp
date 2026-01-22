#include<bits/stdc++.h>

using namespace std;

const int N=5e2+9;

int a[N][N],b[N][N];

int main(){
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                char c;
                cin>>c;
                a[i][j]=c-'0';
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                char c;
                cin>>c;
                b[i][j]=c-'0';
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++) b[i][j]=(b[i][j]-a[i][j]+3)%3;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++) cout<<b[i][j]<<' ';
            cout<<endl;
        }
        cout<<endl;
    }
}