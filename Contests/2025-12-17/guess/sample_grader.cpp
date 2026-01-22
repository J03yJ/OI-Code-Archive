#include <bits/stdc++.h>
using namespace std;
#include "guess.h"

namespace alErEHSDrU {

#define ull unsigned long long

int opcnt = 0, opsum = 0;

mt19937 rnd;
ull x[3010];
ull X;

bool Query(vector<pair<ull, ull>> a) {
    ++opcnt;
    ++opsum;
    bool ok = 0;
    for (auto i : a)
        if (i.first <= X && X <= i.second)
            ok = 1;
    return ok && (rnd() % 10 < 8);
}
void main() {
    int T = 3000;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++)
        scanf("%llu", x + i);
    rnd.seed(time(NULL));
    bool WA = 0;
    for (int i = 1; i <= T; i++) {
        X = x[i];
        opcnt = 0;
        ull r = Guess();
        if (r != X)
            WA = 1,
            printf("Wrong answer on #%d: expected %llu, returned %llu.\n", i, X,
                   r);
        else
            printf("#%d accepted: called `Query` for %d times.\n", i, opcnt);
    }
    double w = opsum * 1.0 / T, sco = 0;
    if (WA)
        printf("Wrong Answer: called `Query` for %.2f times on average.\n", w);
    else {
        double w = opsum * 1.0 / T, sco = 0;
        printf("Accepted: called `Query` for %.2f times on average.\n", w);
        if (w <= 107)
            sco = 1;
        else if (w <= 207)
            sco = 1 - sqrt(1 - (2.07 - 0.01 * w) * (2.07 - 0.01 * w));
        else
            sco = 0;
        sco *= 100;
        printf("Score: %.2f", sco);
    }
}

#undef ull

} // namespace alErEHSDrU

bool Query(vector<pair<unsigned long long, unsigned long long>> a) {
    return alErEHSDrU::Query(a);
}

int main() {
    freopen("guess.in", "r", stdin);
    freopen("guess.out", "w", stdout);
    alErEHSDrU::main();
}
