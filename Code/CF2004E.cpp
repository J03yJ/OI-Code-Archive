#include<bits/stdc++.h>

using namespace std;

const int V=1e7+9;

int pri[V],ntp[V],lpf[V],cnt;
void InitP(int n){
    for(int i=2;i<=n;i++){
        if(!ntp[i]) pri[++cnt]=i;
        for(int j=1;j<=cnt&&pri[j]*i<=n;j++){
            ntp[pri[j]*i]=1;
            if(i%pri[j]==0) break ;
        }
    }
    for(int i=1;i<=cnt;i++){
        for(int j=1;pri[i]*j<=n;j++) if(!lpf[j*pri[i]]) lpf[j*pri[i]]=i;
    }
}
inline int SG(int x){
    if(x==1) return 1;
    else if(x%2==0) return 0;
    else return lpf[x];
}

int main(){
    InitP(1e7);
    
    int T;
    cin>>T;
    while(T--){
        int n,res=0;
        cin>>n;
        for(int i=1,x;i<=n;i++) cin>>x,res^=SG(x);
        if(res) cout<<"Alice"<<endl;
        else cout<<"Bob"<<endl;
    }

    return 0;
}