#include<bits/stdc++.h>

using namespace std;

ifstream fin("watchtower.in");
ofstream fout("watchtower.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=8e3+9;

int p[N],n;

signed main(){
    int id,T;
    cin>>id>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>p[i];
        if(n<=1){
            cout<<0<<endl;
            continue ;
        }
        ll res=0;
        for(int i=1;i<=n;i++){
            int tmp=0;
            if(i!=1) tmp=max(tmp,p[i]-p[i-1]);
            if(i!=n) tmp=max(tmp,p[i+1]-p[i]);
            res+=1ll*tmp*tmp;
        }
        cout<<res<<endl;
    }

    return 0;
}