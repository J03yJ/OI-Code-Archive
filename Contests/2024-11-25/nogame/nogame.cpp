#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>

using namespace std;

namespace IO {
	const int SIZE = (1 << 25) + 1;
	char ibuf[SIZE], *iS, *iT;
	char obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[64];
	int f, qr;
	
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	
	inline void flush () {
		fwrite (obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	inline void Put (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	template <class I> inline void Read (I &x) {
		for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;
		for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); 
		x = f == -1 ? -x : x;
	}
	template <class I> inline void Write (I x) {
		if (! x) Put ('0'); if (x < 0) Put ('-'), x = -x;
		while (x) qu[ ++ qr] = x % 10 + '0',  x /= 10;
		while (qr) Put (qu[qr -- ]);
	}
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using IO :: Read;
using IO :: Put;
using IO :: Write;

#define int long long
const int N=2e6+9;
const int P=N/10;
const int inf=2e18;
const int B=3.3e4;

int pri[N],ntp[N],cnt;
int Mul(int x,int y){
    if(!x||!y) return 0;
    else if(x<=inf/y) return x*y;
    else return inf;
}
int a[P][61];
__gnu_pbds::gp_hash_table<int,int> mp[61];
void Init(int lim){
    for(int i=2;i<=lim;i++){
        if(!ntp[i]) pri[++cnt]=i;
        for(int j=1;j<=cnt&&i*pri[j]<=lim;j++){
            ntp[i*pri[j]]=1;
            if(i%pri[j]==0) break ;
        }
    }
    for(int i=1;i<=cnt;i++){
        a[i][0]=1;
        for(int j=1;j<=60;j++) a[i][j]=Mul(a[i][j-1],pri[i]);
        if(pri[i]>B){
            for(int j=1;j<=60;j++) mp[j][a[i][j]]=pri[i];
        }
    }
}

signed main(){
    freopen("nogame.in","r",stdin);
    freopen("nogame.out","w",stdout);
    Init(2e6);

    int T;
    Read(T);
    while(T--){
        int n,k,ans=1;
        Read(n),Read(k);

        for(int i=1;i<=cnt;i++){
            if(a[i][k]>n) break ;
            if(pri[i]>B) break ;
            if(n%pri[i]) continue ;
            int tmp=0;
            while(n%pri[i]==0) n/=pri[i],tmp++;
            ans*=a[i][tmp/k];
        }
        if(mp[k][n]) ans*=mp[k][n];
        
        Write(ans),Put('\n');
    }

    return 0;
}