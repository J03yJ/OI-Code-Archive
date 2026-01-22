#include<bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        vector<int> a(n);
        for(int &x:a) cin>>x;
        int cnt1=0,cnt2=0;
        for(int x:a){
            if(x&1) cnt1++;
            else cnt2++;
        }
        if(cnt2) cnt1++;
        else cnt1--;
        cout<<cnt1<<endl;
    }

    return 0; 
}