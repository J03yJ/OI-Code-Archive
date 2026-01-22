#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;
const int mod=998244353;

int a[N],b[N],ia[N],ib[N],ai[N],bi[N],n,q;
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    int T;
    cin>>T;
    while(T--){
        cin>>n>>q;
        for(int i=1;i<=n;i++) cin>>a[i],ai[i]=i;
        for(int i=1;i<=n;i++) cin>>b[i],bi[i]=i;

        stable_sort(ai+1,ai+n+1,[](int x,int y){return a[x]<a[y];});
        stable_sort(bi+1,bi+n+1,[](int x,int y){return b[x]<b[y];});
        stable_sort(a+1,a+n+1),stable_sort(b+1,b+n+1);
        for(int i=1;i<=n;i++) ia[ai[i]]=i,ib[bi[i]]=i;

        int res=1;
        for(int i=1;i<=n;i++) res=res*min(a[i],b[i])%mod;
        cout<<res<<' ';

        while(q--){
            int op,pos;
            cin>>op>>pos;
            if(op==1){
                int qos=ai[upper_bound(a+1,a+n+1,a[ia[pos]])-a-1];
                swap(ai[ia[pos]],ai[ia[qos]]);
                swap(ia[pos],ia[qos]);
                // swap(pos,qos);
                pos=ia[pos];
                // cout<<a[pos]<<'-'<<b[pos]<<endl;
                res=res*Inv(min(a[pos],b[pos]))%mod;
                a[pos]++;
                res=res*min(a[pos],b[pos])%mod;
            }else{
                int qos=bi[upper_bound(b+1,b+n+1,b[ib[pos]])-b-1];
                swap(bi[ib[pos]],bi[ib[qos]]);
                swap(ib[pos],ib[qos]);
                // swap(pos,qos);
                pos=ib[pos];
                // cout<<a[pos]<<'='<<b[pos]<<endl;
                res=res*Inv(min(a[pos],b[pos]))%mod;
                b[pos]++;
                res=res*min(a[pos],b[pos])%mod;
            }
            cout<<res<<' ';
            // for(int i=1;i<=n;i++) cout<<a[i]<<' ';cout<<endl;
            // for(int i=1;i<=n;i++) cout<<b[i]<<' ';cout<<endl;
        }
        cout<<endl;
    }

    return 0;
}