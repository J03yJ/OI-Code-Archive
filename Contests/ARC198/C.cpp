#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
#define fir(x) x.first
#define sec(x) x.second
using pii=pair<int,int>;
const int N=1e2+9;

int a[N],b[N],n;
vector<pii> ans;
inline void Do(int i,int j){
    ans.push_back({i,j});
    a[i]++,a[j]--;
    swap(a[i],a[j]);
}
inline void Swap(int i,int j){
    int k=j+1;
    Do(i,k),Do(j,k),Do(i,k);
}
inline void Back(int i,int j){
    Swap(i,j);
    Do(i,j);
}
inline void Front(int i,int j){
    Do(i,j);
    Swap(i,j);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];

    if(n==2){
        if(a[1]==b[1]&&a[2]==b[2]){
            cout<<"Yes"<<endl;
            cout<<ans.size()<<endl;
            for(auto p:ans) cout<<fir(p)<<' '<<sec(p)<<endl;
            return 0;
        }
        Do(1,2);
        if(a[1]==b[1]&&a[2]==b[2]){
            cout<<"Yes"<<endl;
            cout<<ans.size()<<endl;
            for(auto p:ans) cout<<fir(p)<<' '<<sec(p)<<endl;
            return 0;
        }
        cout<<"No"<<endl;
        return 0;
    }

    int suma=0,sumb=0;
    for(int i=1;i<=n;i++) suma+=a[i];
    for(int i=1;i<=n;i++) sumb+=b[i];
    if(suma!=sumb){
        cout<<"No"<<endl;
        return 0;
    }

    for(int i=n;i>=3;i--){
        int p=i;
        if(a[i]>b[i]){
            while(a[p]>b[i]-1){
                Do(p-1,p);
                p--;
                if(p==1){
                    Do(p,i);
                    p=i;
                }
            }
            if(p!=i) Do(p,i);
            else Do(i-2,i),Do(i-2,i-1),Do(i-1,i);
        }else if(a[i]<b[i]){
            int p=1;
            Do(p,i);
            while(a[p]<b[i]-1){
                Do(p,p+1);
                p++;
                if(p==i){
                    Do(1,p);
                    p=1;
                }
            }
            if(p!=i) Do(p,i);
            else Do(i-2,i),Do(i-2,i-1),Do(i-1,i);
        }
    }
    while(a[1]<b[1]) Front(1,2);
    while(a[1]>b[1]) Back(1,2);

    assert(ans.size()<=31000);
    for(int i=1;i<=n;i++) assert(a[i]==b[i]);
    // for(int i=1;i<=n;i++) cout<<a[i]<<' ';cout<<endl;
    // for(int i=1;i<=n;i++) cout<<b[i]<<' ';cout<<endl;

    cout<<"Yes"<<endl;
    cout<<ans.size()<<endl;
    for(auto p:ans) cout<<fir(p)<<' '<<sec(p)<<endl;

    return 0;
}