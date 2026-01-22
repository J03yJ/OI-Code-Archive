#include<bits/stdc++.h>

using namespace std;

ifstream fin("make.in");
ofstream fout("memory.in");
#define cin fin
#define cout fout
#define endl '\n'

int main(){
    int v;
    cin>>v;
    mt19937 rand(time(0));
    int n=rand()%v+1,m=rand()%v+1;
    cout<<m<<endl;
    for(int i=1;i<=n;i++) cout<<char(rand()%1+'a');
    cout<<endl;
    for(int i=1;i<=m;i++){
        int l=rand()%n+1,r=rand()%n+1,x=rand()%n+1;
        if(r<l) swap(l,r);
        cout<<l<<' '<<r<<' '<<x<<endl;
    }
}