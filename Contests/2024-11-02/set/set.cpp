#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>

using namespace std;

ifstream fin("set.in");
ofstream fout("set.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e6+9;

unsigned long long h[N];
mt19937_64 myrand(1145);

int main(){
    ios::sync_with_stdio(0);
    fin.tie(0);
    fout.tie(0);

    int id,T;
    cin>>id>>T;
    while(T--){
        int n,m,ans=0;
        cin>>n>>m;
        for(int i=1;i<=n;i++) h[i]=0;
        for(int i=1,k;i<=m;i++){
            cin>>k;
            unsigned long long p=myrand();
            for(int j=1,l,r;j<=k;j++){
                cin>>l>>r;
                h[l]^=p,h[r+1]^=p;
            }
        }
        for(int i=1;i<=n;i++) h[i]^=h[i-1];

        __gnu_pbds::gp_hash_table<unsigned long long,int> mp;
        for(int i=1;i<=n;i++) mp[h[i]]++;
        for(int i=1;i<=n;i++) if(mp[h[i]]==1) ans++;

        cout<<ans<<endl;
    }

    return 0;
}