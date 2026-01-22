#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;

int pri[N],ntp[N],cnt;
void InitP(int n){
    for(int i=2;i<=n;i++){
        if(!ntp[i]) pri[++cnt]=i;
        for(int j=1;j<=cnt&&pri[j]*i<=n;j++){
            ntp[pri[j]*i]=1;
            if(i%pri[j]==0) continue ;
        }
    }
}

int l[N],a[N],b[N],n;

int main(){
    InitP(sqrt(1e9));
    
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i],l[i]=i;

        long long ans=0;
        b[0]=1;
        int lst[2]={0,0};
        for(int i=1,cur=0;i<=n;i++){
            while(b[i]%2==0) b[i]/=2;
            for(int j=i-1;j>=0;j--){
                if(__gcd(b[i],b[j])==1){
                    l[i]=j;
                    // cout<<b[i]<<' '<<b[j]<<endl;
                    break ;
                }
            }
            l[i]=min(l[i],lst[a[i]%2]);
            cout<<l[i]<<'/'<<b[i]<<'/'<<b[l[i]]<<'\n';
            lst[a[i]%2]=i;
            cur=max(cur,l[i]);
            ans+=cur+1;
        }

        cout<<ans<<endl;
    }

    return 0;
}