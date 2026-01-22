#include<bits./stdc++.h>

using namespace std;

ifstream fin("npc.in");
ofstream fout("npc.out");
#define cin fin
#define cout fout

const int N=1e6+9;

map<int,vector<int>> mp;
bool b[N];int phi[N],p[N],cnt;

int main(){
    for(int i=2;i<=1e5;i++){
        if(!b[i]) phi[i]=i-1,p[++cnt]=i;
        for(int j=1;j<=cnt&&p[j]*i<=1e5;j++){
            b[p[j]*i]=1;
            if(i%p[j]) phi[p[j]*i]=phi[i]*(p[j]-1);
            else{
                phi[p[j]*i]=phi[i]*p[j];
                break ;
            }
        }
        mp[phi[i]].push_back(i);
        // cout<<phi[i]<<'/'<<i<<' ';
    }
    // cout<<endl;
    // for(pair<int,vector<int>> p:mp){
    //     cout<<p.first<<" : ";
    //     for(int x:p.second) cout<<x<<' ';cout<<endl;
    // }
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        cout<<mp[n].size()<<endl;
        // for(int x:mp[n]) cout<<x<<' ';cout<<endl;
    }
    return 0;
}