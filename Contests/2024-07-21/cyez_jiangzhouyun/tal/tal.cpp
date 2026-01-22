#include<bits/stdc++.h>

using namespace std;

ifstream fin("tal.in");
ofstream fout("tal.out");
#define cin fin
#define cout fout

#define int long long
const int N=4e5+9;

int l[N],r[N],a[N],f[N];

signed main(){
    int n,q,typ;
    cin>>n>>q>>typ;
    for(int i=1;i<=n;i++) cin>>a[i];

    for(int i=1;i<=n;i++) r[i]=i;
    vector<int> stk;
    for(int i=1;i<=n;i++){
        while(stk.size()&&a[stk.back()]<a[i]) stk.pop_back();
        if(!stk.size()) l[i]=1;
        else l[i]=stk.back()+1;
        stk.push_back(i);
    }
    for(int i=1;i<=n;i++) f[l[i]]++,f[r[i]+1]--;
    for(int i=1;i<=n;i++) f[i]+=f[i-1];
    for(int i=1;i<=n;i++) f[i]+=f[i-1];

    while(q--){
        int ql,qr;
        cin>>ql>>qr;
        int ans=(f[qr]-f[ql-1])*(qr-ql+1)*2;
        for(int i=1;i<=n;i++){
            int l0=max(l[i],ql),r0=min(r[i],qr);
            if(l0>r0) continue ;
            ans-=(r0-l0+1)*(r0-l0+1);
        }
        cout<<ans<<endl;
    }

    return 0;
}