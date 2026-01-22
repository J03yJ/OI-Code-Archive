#include<cstdio>
#include<algorithm>
#include<vector>
#include<cctype>
#include<cstring>
#include<iostream>
#define N 100005
#define siz 317
class istream{
    char buf[15000003],*s;
    public:
        inline istream(){
            buf[fread(s=buf,1,15000001,stdin)]='\n';
            fclose(stdin);
        }
        template<typename T>
        inline istream&operator>>(T&rhs){
            for(rhs=0;!isdigit(*s);++s);
            while(isdigit(*s))rhs=rhs*10+(*s++&15);
            return*this;
        }
}cin;
struct ostream{
    char buf[8000005],*s;
    inline ostream(){s=buf;}
    inline void operator<<(long long d){
        if(!d){
            *s++='0';
        }else{
            static long long w;
            for(w=1;w<=d;w*=10);
            for(;w/=10;d%=w)*s++=d/w^'0';
        }
        *s++='\n';
    }
    inline ostream&operator<<(const char&c){*s++=c;return*this;}
    inline~ostream(){fwrite(buf,1,s-buf,stdout);}
}cout;
std::vector<int>ls;
int n,m,a[N];
long long L_R[N],R_L[N],ans[N],out[N];
struct BiT{
    int b[N];
    inline void add(int i){for(;i<N;i+=i&-i)++b[i];}
    inline int ask(int i){int x=0;for(;i;i^=i&-i)x+=b[i];return x;}
}b;
struct que{
    int l,r,id;
    inline bool operator<(const que&rhs)const{
        return(l/siz!=rhs.l/siz)?(l<rhs.l):(r<rhs.r);
    }
}q[N];
struct node{
    int l,r,id,op;
};
std::vector<node>L[N],R[N];
int bL[320],bR[320],bel[123456],c[123456],s[320];
int main(){
    ls.push_back(-1);
    cin>>n>>m;
    for(int i=1;i<=n;ls.push_back(a[i++]))cin>>a[i];
    std::sort(ls.begin(),ls.end());
    ls.erase(std::unique(ls.begin(),ls.end()),ls.end());
    for(int i=1;i<=n;++i)a[i]=std::lower_bound(ls.begin(),ls.end(),a[i])-ls.begin();
    for(int i=1;i<=n;++i){
        L_R[i]=L_R[i-1]+b.ask(1e5)-b.ask(a[i]);
        b.add(a[i]);
    }
    memset(b.b,0,sizeof b.b);
    for(int i=n;i;--i){
        R_L[i]=R_L[i+1]+b.ask(a[i]-1);
        b.add(a[i]);
    }
    for(int i=1;i<=m;++i)cin>>q[i].l>>q[q[i].id=i].r;
    std::sort(q+1,q+m+1);
    q[0].l=1;
    for(int i=1;i<=m;++i){
        std::cout<<q[i].l<<' '<<q[i].r<<'\n';
        ans[i]=L_R[q[i].r]-L_R[q[i-1].r]+R_L[q[i].l]-R_L[q[i-1].l];
        if(q[i].r>q[i-1].r)
        R[q[i-1].l-1].push_back((node){q[i-1].r+1,q[i].r,i,-1});
        else
        if(q[i].r<q[i-1].r)
        R[q[i-1].l-1].push_back((node){q[i].r+1,q[i-1].r,i,1});
        if(q[i].l<q[i-1].l)
        L[q[i].r+1].push_back((node){q[i].l,q[i-1].l-1,i,-1});
        else
        if(q[i].l>q[i-1].l)
        L[q[i].r+1].push_back((node){q[i-1].l,q[i].l-1,i,1});
    }
    for(int i=1;i<=siz;++i){
        bL[i]=bR[i-1]+1;
        bR[i]=i*siz;
        for(int j=bL[i];j<=bR[i];++j)bel[j]=i;
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<bel[a[i]];++j)++s[j];
        for(int j=bL[bel[a[i]]];j<=a[i];++j)++c[j];
        for(node j:R[i]){
            int l=j.l,r=j.r;
            long long tmp=0;
            for(int k=l;k<=r;++k)
            tmp+=s[bel[a[k]+1]]+c[a[k]+1];
            ans[j.id]+=j.op*tmp;
            std::cout<<tmp<<"::"<<'\n';
        }
    }
    memset(c,0,sizeof c);
    memset(s,0,sizeof s);
    for(int i=n;i;--i){
        for(int j=bel[a[i]]+1;j<=siz;++j)++s[j];
        for(int j=a[i];j<=bR[bel[a[i]]];++j)++c[j];
        for(node j:L[i]){
            int l=j.l,r=j.r;
            long long tmp=0;
            for(int k=l;k<=r;++k)
            tmp+=s[bel[a[k]-1]]+c[a[k]-1];
            ans[j.id]+=j.op*tmp;
            std::cout<<tmp<<'\n';
        }
    }
    for(int i=1;i<=m;++i)ans[i]+=ans[i-1],out[q[i].id]=ans[i];
    for(int i=1;i<=m;++i)cout<<out[i];
    return 0;
}
