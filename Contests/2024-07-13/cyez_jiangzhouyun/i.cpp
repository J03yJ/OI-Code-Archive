#include<bits/stdc++.h>

using namespace std;

ifstream fin("i.in");
ofstream fout("i.out");
#define cin fin
#define cout fout

const int N=2e5+9;

long long a[N];

int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    int l=1,r=n;
    while(a[l+1]<a[l]) l++;
    while(a[r-1]<a[r]) r--;

    long long cnt=0;
    for(int i=l+1;i<r;i++){
        if(a[i]>a[i-1]&&a[i]>a[i+1]){
            a[i]=min(a[i-1],a[i+1])-1;
            cnt+=i-l;
            l++;
            // for(int j=i;j>l;j--){
            //     if(a[j]>a[j-1]&&a[j]>a[j+1]){
            //         while(a[l+1]<a[l]) l++;
            //         while(a[r-1]<a[r]) r--;
            //         a[j]=min(a[j-1],a[j+1])-1;
            //         cnt++;
            //     }
            // }
        }
    }

    cout<<cnt<<endl;

    return 0;
}