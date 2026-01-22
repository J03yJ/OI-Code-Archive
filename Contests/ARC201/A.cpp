#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;

int a[N],b[N],c[N],n;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i]>>b[i]>>c[i];

        vector<int> p,q;
        for(int i=1;i<=n;i++){
            a[i]=min(a[i],b[i]);
            c[i]=min(c[i],b[i]);
            if(b[i]>=a[i]+c[i]) p.push_back(i);
            else q.push_back(i);
        }

        ll hi=0,lo=0;
        for(int i:p) hi+=a[i],lo+=c[i];
        for(int i:q){
            int maxa=min(a[i],b[i]),maxc=min(c[i],b[i]);
            int mina=b[i]-maxc,minc=b[i]-maxa;
            hi+=mina,lo+=minc;
            a[i]-=mina,b[i]-=mina+minc,c[i]-=minc;
        }
        for(int i:q){
            int maxa=min(a[i],b[i]),maxc=min(c[i],b[i]);
            int mina=b[i]-maxc,minc=b[i]-maxa;
            if(hi>lo){
                if(hi+mina>=lo+maxc) hi+=mina,lo+=maxc;
                else{
                    ll sum=hi+lo+b[i];
                    lo=sum>>1;
                    hi=sum-lo;
                }
            }else{
                if(lo+minc>=hi+maxa) hi+=maxa,lo+=minc;
                else{
                    ll sum=hi+lo+b[i];
                    hi=sum>>1;
                    lo=sum-hi;
                }
            }
        }

        cout<<min(lo,hi)<<endl;
    }

    return 0;
}