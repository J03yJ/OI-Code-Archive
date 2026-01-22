/*
Problem : tree
Type    : Special Judge
*/
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-9;
int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int c = inf.readInt(), T = inf.readInt(), n, q, x, k;
    long long a[15], b[15];
    bool odd = 1, eve = 1;
    auto chk = [&] {
        for(int i = 1; i <= 5; i++) {
            a[i] = ouf.readLong(), b[i] = ans.readLong();
        }
        if(a[1] == -1 && a[2] == -1 && a[3] == -1 && a[4] == -1 && a[5] == -1) {
            odd = 0;
        }
        else {
            for(int i = 1; i <= 5; i++) if(a[i] ^ b[i]) {
                quitf(_wa, "you output the wrong answer in odd line(s)");
            }
        }
        for(int i = 1; i <= 5; i++) {
            a[i] = ouf.readLong(), b[i] = ans.readLong();
        }
        if(a[1] == -1 && a[2] == -1 && a[3] == -1 && a[4] == -1 && a[5] == -1) {
            eve = 0;
        }
        else {
            for(int i = 1; i <= 5; i++) if(a[i] ^ b[i]) {
                quitf(_wa, "you output the wrong answer in even line(s)");
            }
        }
    };
    while(T--) {
        n = inf.readInt(), q = inf.readInt();
        for(int i = 1; i <= n; i++) x = inf.readInt();
        chk();
        while(q--) {
            k = inf.readInt();
            while(k--) {
                x = inf.readInt(), x = inf.readInt();
            }
            chk();
        }
    }
    if(!odd && !eve) {
        quitf(_wa, "you avoid to answer any questions");
    }
    if(!odd) {
        quitp(50, "even lines are correct");
    }
    if(!eve) {
        quitp(25, "odd lines are correct");
    }
    quitf(_ok, "accepted");
    return 0;
}