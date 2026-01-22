#include<bits/stdc++.h>

using namespace std;

ifstream fin("ttheal.in");
ofstream fout("ttheal.out");
#define cin fin
#define cout fout

const int N=1e5+9;

int a[N],b[N],cnt[N],n;

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        int ans=0,l,r,x,y;
        for(int i=1;i<=n;i++){
            for(int j=i;j<=n;j++){
                for(int k=i;k<=j;k++) cnt[a[k]]++;
                int mx=0,pos=0;
                for(int k=1;k<=n;k++) if(cnt[k]>mx) mx=cnt[k],pos=k;
                for(int k=1;k<=n;k++) b[k]=cnt[k]-(cnt[k]&mx);
                int smx=0,spos=0;
                for(int k=1;k<=n;k++) if(b[k]>smx) smx=b[k],spos=k;
                if(mx+smx>ans) ans=mx+smx,l=i,r=j,x=pos,y=spos;
                for(int k=i;k<=j;k++) cnt[a[k]]--;
            }
        }
        cout<<ans<<endl;
        cout<<l<<' '<<r<<endl;
        cout<<x<<' '<<y<<endl;
    }

    return 0;
}