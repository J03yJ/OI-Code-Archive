#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=5e4+9;
const int mod=1e9+7;

int a[N][10],n,m,cnt;
struct Node{
    char c;
    int lc,rc,l,r;
}tr[N];
#define c(x) tr[x].c
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define l(x) tr[x].l
#define r(x) tr[x].r

int b[N],f[1<<11];
string s;
int Build(int l,int r){
    if(s[l]=='('&&s[r]==')'&&b[l]==r) return Build(l+1,r-1);
    int x=++cnt;
    l(x)=l;r(x)=r;
    if(l==r) return c(x)=s[l],x;
    int pos=0;
    for(int i=l;i<=r;i++){
        if(s[i]=='>'||s[i]=='<'||s[i]=='?'){
            pos=i;
            continue ;
        }
        if(s[i]=='(') i=b[i];
    }
    c(x)=s[pos];
    lc(x)=Build(l,pos-1),rc(x)=Build(pos+1,r);
    return x;
}
#define fir(x) (x).first
#define sec(x) (x).second
pair<int,int> F(int x,int sta){
    if(!lc(x)){
        if(sta>>c(x)-'0'&1) return {0,1};
        else return {1,0};
    }
    pair<int,int> lf=F(lc(x),sta),rf=F(rc(x),sta);
    // cout<<l(x)<<' '<<r(x)<<' '<<c(x)<<" : "<<fir(lf)<<' '<<sec(lf)<<' '<<fir(rf)<<' '<<sec(rf)<<endl;
    if(c(x)=='>'){
        return {fir(lf)*fir(rf)%mod,
                (fir(lf)*sec(rf)%mod+fir(rf)*sec(lf)%mod+sec(lf)*sec(rf)%mod)%mod};
    }else if(c(x)=='<'){
        return {(fir(lf)*sec(rf)%mod+fir(rf)*sec(lf)%mod+fir(lf)*fir(rf)%mod)%mod,
                sec(lf)*sec(rf)%mod};
    }else{
        return {(fir(lf)*sec(rf)%mod+fir(rf)*sec(lf)%mod+2*fir(lf)*fir(rf)%mod)%mod,
                (fir(lf)*sec(rf)%mod+fir(rf)*sec(lf)%mod+2*sec(lf)*sec(rf)%mod)%mod};
    }
}

signed main(){
    cin>>n>>m;
    for(int j=0;j<m;j++) for(int i=1;i<=n;i++) cin>>a[i][j];
    cin>>s;

    vector<int> stk;
    for(int i=0;i<s.size();i++){
        if(s[i]=='(') stk.push_back(i);
        else if(s[i]==')') b[stk.back()]=i,b[i]=stk.back(),stk.pop_back();
    }
    Build(0,s.size()-1);
    for(int sta=0;sta<(1<<m);sta++){
        // cout<<sta<<" : "<<endl;
        pair<int,int> tmp=F(1,sta);
        // cout<<fir(tmp)<<' '<<sec(tmp)<<endl;
        f[sta]=sec(tmp);
    }

    int sum=0;
    for(int i=1;i<=n;i++){
        vector<int> vec;
        for(int j=0;j<m;j++) vec.push_back(j);
        sort(vec.begin(),vec.end(),[i](int x,int y){return a[i][x]<a[i][y];});
        int sta=(1<<m)-1,lst=0,res=0;
        for(int j=0;j<m;j++){
            res=(res+(a[i][vec[j]]-lst)*f[sta]%mod)%mod;
            sta^=(1<<vec[j]);
            lst=a[i][vec[j]];
        }
        sum=(sum+res)%mod;
    }
    cout<<sum<<endl;

    return 0;
}