#include "testlib.h"
#include <algorithm>
#include <cstdint>
using namespace std;

const int N = 1e5;

uint64_t f(uint64_t x) {
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	return x;
}

int main(int argc, char* argv[]) {
	registerTestlibCmd(argc, argv);
	int T=inf.readInt(1, 10);
	for(int t=1; t<=T; ++t) {
		static int a[N + 2], b[N + 2];
		int n=inf.readInt(50, N);
		for(int i=1; i<=n; ++i) a[i]=inf.readInt(1, n);
		uint64_t x=ouf.readUnsignedLong();
		for(int i=1; i<=n; ++i) {
			b[i]=i;
			x=f(x);
			swap(b[i],b[x%i+1]);
		}
		for(int i=1; i<=n; ++i)
			if(a[i]!=b[i])
				quitf(_wa, "Failed test %d", i);
	}
	quitf(_ok,"no problem");
	return 0;
}