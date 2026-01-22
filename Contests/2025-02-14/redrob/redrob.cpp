#include<bits/stdc++.h>

using namespace std;

ifstream fin("redrob.in");
ofstream fout("redrob.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
using ull=unsigned long long;
const int N=1e6+9;

int a[N],n,m;
string s;
ll ans;

struct Node{
    int son[2],siz;
}tr[N<<5];
#define son(x,k) tr[x].son[k]
#define siz(x) tr[x].siz

int cnt=1;
inline int Allc(){return ++cnt;}

inline void Solve(){
    s="#"+s;
    for(int i=1;i<=n;i++){
        a[0]=a[1]=0;
        int p=1;
        for(int j=1,k=0;i+j-1<=n&&j<=50;j++){
            if(j!=1){
                while(k&&s[i+j-1]!=s[i+k]) k=a[k];
                if(s[i+j-1]==s[i+k]) k++;
                a[j]=k;
            }

            int f=s[i+j-1]=='b';
            if(!son(p,f)) son(p,f)=Allc();
            p=son(p,f);
            ans+=1ll*siz(p)*(j-a[j]);
            siz(p)++;
        }
    }
}

signed main(){
    cin>>n>>m>>s;

    if(m==1){
        ll sum=0;
        for(int i=1;i<=n;i++) sum+=1ll*i*(i-1)/2;
        cout<<sum<<endl;
    }else{
        Solve();
        cout<<ans<<endl;
    }

    return 0;
}