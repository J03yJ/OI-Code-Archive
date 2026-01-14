#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int a[N],cnt[N],c[N],n,k;

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++){
            if(a[i]>n) continue ;
            cnt[a[i]]++;
        }
        for(int i=0;i<=n;i++){
            if(!cnt[i]){
                if(c[i%k]) c[i%k]--,cnt[i]++;
                else{
                    cout<<i<<endl;
                    break ;
                }
            }
            cnt[i]--;
            c[i%k]+=cnt[i];
        }
        for(int i=0;i<=n;i++) cnt[i]=0;
        for(int i=0;i<=min(n,k);i++) c[i]=0;
    }

    return 0;
}