#include<bits/stdc++.h>

using namespace std;

ifstream fin("give.in");
ofstream fout("give.out");
#define cin fin
#define cout fout

const int N=2e5+9;

int a[N],bl[N],br[N],n,k;
int pre[N][1024],suf[N][1024];

int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    
    if(k<=2){
        long long ans=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++) bl[j]=br[j]=0;
            for(int l=i,r=i,lst=i,cl=0,cr=0;l>=1;l--){
                if(!bl[a[l]]){
                    cl++;
                    bl[a[l]]=1;
                    if(!br[a[l]]){
                        while(true){
                            r++;
                            if(r>n) break ;
                            if(!br[a[r]]) cr++,br[a[r]]=1;
                            if(a[r]==a[l]) break ;
                        }
                        if(r>n) break ;
                        lst=r;
                        while(r<n&&br[a[r+1]]) r++;
                    }
                }
                if(cl==cr) ans+=r-lst+1;
            }
        }
        cout<<ans<<endl;
    }else if(k==3){
        for(int i=1;i<=n;i++){
            for(int j=0;j<1024;j++) pre[i][j|(1<<a[i]-1)]+=pre[i-1][j];
            pre[i][1<<a[i]-1]++;
        }
        for(int i=n;i>=1;i--){
            for(int j=0;j<1024;j++) suf[i][j|(1<<a[i]-1)]+=suf[i+1][j];
            suf[i][1<<a[i]-1]++;
        }
        long long ans=0;
        for(int i=1;i<n;i++){
            for(int j=0;j<1024;j++) ans+=1ll*pre[i][j]*suf[i+1][j];
        }
        cout<<ans<<endl;
    }

    return 0;
}