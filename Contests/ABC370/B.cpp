#include<bits/stdc++.h>

using namespace std;

const int N=2e3+9;

int a[N][N];

int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++) cin>>a[i][j];
    }
    #define Opt(x,y) (x>y?a[x][y]:a[y][x])
    int x=1;
    for(int i=1;i<=n;i++) x=Opt(x,i);
    cout<<x<<endl;
}