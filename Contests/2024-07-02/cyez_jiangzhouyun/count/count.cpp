#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;

ifstream fin("count.in");
ofstream fout("count.out");
#define cin fin
#define cout fout

int fi[N],ne[N],to[N],ind[N],adj;
double p[N];
void adeg(int x,int y,double z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    p[adj]=z;
    ind[y]++;
}

double P[N];

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x,y;double k;
        cin>>x>>y>>k;
        adeg(x,y,k);
    }
    P[1]=1;
    queue<int> q;
    for(int i=1;i<=n;i++) if(!ind[i]) q.push(i);
    while(q.size()){
        int x=q.front();
        q.pop();
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            P[y]+=P[x]*p[i];
            ind[y]--;
            if(!ind[y]) q.push(y);
        }
    }
    cout<<fixed<<setprecision(2)<<P[n]<<endl;
    return 0;
}