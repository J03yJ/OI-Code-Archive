#include<bits/stdc++.h>

using namespace std;

#define int long long

const int N=2e5+9;
int a[N],b[N],c[N],p[4],s[N];
int l[4],r[4];
int ansl[4],ansr[4];

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++) cin>>b[i];
        for(int i=1;i<=n;i++) cin>>c[i];

        int sum=0;
        for(int i=1;i<=n;i++) sum+=a[i];
        int k=(sum+2)/3;

        bool flag=0;
        for(int i=1;i<=3;i++) p[i]=i;
        do{
            for(int i=1;i<=n;i++){
                if(p[1]==1) s[i]=s[i-1]+a[i];
                if(p[1]==2) s[i]=s[i-1]+b[i];
                if(p[1]==3) s[i]=s[i-1]+c[i];
            }
            int pos1=lower_bound(s+1,s+n+1,k)-s;
            for(int i=1;i<=n;i++) s[i]=0;
            for(int i=1;i<=n;i++){
                if(p[3]==1) s[i]=s[i-1]+a[n-i+1];
                if(p[3]==2) s[i]=s[i-1]+b[n-i+1];
                if(p[3]==3) s[i]=s[i-1]+c[n-i+1];
            }
            int pos3=lower_bound(s+1,s+n+1,k)-s;
            pos3=n-pos3+1;
            l[1]=1;r[1]=pos1;
            l[3]=pos3;r[3]=n;
            l[2]=pos1+1;r[2]=pos3-1;
            for(int i:{1,2,3}) ansl[p[i]]=l[i],ansr[p[i]]=r[i];

            // for(int i:{1,2,3}) cout<<p[i]<<' ';cout<<endl;
            // cout<<" : ";for(int i:{1,2,3}) cout<<ansl[i]<<' '<<ansr[i]<<' ';
            // cout<<endl;
            for(int i=1;i<=n;i++) s[i]=0;
            for(int i=1;i<=n;i++){
                if(p[2]==1) s[i]=s[i-1]+a[i];
                if(p[2]==2) s[i]=s[i-1]+b[i];
                if(p[2]==3) s[i]=s[i-1]+c[i];
            }
            // cout<<s[r[2]]-s[l[2]-1]<<endl;
            if(s[r[2]]-s[l[2]-1]>=k){
                flag=1;
                break ;
            }
            for(int i=1;i<=n;i++) s[i]=0;
        }while(next_permutation(p+1,p+4));
        if(flag){
            for(int i:{1,2,3}) cout<<ansl[i]<<' '<<ansr[i]<<' ';
            cout<<endl;
        }else cout<<-1<<endl;
        // cout<<endl;
    }
}