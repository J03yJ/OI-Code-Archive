#include<bits/stdc++.h>

using namespace std;

const int N=2e3+9;

int a[N];

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];

        map<long long,int> mp;
        long long ans=0;
        for(int i=1;i<=n;i++) ans+=1ll*i*(n-i);
        for(int i=1;i<=n;i++){
            long long sum=0;
            for(int j=i;j<=n;j++) ans-=mp[sum+=a[j]]<<1;
            sum=0;
            for(int j=i;j>=1;j--) mp[sum+=a[j]]++;
        }
        for(int i=1;i<=n;i++){
            long long suml=0,sumr=0;
            for(int j=i,cur=i;j<=n;j++){
                sumr+=a[j];
                while(cur>1&&suml<sumr) suml+=a[--cur];
                if(suml==sumr) ans++;
            }
        }
        
        cout<<ans<<endl;
    }

    return 0;
}