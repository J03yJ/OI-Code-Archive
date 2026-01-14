#include<bits/stdc++.h>

using namespace std;

ifstream fin("puzzle.in");
ofstream fout("puzzle.out");
#define cin fin
#define cout fout

const int N=5e5+9;

int p[N],tmp[N],val[N],tot,n;
int u[N],v[N],m;
void Work(){
    tot=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>p[i];
    for(int i=1;i<=m;i++) cin>>u[i]>>v[i];

    map<int,int> mp;
    for(int i=1;i<=n;i++) mp[p[i]]=1;
    for(int i=1;i<=n;i++) if(!mp[i]) val[++tot]=i;

    do{
        for(int i=1;i<=n;i++) tmp[i]=p[i];
        for(int i=1,j=1;i<=n;i++) if(!tmp[i]) tmp[i]=val[j++];
        int err=0;
        for(int i=1;i<=m;i++){
            if(tmp[u[i]]>=tmp[v[i]]) err=1;
        }
        if(!err){
            for(int i=1;i<=n;i++) cout<<tmp[i]<<' ';cout<<endl;
            return ;
        }
    }while(next_permutation(val+1,val+tot+1));
    cout<<-1<<endl;
}

int main(){
    int T;
    cin>>T;
    while(T--) Work();

    return 0;
}