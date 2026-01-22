#include<bits/stdc++.h>

using namespace std;

ifstream fin("b.in");
ofstream fout("b.out");
#define cin fin
#define cout fout

#define int long long
const int N=2e5+9;

int a[N],ra[N],p[3],ans[N],n;

struct BIT{
    int tr[N];
    inline void Add(int x,int k){
        while(x<=n){
            tr[x]+=k;
            x+=x&-x;
        }
    }
    inline int Ask(int x){
        int sum=0;
        while(x){
            sum+=tr[x];
            x&=x-1;
        }
        return sum;
    }
    inline int Ask(int l,int r){
        return Ask(r)-Ask(l-1);
    }
}b;

signed main(){
    cin>>n;
    for(int i=0;i<3;i++) cin>>p[i];
    for(int i=1;i<=n;i++) cin>>a[i],ans[i]=1;

    int sum=0;
    if(p[0]==2){
        if(p[1]==1){
            for(int i=1;i<=n;i++){
                int k=b.Ask(1,a[i]);
                sum+=k*(k-1)/2;
                b.Add(a[i],1);
            }
            memset(b.tr,0,sizeof(b.tr));
            for(int i=1;i<=n;i++){
                ans[i]*=b.Ask(1,a[i]);
                b.Add(a[i],1);
            }
            memset(b.tr,0,sizeof(b.tr));
            for(int i=n;i;i--){
                ans[i]*=b.Ask(a[i],n);
                b.Add(a[i],1);
            }
        }else{
            for(int i=1;i<=n;i++){
                int k=b.Ask(a[i],n);
                sum+=k*(k-1)/2;
                b.Add(a[i],1);
            }
            memset(b.tr,0,sizeof(b.tr));
            for(int i=1;i<=n;i++){
                ans[i]*=b.Ask(a[i],n);
                b.Add(a[i],1);
            }
            memset(b.tr,0,sizeof(b.tr));
            for(int i=n;i;i--){
                ans[i]*=b.Ask(1,a[i]);
                b.Add(a[i],1);
            }
        }
        for(int i=1;i<=n;i++) sum-=ans[i];
    }else if(p[1]==2){
        if(p[0]==1){
            for(int i=1;i<=n;i++){
                ans[i]*=b.Ask(1,a[i]);
                b.Add(a[i],1);
            }
            memset(b.tr,0,sizeof(b.tr));
            for(int i=n;i;i--){
                ans[i]*=b.Ask(a[i],n);
                b.Add(a[i],1);
            }
        }else{
            for(int i=1;i<=n;i++){
                ans[i]*=b.Ask(a[i],n);
                b.Add(a[i],1);
            }
            memset(b.tr,0,sizeof(b.tr));
            for(int i=n;i;i--){
                ans[i]*=b.Ask(1,a[i]);
                b.Add(a[i],1);
            }
        }
        for(int i=1;i<=n;i++) sum+=ans[i];
    }else{
        if(p[0]==1){
            for(int i=n;i;i--){
                int k=b.Ask(a[i],n);
                sum+=k*(k-1)/2;
                b.Add(a[i],1);
            }
            memset(b.tr,0,sizeof(b.tr));
            for(int i=1;i<=n;i++){
                ans[i]*=b.Ask(1,a[i]);
                b.Add(a[i],1);
            }
            memset(b.tr,0,sizeof(b.tr));
            for(int i=n;i;i--){
                ans[i]*=b.Ask(a[i],n);
                b.Add(a[i],1);
            }
        }else{
            for(int i=n;i;i--){
                int k=b.Ask(1,a[i]);
                sum+=k*(k-1)/2;
                b.Add(a[i],1);
            }
            memset(b.tr,0,sizeof(b.tr));
            for(int i=1;i<=n;i++){
                ans[i]*=b.Ask(a[i],n);
                b.Add(a[i],1);
            }
            memset(b.tr,0,sizeof(b.tr));
            for(int i=n;i;i--){
                ans[i]*=b.Ask(1,a[i]);
                b.Add(a[i],1);
            }
        }
        for(int i=1;i<=n;i++) sum-=ans[i];
    }

    cout<<sum<<endl;

    return 0;
}