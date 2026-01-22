#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int p[N],n;
pair<int,int> And(pair<int,int> x,pair<int,int> y){
    return {max(x.first,y.first),min(x.second,y.second)};
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>p[i];

    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            swap(p[i],p[j]);
            
            swap(p[i],p[j]);
        }
    }

    return 0;
}