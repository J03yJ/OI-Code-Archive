#include<bits/stdc++.h>

using namespace std;

#define Allc(x) x.begin(),x.end()

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        vector<int> a(n);
        for(int i=0;i<n;i++) cin>>a[i];
        while(a.size()>1){
            sort(Allc(a));
            a.push_back(a[0]+a[1]>>1);
            a.erase(a.begin(),a.begin()+2);
        }
        cout<<a[0]<<endl;
    }

    return 0;
}