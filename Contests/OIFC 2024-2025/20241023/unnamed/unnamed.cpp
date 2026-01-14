#include<bits/stdc++.h>

using namespace std;

ifstream fin("unnamed.in");
ofstream fout("unnamed.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e3+9;
const int LIM=1e3;

long long f[N][N];

int main(){
    for(int i=1;i<=LIM;i++){
        for(int j=1;j<=LIM;j++){
            int tmp=i/__gcd(i,j)*j;
            vector<int> v;
            for(int k=2;k*k<=tmp;k++){
                if(tmp%k) continue ;
                v.push_back(0);
                while(tmp%k==0) tmp/=k,v.back()++;
            }
            if(tmp!=1) v.push_back(1);
            if(!v.size()){
                f[i][j]=1;
                continue ;
            }
            int t=v[0];
            for(int x:v) t=__gcd(t,x);
            if(t!=1) f[i][j]=1;
        }
    }
    for(int i=1;i<=LIM;i++){
        for(int j=1;j<=LIM;j++) f[i][j]+=f[i-1][j]+f[i][j-1]-f[i-1][j-1];
    }
    int T;
    cin>>T;
    while(T--){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        cout<<f[b][d]-f[a-1][d]-f[b][c-1]+f[a-1][c-1]<<endl;
    }

    return 0;
}