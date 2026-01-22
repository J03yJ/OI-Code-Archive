#include<bits/stdc++.h>

using namespace std;

#define int long long

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        if(n==1) cout<<3<<' '<<4<<endl;
        else if(n==2) cout<<"Poor"<<2<<endl;
        else{
            int ans1=0,ans2=0;
            for(int k=2;k<=n;k++){
                int a=n*2-4*k+2*k*k;
                int b=k*k-k;
                if(a<3*b) break ;
                if(a%b==0) ans2=ans1,ans1=a/b;
            }
            if(!ans1) cout<<"Poor"<<n<<endl;
            else if(!ans2) cout<<ans1<<endl;
            else cout<<ans1<<' '<<ans2<<endl;
        }
    }
}