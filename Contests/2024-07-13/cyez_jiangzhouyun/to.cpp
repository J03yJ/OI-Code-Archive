#include<bits/stdc++.h>

using namespace std;

ifstream fin("to.in");
ofstream fout("to.out");
#define cin fin
#define cout fout

#define int long long
const int N=5e3+9;
const int p=1e9+7;

int f[N][N],fac[N],inv[N],m;
int qpow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%p;
        x=x*x%p;
        y>>=1;
    }
    return res;
}
void init(){
    for(int i=0;i<=m;i++) f[i][0]=1;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=i;j++){
            f[i][j]=(f[i-1][j]+f[i-1][j-1]*i%p)%p;
            // cout<<f[i][j]<<' ';
        }
        // cout<<endl;
    }
    fac[0]=1;
    for(int i=1;i<=m;i++) fac[i]=fac[i-1]*i%p;
    inv[m]=qpow(fac[m],p-2);
    for(int i=m-1;~i;i--) inv[i]=inv[i+1]*(i+1)%p;
}
int P(int n,int m){return fac[n]*inv[n-m]%p;}
int invP(int n,int m){return fac[n-m]*inv[n]%p;}

string s;
int Bra[N<<1],tot,n;
void calc_op(){
    vector<int> stk;
    for(int i=1;i<=n;i++){
        if(s[i]=='(') stk.push_back(i);
        else if(s[i]==')'){
            int j=stk.back();
            stk.pop_back();
            Bra[i]=j;Bra[j]=i;
        }
    }
}

int buc[N];
struct node{
    int lc,rc;
    char op;vector<pair<int,int>> cnt;
}tr[N<<2];int cnt;
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define op(x) tr[x].op
#define cnt(x) tr[x].cnt
int build(int l,int r){
    // cout<<l<<' '<<r<<' '<<s[l]<<' '<<s[r]<<endl;
    if(l>r) return 0;
    if(s[l]=='('&&s[r]==')'&&Bra[l]==r) return build(l+1,r-1);
    int x=++cnt;
    if(l==r){
        if(s[l]!='_') return 0;
        op(x)='_';
        cnt(x).push_back({1,1});
        tot++;
        return x;
    }
    int mid=l+r>>1,pos=0;
    for(int i=l;i<=r;i++){
        if(s[i]=='('){
            i=Bra[i];
            continue ;
        }
        if(s[i]=='+'){
            if(!pos||s[pos]=='*'||abs(mid-pos)>abs(mid-i)) pos=i;
        }
        if(s[i]=='*'){
            if((!pos||abs(mid-pos)>abs(mid-i))&&s[pos]!='+') pos=i;
        }
    }
    // cout<<" << "<<s[pos]<<endl;
    op(x)=s[pos];
    lc(x)=build(l,pos-1);
    rc(x)=build(pos+1,r);
    if(op(x)=='*'){
        for(pair<int,int> a:cnt(lc(x))){
            for(pair<int,int> b:cnt(rc(x))){
                if(!buc[a.first+b.first]) cnt(x).push_back({a.first+b.first,0});
                buc[a.first+b.first]=(buc[a.first+b.first]+a.second*b.second%p)%p;
            }
        }
        for(int i=0;i<cnt(x).size();i++){
            cnt(x)[i].second=(cnt(x)[i].second+buc[cnt(x)[i].first])%p;
            buc[cnt(x)[i].first]=0;
        }
    }else{
        for(pair<int,int> a:cnt(lc(x))){
            if(!buc[a.first]) cnt(x).push_back({a.first,0});
            buc[a.first]=(buc[a.first]+a.second)%p;
        }
        for(pair<int,int> a:cnt(rc(x))){
            if(!buc[a.first]) cnt(x).push_back({a.first,0});
            buc[a.first]=(buc[a.first]+a.second)%p;
        }
        for(int i=0;i<cnt(x).size();i++){
            cnt(x)[i].second=(cnt(x)[i].second+buc[cnt(x)[i].first])%p;
            buc[cnt(x)[i].first]=0;
        }
    }
    // cout<<l<<" ~ "<<r<<" : ";
    // for(pair<int,int> a:cnt(x)) cout<<a.second<<'*'<<a.first<<' ';
    // cout<<endl;
    return x;
}

signed main(){
    cin>>m>>s;

    init();
    n=s.size();
    s=" "+s;
    calc_op();
    int root=build(1,n);

    int ans=0;
    for(pair<int,int> x:cnt(root)) ans=(ans+x.second*f[m][x.first]%p*P(m-x.first,tot-x.first)%p*P(x.first,x.first)%p)%p;
    cout<<ans*invP(m,tot)%p<<endl;

    return 0;
}