#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>

using namespace std;
using __gnu_pbds::gp_hash_table;

ifstream fin("make.in");
ofstream fout("make.out");
#define cin fin
#define cout fout

const int N=5e2+9;

int a[N],s[N],n;
long long ans;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    gp_hash_table<int,int> cnt;
    for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=0;k<j;k++){
                cnt[-(s[j]-s[k]-s[i-1])]++;
            }
        }
        for(int j=1;j<=n;j++){
            for(int k=0;k<j;k++){
                ans+=cnt[s[j]-s[k]+s[i]];
            }
        }
    }
    cnt.clear();
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++){
            cnt[-(s[i]-s[j])*2]++;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++){
            ans-=cnt[s[i]-s[j]]*3;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++){
            if(s[i]==s[j]) ans+=2;
        }
    }

    cout<<ans/6<<endl;

    return 0;
}