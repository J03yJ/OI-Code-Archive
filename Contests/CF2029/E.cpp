#include<bits/stdc++.h>

using namespace std;

const int N=4e5+9;

int pri[N],ntp[N],f[N],pcnt;
vector<int> d[N];
void InitP(int lim){
    for(int i=2;i<=lim;i++){
        if(!ntp[i]) pri[++pcnt]=i;
        for(int j=1;j<=pcnt&&pri[j]*i<=lim;j++){
            ntp[i*pri[j]]=1;
            if(i%pri[j]==0) break ;
        }
    }
    for(int i=1;i<=pcnt;i++){
        for(int j=pri[i];j<=lim;j+=pri[i]) d[j].push_back(pri[i]);
    }
    for(int i=1;i<=pcnt;i++) f[pri[i]]=i;
    for(int i=1;i<=lim;i++){
        if(!ntp[i]) continue ;
        for(int dlt:d[i]) f[i]=max(f[i],f[i-dlt]);
    }
}
int a[N],n;

int main(){
    InitP(4e5);
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];

        int mn=pcnt;
        for(int i=1;i<=n;i++) mn=min(mn,f[a[i]]);
        mn=pri[mn];
        for(int i=1;i<=n;i++){
            if(ntp[a[i]]) continue ;
            if(mn<a[i]){
                mn=-1;
                break ;
            }
        }
        cout<<mn<<endl;
    }
    
    return 0;
}