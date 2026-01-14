#include<bits/stdc++.h>

using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> a(n),b(n-1);
    for(int &x:a) cin>>x;
    for(int &x:b) cin>>x;

    sort(a.begin(),a.end());
    sort(b.begin(),b.end());

    int cnt=0,ans=0;
    for(int i=n-1,j=n-2;i>=0;i--,j--){
        if(j<0||a[i]>b[j]){
            cnt++,ans=a[i];
            j++;
        }
    }
    if(cnt==1) cout<<ans<<endl;
    else cout<<-1<<endl;

    return 0;
}