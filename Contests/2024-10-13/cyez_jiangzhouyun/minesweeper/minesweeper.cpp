#include<bits/stdc++.h>

using namespace std;

ifstream fin("minesweeper.in");
ofstream fout("minesweeper.out");
#define cin fin
#define cout fout

#define int long long
const int mod=998244353;
const int pmod=mod-1;

int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

signed main(){
    string s;
    cin>>s;

    if(s=="1"){
        cout<<0<<endl;
        return 0;
    }
    
    int x=0,y=0;
    for(int i=0;i<s.size();i++){
        x=x*10%mod;
        y=y*10%pmod;
        x=(x+s[i]-'0')%mod;
        y=(y+s[i]-'0')%pmod;
    }

    int inv2=QPow(2,mod-2),ans=inv2*inv2%mod*3%mod*4%mod,z=(x+mod-2)%mod;
    ans=(ans+inv2%mod*inv2%mod*5%mod*(z*4%mod)%mod)%mod;
    ans=(ans+inv2%mod*inv2%mod*8%mod*(z*z%mod)%mod)%mod;
    ans=ans*QPow(2,y*y%pmod)%mod;
    cout<<ans<<endl;

    return 0;
}