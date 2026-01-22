#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e5+9;

int arr[N],n;

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>arr[i];
        
        int a=0,b=0,c=0,ans=0;
        for(int i=1;i<=n;i++){
            int tmp=0;
            if(arr[i+1]<a+b){
                int k=a+b-arr[i+1];
                if(a<k) b-=k-a,k=a;
                if(b<k) a-=k-b,k=b;
                b-=k;
                a-=k;
                arr[i+1]-=k;
                tmp=k;
            }
            arr[i+1]-=a+b;

            int res=min(arr[i],arr[i+1]);
            ans+=res;
            arr[i]-=res;
            arr[i+1]-=res;
            a+=res;

            ans+=arr[i];
            c+=arr[i];
            arr[i]=0;

            arr[i+1]+=tmp;
            ans-=tmp;
            swap(b,c);
        }

        cout<<ans<<endl;
    }
}