#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<bitset>
#include<queue>
#include<ctime>
#include<cmath>
#include<set>
#include<map>
#define infile(filename) freopen(filename".in","r",stdin)
#define outfile(filename) freopen(filename".out","w",stdout)
#define usefile(filename) infile(filename),outfile(filename)
using namespace std; typedef long long ll; typedef unsigned long long ull; typedef __int128 I;
namespace IO {
	const int BUF=1<<20; static char ch[BUF]={},out[BUF]={},*l=ch,*r=ch,*o=out;
#define FASTIO
#ifdef FASTIO
	inline char gc() { return (l==r&&(r=(l=ch)+fread(ch,1,BUF,stdin),l==r))?EOF:*l++; }
#else
	inline char gc() { return getchar(); }
#endif
	inline void flush() { fwrite(out,1,o-out,stdout),o=out; }
	inline void putc(char ch) { if(o==out+BUF) flush(); *o++=ch; }
	struct flusher{~flusher(){flush();}}_;
}; using IO::gc; using IO::putc;
template <typename T> void read(T &a) { static char fushu,ch; a=fushu=0; do ch=gc(); while(ch!='-'&&(ch<48||ch>57)); if(ch=='-') ch=gc(),fushu=1; do a=(a<<1)+(a<<3)+(ch^48),ch=gc(); while(ch>47&&ch<58); if(fushu) a=-a; }
template <typename T,typename ...Args> void read(T &a,Args &...args) { read(a),read(args...); }
template <typename T> void write(T a) { static char que[114]={},*p=que; if(!a) putc(48); if(a<0) putc('-'),a=-a; while(a) *p++=(a%10)^48,a/=10; while(p!=que) putc(*--p); putc(32); }
template <typename T,typename ...Args> void write(T a,Args ...args) { write(a),write(args...); }
template <typename T> void ckmax(T &a,T b) { if(a<b) a=b; }
template <typename T> void ckmin(T &a,T b) { if(b<a) a=b; }
int main()
{
	// usefile("a+b");
	int i,a,b,sum=0;
	read(a,b);
	for(i=1;i<=a;++i) ++sum;
	for(i=1;i<=b;++i) ++sum;
	putc('a'),putc('+'),putc('b'),putc('=');
	write(sum),putc('\n');
	return 0;
}
// Press Ctrl+Z after inputting.