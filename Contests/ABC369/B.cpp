#include<bits/stdc++.h>

using namespace std;

int main(){
    int ans=0,n,lst[2]={0,0};
    cin>>n;
    for(int i=1;i<=n;i++){
        int a;char c;
        cin>>a>>c;
        if(c=='L'){
            if(lst[0]) ans+=abs(lst[0]-a);
            lst[0]=a;
        }else{
            if(lst[1]) ans+=abs(lst[1]-a);
            lst[1]=a;
        }
    }

    cout<<ans<<endl;

    return 0;
}