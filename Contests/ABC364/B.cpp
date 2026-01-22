#include<bits/stdc++.h>

using namespace std;

const int N=1e3+9;

char c[N][N];

int main(){
    int n,m,x,y;
    cin>>n>>m>>x>>y;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>c[i][j];

    string s;
    cin>>s;
    for(int i=0;i<s.size();i++){
        if(s[i]=='U'){
            if(x>1&&c[x-1][y]!='#') x--;
        }else if(s[i]=='D'){
            if(x<n&&c[x+1][y]!='#') x++; 
        }else if(s[i]=='L'){
            if(y>1&&c[x][y-1]!='#') y--; 
        }else if(s[i]=='R'){
            if(y<m&&c[x][y+1]!='#') y++; 
        }
    }

    cout<<x<<' '<<y<<endl;

    return 0;
}