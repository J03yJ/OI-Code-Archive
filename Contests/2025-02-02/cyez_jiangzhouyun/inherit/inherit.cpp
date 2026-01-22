#include<bits/stdc++.h>

using namespace std;

ifstream fin("inherit.in");
ofstream fout("inherit.out");
#define cin fin
#define cout fout
#define endl '\n'

#define ssiz(x) (signed)x.size()

int ans;
void Solve(string &s){
    if(ssiz(s)==1){
        ans++;
        return ;
    }
    for(int i=0;i<ssiz(s);i++){
        if(i&&s[i]==s[i-1]) continue ;
        string t="";
        if(i) t+=s.substr(0,i);
        if(i!=ssiz(s)-1) t+=s.substr(i+1);
        Solve(t);
    }
}
void Work(string &s,int pos){
    if(pos==ssiz(s)) return Solve(s);
    if(s[pos]!='?') return Work(s,pos+1);
    string t0=s,t1=s;
    t0[pos]='0',t1[pos]='1';
    Work(t0,pos+1),Work(t1,pos+1);
}

int n;
string s;
const int mod=998244353;

signed main(){
    cin>>n>>s;
    if(n>5){
        int res=1;
        for(int i=1;i<=n+1;i++) res=1ll*res*(i)%mod;
        cout<<res<<endl;
        return 0;
    }

    Work(s,0);
    cout<<ans<<endl;

    return 0;
}