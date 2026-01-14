#include<bits/stdc++.h>

using namespace std;

const int N=4e5+9;

int a[N],n;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    if(n&3){
        int cnt=0;
        for(int i=1;i<=n;i++) cnt+=a[i];
        if(n&1){
            if(cnt) cout<<"Yes"<<endl;
            else cout<<"No"<<endl;
        }else{
            if(cnt<2) cout<<"No"<<endl;
            else{
                int c[2]={0,0};
                for(int i=1;i<=n;i++) if(a[i]) c[i&1]++;
                if(c[0]&&c[1]) cout<<"Yes"<<endl;
                else cout<<"No"<<endl;
            }
        }
    }else cout<<"Yes"<<endl;

    return 0;
}