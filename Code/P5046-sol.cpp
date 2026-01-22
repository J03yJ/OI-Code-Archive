// Test
#include<cstdio>
#include<cctype>
#include<algorithm>
#include<cstring>
#include<ctime>
#define N 100001
#define siz 160
class istream{
    char buf[13000003],*s;
    public:
        inline istream(){
#ifndef ONLINE_JUDGE
            freopen("input.txt","r",stdin);
#endif
            buf[fread(s=buf,1,13000001,stdin)]='\n';
        }
        template<typename T>
        inline void operator>>(T&rhs){
            for(rhs=0;!isdigit(*s);++s);
            while(isdigit(*s))rhs=rhs*10+(*s++&15);
        }
}in;
struct BiT{
    int b[N];
    inline void add(int i,int x){for(;i<N;i+=i&-i)b[i]+=x;}
    inline int ask(int i){int ret=0;for(;i;i^=i&-i)ret+=b[i];return ret;}
}t;
int n,m,a[N],L[666],R[666],bel[N],blocks,pre[N],suf[N],cnt[666][N];
long long F[666][666],ans;
int x[666],y[666],lx,ly;
int c[N],d[N];
struct Pair{
    int first,second;
    inline bool operator<(const Pair&rhs)const{return first<rhs.first;}
}b[N];
int merge(int *a,int *b,int n,int m){
    int i=1,j=1,ans=0;
    while(i<=n&&j<=m){
        if(a[i]<b[j]) i++;
        else ans+=n-i+1,j++;
    }
    return ans;
}
void init(){
    blocks=(n-1)/siz+1;
    for(int i=1;i<=blocks;++i)L[i]=R[i-1]+1,R[i]=i*siz;
    R[blocks]=n;
    for(int i=1;i<=n;++i)b[i]=(Pair){a[i],i};
    for(int i=1;i<=blocks;++i){
        std::sort(b+L[i],b+R[i]+1);
        for(int j=L[i];j<=R[i];++j)bel[j]=i,c[j]=b[j].first;
        int lst=0;
        for(int j=L[i];j<=R[i];j++){
            t.add(a[j],1);
            pre[j]=lst+=t.ask(n)-t.ask(a[j]);
        }
        for(int j=L[i];j<=R[i];j++) t.add(a[j],-1);
        F[i][i]=lst;
        lst=0;
        for(int j=R[i];j>=L[i];j--){
            t.add(a[j],1);
            suf[j]=lst+=t.ask(a[j]-1);
        }
        for(int j=R[i];j>=L[i];j--) t.add(a[j],-1);
        for(int j=L[i];j<=R[i];j++) cnt[i][a[j]]++;
        for(int j=1;j<=n;j++) cnt[i][j]+=cnt[i-1][j];
    }
    for(int i=1;i<=bel[n];i++){
        for(int j=n-1;j;j--) cnt[i][j]+=cnt[i][j+1];
    }
    for(int len=2;len<=bel[n];len++){
        for(int i=1;i<=bel[n]-len+1;i++){
            int j=i+len-1;
            F[i][j]=F[i+1][j]+F[i][j-1]-F[i+1][j-1]+merge(c+L[i]-1,c+L[j]-1,R[i]-L[i]+1,R[j]-L[j]+1);
        }
    }
}
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
int main(){
    in>>n;in>>m;
    for(int i=1;i<=n;++i)in>>a[i];
    init();
    while(m--){
        long long ll,rr;in>>ll;in>>rr;
        const int l=ll^ans,r=rr^ans,bL=bel[l],bR=bel[r];
    //    const int l=ll,r=rr,bL=bel[l],bR=bel[r];
        lx=ly=0;
        if(bL==bR){
            for(int i=L[bL];i<=R[bL];++i)
            if(l<=b[i].second&&b[i].second<=r)y[++ly]=c[i];else
            if(b[i].second<l)x[++lx]=c[i];
            ans=pre[r]-((l==L[bL])?(0):(pre[l-1]))-merge(x,y,lx,ly);
        }else{
            ans=F[bL+1][bR-1]+pre[r]+suf[l];
            const int*cR=cnt[bR-1],*cL=cnt[bL];
            for(int i=L[bL];i<=R[bL];++i)
            if(b[i].second>=l)ans+=cR[1]-cR[x[++lx]=c[i]]-cL[1]+cL[c[i]];
            for(int i=L[bR];i<=R[bR];++i)
            if(b[i].second<=r)ans+=cR[(y[++ly]=c[i])+1]-cL[c[i]+1];
            ans+=merge(x,y,lx,ly);
        }
        // cout<<ans;
    }
    return 0;
}