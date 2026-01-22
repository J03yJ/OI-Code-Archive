#include<bits/stdc++.h>

using namespace std;

ifstream fin("perm.in");
ofstream fout("perm.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e5+9;

int a[N],pos[N],r[N],n;
bool Check(uint64_t x){
    for(int i=1;i<=n;i++){
        x^=x<<13;
        x^=x>>7;
        x^=x<<17;
        if(x%i+1!=r[i]) return 0;
    }
    return 1;
}

struct Mat{
    uint64_t c[64];
    Mat(){memset(c,0,sizeof c);}
    uint64_t& operator [](int pos){return c[pos];}
    Mat operator ^(Mat x){
        Mat res;
        for(int i=0;i<64;i++) res[i]=c[i]^x[i];
        return res;
    }
    Mat operator <<(int k){
        Mat res;
        for(int i=k;i<64;i++) res[i]=c[i-k];
        return res;
    }
    Mat operator >>(int k){
        Mat res;
        for(int i=k;i<64;i++) res[i-k]=c[i];
        return res;
    }
}m[N];

inline uint64_t Solve(vector<uint64_t> &a,vector<uint64_t> &b){
    uint64_t res=0;
    for(int i=0,it=0;i<64;i++){
        int pos=-1;
        for(int j=it;j<a.size();j++){
            if(a[j]>>i&1){
                pos=j;
                break ;
            }
        }
        if(!~pos) continue ;
        else swap(a[it],a[pos]),swap(b[it],b[pos]),res|=1ull<<i;
        for(int j=it+1;j<a.size();j++) if(a[j]>>i&1) a[j]^=a[it],b[j]^=b[it];
        it++;
    }
    return res;
}
inline uint64_t Find(){
    vector<uint64_t> p,q;
    for(int i=1;i<=n;i++){
        for(int k=0;~i>>k&1;k++){
            p.push_back(m[i][k]);
            q.push_back(r[i]-1>>k&1);
        }
    }
    uint64_t tmp=Solve(p,q);
    int cnt=64-__builtin_popcountll(tmp);
    vector<int> s,t;
    for(int i=0;i<64;i++){
        if(~tmp>>i&1) t.push_back(i);
        else s.push_back(i);
    }
    for(int sta=0;sta<(1<<cnt);sta++){
        uint64_t x=0;
        for(int i=0;i<cnt;i++){
            if(sta>>i&1) x|=1ull<<t[i];
        }
        for(int i=63-cnt;~i;i--){
            x|=uint64_t((__builtin_popcountll(x&p[i])&1)^q[i])<<s[i];
        }
        if(Check(x)) return x;
    }
    return -1;
}

signed main(){
    int T;
    cin>>T;
    for(int i=0;i<64;i++) m[0][i]=1ull<<i;
    for(int i=1;i<=1e5;i++){
        m[i]=m[i-1];
        m[i]=m[i]^(m[i]<<13);
        m[i]=m[i]^(m[i]>>7);
        m[i]=m[i]^(m[i]<<17);
    }
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];

        for(int i=1;i<=n;i++) pos[a[i]]=i;
        for(int i=n;i>=1;i--){
            r[i]=pos[i];
            swap(a[pos[i]],a[i]);
            swap(pos[a[pos[i]]],pos[i]);
        }

        cout<<Find()<<endl;
    }

    return 0;
}