#include<bits/stdc++.h>

using namespace std;

ifstream fin("transform.in");
ofstream fout("transform.out");
#define cin fin
#define cout fout

#define int long long
#define bint __int128

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,k,m,a,b;
        cin>>n>>k>>m>>a>>b;
        if(k==1){
            if(n==m) cout<<0<<endl;
            else if(!m) cout<<1<<endl;
            else cout<<-1<<endl;
            continue ;
        }
        int ans=1e18;
        for(bint x=n,i=0;;x/=k,i++){
            int res=i*b;
            // cout<<(int)x<<" : "<<endl;
            for(bint y=x,z=1;;y*=k,z*=k,res+=a){
                bint r=(m-y%m)%m;
                // cout<<res<<' '<<(int)y<<' '<<(int)r<<endl;
                if(r<z){
                    ans=min(ans,res);
                    break ;
                }
            }
            if(!x) break ;
        }
        cout<<ans<<endl;
    }
    return 0;
}