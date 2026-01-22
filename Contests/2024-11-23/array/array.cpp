#include<bits/stdc++.h>

using namespace std;

ifstream fin("array.in");
ofstream fout("array.out");
#define cin fin
#define cout fout

#define int long long
#define ssiz(x) (signed)(x).size()
const int N=1e6+9;
const int lgN=63;
const int mod=1e9+7;
using Matrix=vector<vector<int>>;

Matrix Mul(Matrix a,Matrix b){
    assert(ssiz(*a.begin())==ssiz(b));
    Matrix c(ssiz(a),vector<int>(ssiz(*b.begin()),0));
    for(int i=0;i<ssiz(a);i++){
        for(int j=0;j<ssiz(*b.begin());j++){
            for(int k=0;k<ssiz(b);k++) c[i][j]=(c[i][j]+a[i][k]*b[k][j]%mod)%mod;
        }
    }
    return c;
}

Matrix f[lgN],g[lgN],e[lgN];
Matrix Carry(int k){
    Matrix f(lgN,vector<int>(lgN,0));
    for(int i=0;i<=k;i++) f[i][i]=2,f[i][i+1]=mod-1;
    for(int i=k+1;i<lgN;i++) f[i][i]=1;
    return f;
}
Matrix E(){
    Matrix f(lgN,vector<int>(lgN,0));
    for(int i=0;i<lgN;i++) f[i][i]=1;
    return f;
}
void Print(Matrix x){
    for(auto &c:x){
        for(int a:c) cout<<a<<' ';cout<<endl;
    }
    cout<<endl;
}
int F(int n){
    if(!n) return 0;
    Matrix x;
    for(int k=lgN-1;~k;k--){
        if(n>>k&1){
            if(!ssiz(x)) x=e[k];
            else x=Mul(f[k],x);
        }
    }
    return x[0][0];
}

signed main(){
    int T,c;
    cin>>c>>T;
    
    f[0]=Carry(0),g[0]=E();
    for(int i=1;i<lgN-1;i++){
        g[i]=Mul(g[i-1],f[i-1]);
        f[i]=Mul(Carry(i),g[i]);
    }

    e[0]=Matrix(lgN,{0}),e[0][0][0]=1;
    for(int i=1;i<lgN-1;i++){
        e[i]=e[i-1];
        e[i]=Mul(g[i-1],e[i]);
        e[i]=Mul(Carry(i),e[i]);
        e[i][i][0]=1;
    }

    while(T--){
        int n;
        cin>>n;
        cout<<(F(n)-F(n-1)+mod)%mod<<endl;
    }

    return 0;
}