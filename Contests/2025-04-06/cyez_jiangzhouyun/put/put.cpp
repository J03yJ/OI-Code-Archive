#include<bits/stdc++.h>

using namespace std;

ifstream fin("put.in");
ofstream fout("put.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e6+9;
const ll inf=1e18;

int n,m;
ll a[N],b[N],w[N],pre[N],k;
inline ll W(int len){
    deque<int> q;
    ll sum=0;
    for(int i=1,j=1;i<=n;i++){
        while(j<=n&&j-i+1<=len){
            while(q.size()&&pre[q.back()]<pre[j]) q.pop_back();
            q.push_back(j++);
        }
        while(q.size()&&q.front()<i) q.pop_front();
        if(pre[q.front()]<pre[i-1]) sum+=pre[i-1]-pre[q.front()];
    }
    return sum;
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;i++) cin>>a[i],a[i+n]=a[i];
        for(int i=1;i<=n;i++) cin>>b[i],b[i+n]=b[i];
        
        ll sum=0,mx=-1,suma=0;int st=0;
        for(int i=1;i<=n;i++){
            sum+=b[i]-a[i];
            suma+=a[i];
            if(sum>mx) mx=sum,st=i;
        }
        for(int i=1;i<=n;i++) a[i]=a[i+st],b[i]=b[i+st];
        if(suma<=k){
            cout<<0<<endl;
            continue ;
        }
        for(int i=1;i<=n;i++) w[i]=b[i]-a[i],pre[i]=pre[i-1]+w[i];
        int l=0,r=n+1;
        while(l+1<r){
            int mid=l+r>>1;
            if(W(mid)<=k) r=mid;
            else l=mid;
        }
        cout<<r<<endl;
    }

    return 0;
}