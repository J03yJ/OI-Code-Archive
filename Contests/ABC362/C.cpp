#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;

int a[N],l[N],r[N],n;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>l[i]>>r[i];

    int sum=0;
    for(int i=1;i<=n;i++){
        if(l[i]<=0&&r[i]>=0) a[i]=0;
        else if(r[i]<0) a[i]=r[i];
        else a[i]=l[i];
        sum+=a[i];
    }
    if(sum>0){
        for(int i=1;i<=n;i++){
            if(a[i]==l[i]) continue ;
            int k=a[i]-l[i];
            k=min(k,sum);
            sum-=k;
            a[i]-=k;
            if(sum==0) break ;
        }
    }else if(sum<0){
        for(int i=1;i<=n;i++){
            if(a[i]==r[i]) continue ;
            int k=r[i]-a[i];
            k=min(-sum,k);
            sum+=k;
            a[i]+=k;
            if(sum==0) break ;
        }
    }

    if(sum==0){
        cout<<"Yes"<<endl;
        for(int i=1;i<=n;i++) cout<<a[i]<<' ';
        cout<<endl;
    }else cout<<"No"<<endl;

    return 0;
}