#include<bits/stdc++.h>

using namespace std;

#define int long long
const int C=7;
const int p=1e9+7;
const int N=5e4+9;

int qpow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%p;
        x=x*x%p;
        y>>=1;
    }
    return res;
}

map<char,int> mp;
const int LEN=10;
int pro[LEN+1],P[C+1],sum;
struct dat{
    int dp[LEN+1][LEN+1];
    dat(){
        for(int i=0;i<=LEN;i++){
            for(int j=0;j<=LEN;j++){
                if(!i||!j||i>j) dp[i][j]=1;
                else dp[i][j]=0;
            }
        }
    }
    dat(int k){
        for(int i=0;i<=LEN;i++){
            for(int j=0;j<=LEN;j++){
                if(!i||!j||i>j) dp[i][j]=1;
                else dp[i][j]=0;
            }
        }
        if(!k){
            for(int i=1;i<=LEN;i++) dp[i][i]=pro[i];
        }else{
            string s="#helloworld";
            for(int i=1;i<s.size();i++){
                if(mp[s[i]]==k) dp[i][i]=1;
            }
        }
    }
    int* operator [](int k){
        return dp[k];
    }
    dat operator +(dat x){
        dat res;
        for(int r=1;r<=LEN;r++){
            for(int k=0;k<=r;k++){
                if(!x[k+1][r]) continue ;
                for(int l=min(r,k+1);l>=1&&dp[l][k];l--){
                    res[l][r]=(res[l][r]+dp[l][k]*x[k+1][r]%p)%p;
                }
            }
        }
        return res;
    }
    void debug(){
        for(int i=1;i<=LEN;i++){
            for(int j=i;j<=LEN;j++){
                cout<<dp[i][j]<<' ';
            }
            cout<<endl;
        }
        cout<<endl;
    }
};

int n;
dat a[N];

struct node{
    int l,r;
    dat v;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define v(x) tr[x].v
void build(int x,int l,int r){
    l(x)=l;r(x)=r;
    v(x)=dat(0);
    if(l(x)==r(x)){
        v(x)=a[l(x)];
        return ;
    }
    int mid=l(x)+r(x)>>1;
    build(x<<1,l(x),mid);
    build(x<<1|1,mid+1,r(x));
    v(x)=v(x<<1)+v(x<<1|1);
    cout<<x<<" : "<<endl;
    v(x).debug();
}
void modify(int x,int pos,dat &k){
    if(l(x)==r(x)){
        v(x)=k;
        return ;
    }
    int mid=l(x)+r(x)>>1;
    if(pos<=mid) modify(x<<1,pos,k);
    else modify(x<<1|1,pos,k);
    v(x)=v(x<<1)+v(x<<1|1);
}
dat query(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r){
        cout<<l(x)<<' '<<r(x)<<endl;
        return v(x);
    }
    int mid=l(x)+r(x)>>1;
    if(l<=mid&&r>mid){
        dat lc=query(x<<1,l,r);
        dat rc=query(x<<1|1,l,r);
        return lc+rc;
    }
    else if(l<=mid) return query(x<<1,l,r);
    else return query(x<<1|1,l,r);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    mp['h']=1;mp['e']=2;mp['l']=3;mp['o']=4;mp['w']=5;mp['r']=6;mp['d']=7;
    int T;
    cin>>T;
    while(T--){
        memset(tr,0,sizeof tr);
        memset(a,0,sizeof a);
        memset(P,0,sizeof P);
        memset(pro,0,sizeof pro);

        cin>>n;
        for(int i=1;i<=C;i++) cin>>P[i];

        sum=0;
        for(int i=1;i<=C;i++) sum=(sum+P[i])%p;
        sum=qpow(sum,p-2);
        for(int i=1;i<=C;i++) P[i]=P[i]*sum%p;
        string s="#helloworld";
        for(int i=1;i<s.size();i++) pro[i]=P[mp[s[i]]];
        for(int i=1;i<=n;i++) a[i]=dat(0);
        build(1,1,n);
        cout<<"DKD"<<endl;

        int q;
        cin>>q;
        while(q--){
            int opt,x,y;
            cin>>opt;
            if(opt==1){
                char c;
                cin>>x>>c;
                y=mp[c];
                a[x]=dat(y);
                modify(1,x,a[x]);
                
            }else{
                cin>>x>>y;
                cout<<query(1,x,y).dp[1][LEN]<<endl;
            }
        }
    }
}