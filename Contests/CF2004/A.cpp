#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
int a[N];

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];

        bool flag=0;
        for(int ans=1;ans<=100;ans++){
            bool err=0;
            for(int i=1;i<=n;i++){
                if(ans==a[i]){
                    err=1;
                    break ;
                }
            }
            if(err) continue ;
            for(int i=1;i<=n;i++){
                int mn=1e9;
                for(int j=1;j<=n;j++){
                    if(i==j) continue ;
                    mn=min(mn,abs(a[i]-a[j]));
                }
                if(mn<abs(ans-a[i])) err=1;
            }
            if(err) continue ;
            flag=1;
            cout<<"YES"<<endl;
            break ;
        }
        if(!flag) cout<<"NO"<<endl;
    }
}