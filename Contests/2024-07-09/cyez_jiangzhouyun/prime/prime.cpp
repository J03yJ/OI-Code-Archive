#include<bits/stdc++.h>

using namespace std;

ifstream fin("prime.in");
ofstream fout("prime.out");
#define cin fin
#define cout fout

#define int __int128

const int N=1e3+9;
const int V=1e6;
const int p=998244353;

int vis[V+9],pri[V+9],cnt;
void init(){
    for(int i=2;i<=V;i++){
        if(!vis[i]) pri[++cnt]=i;
        for(int j=1;j<=cnt&&pri[j]*i<=V;j++){
            vis[pri[j]*i]=1;
            if(i%pri[j]==0) break ;
        }
    }
}
int gcd(int x,int y){
    if(!y) return x;
    else return gcd(y,x%y);
}
int qpow(int x,int y,int p){
    int m=1;
    while(y){
        if(y&1) m=int(1)*m*x%p;
        x=int(1)*x*x%p;
        y>>=1;
    }
    return m;
}
bool test(int x){
    if(x%2==0||x<2) return x==2;
    int y=x-1,cnt=0;
    while(y%2==0) y>>=1,cnt++;
    for(int i=1;i<=12;i++){
        int val=qpow(pri[i]%x,y,x);
        if(pri[i]==x) continue ;
        if(val==1) continue ;
        for(int j=1;j<=cnt;j++){
            if(val==x-1) break ;
            val=val*val%x;
            if(j==cnt) return 0;
        }
    }
    return 1;
}

int a[N];
map<int,int> ans,siv;

signed main(){
    init();
    long long n;
    cin>>n;
    for(long long i=1,tmp;i<=n;i++) cin>>tmp,a[i]=tmp;
    
    vector<int> v,P;
    for(int i=1;i<=n;i++){
        int k=a[i];
        for(int j=1;j<=cnt&&pri[j]<=k;j++){
            if(k%pri[j]) continue ;
            ans[pri[j]]=(ans[pri[j]]+i*(n-i+1)%p)%p;
            while(k%pri[j]==0) k/=pri[j];
        }
        if(k!=1){
            ans[k]=(ans[k]+i*(n-i+1)%p)%p;
            v.push_back(k);
        }
    }
    for(int x:v){
        if(siv[x]) continue ;
        siv[x]=1;
        for(int y:v){
            if(siv[y]) continue ;
            if(x==y) continue ;
            int g=gcd(x,y);
            if(g==1) continue ;
            ans[g]=(ans[g]+ans[x]+ans[y])%p;
            ans[x/g]=(ans[x/g]+ans[x])%p;
            ans[y/g]=(ans[y/g]+ans[y])%p;
            ans[x]=ans[y]=0;
            // P.push_back(x/g);
            // P.push_back(y/g);
            // P.push_back(g);
        }
    }
    for(int x:v){
        int y=sqrt((long long)x);
        if(y*y!=x) continue ;
        if(!test(y)) continue ;
        ans[y]=(ans[y]+ans[x])%p;
        ans[x]=0;
        // P.push_back(y);
    }
    int res=1;
    for(pair<int,int> pr:ans){
        int val=pr.first,w=pr.second;
        // cout<<val<<' '<<w<<' '<<test(val)<<endl;
        if(!w) continue ;
        if(test(val)) res=res*w%p;
        else res=res*w%p*w%p;
    }

    cout<<(long long)res<<endl;

    return 0;
}