#include<bits/stdc++.h>

using namespace std;

const int N=3e5+9;
const int K=1e2+9;

int fi[N],ne[N<<1],to[N<<1],adj=1;
long long w[N<<1];
void adeg(int x,int y,long long z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

bool vis[N];
int dp[N][K];

int main(){
    int n;
    cin>>n;
    for(int i=1;i<n;i++){
        int x,y;long long z;
        cin>>x>>y>>z;
        adeg(x,y,z);
        adeg(y,x,z);
    }
}