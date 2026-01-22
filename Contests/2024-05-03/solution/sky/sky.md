# sky

## 前言

本题是签到题。

无论通过 打表，观察大样例等方法，都可以很容易的发现答案不大。

希望选手能通过这样的方式省去数学分析的时间。

## Subtask1

只有二操作，模拟即可。

## Subtask2

可以通过暴力打表或其他乱搞通过。

## Subtask3

首先放过了写了正解但不开 int128 的人。

其次考虑到有些人搜索中预估了较大的界，而被卡常的结果。

## Subtask4

我们考虑先求出第一个答案，即最小变成多少。

我们考察第二个操作，即 "数位和操作" 。

~~（由小学数学知识）~~ 容易想到其满足 $x' \equiv x\pmod 9$ 也就是说二操作并不改变其对 $9$ 的余 。

而第二个操作最多做 $4$ 次就会不可操作。

容易想到将第一个操作也放在 $\bmod 9$ 的剩余系下考虑，那我们现在可以忽略二操作的影响 。

假设执行了 $p$ 次一操作，容易知道 $x$ 最后为：$d^p \bmod 9$ ，且 $d$ 显然可以直接先与 $9$ 取模

下文 $\delta_p(d)$ 表示 $d$ 在 模 $p$ 意义下的阶。

如果不清楚阶的定义，请查阅 [oiwiki](https://oiwiki.org/math/number-theory/primitive-root/)

我们先考虑与 $9$ 互质的那些 $d$，显然当 $p \geq \delta_9(d)$ 时，操作就没有意义了，此时总操作次数最多 $\delta_9(d)+4 \leq 13$

再考虑少数与 $9$ 不互质的 $d$，会发现其乘几轮之后 $d^p \equiv 0 \pmod 9$ 接下来的就都没有意义了，操作次数显然也 $< 13$

所以有效的操作次数至多 $13$ 次，这启发我们可以暴搜出答案。

具体的，最好先把第一个答案算出来，然后暴搜第二个方案。

```cpp
#include <bits/stdc++.h>
#define For(i, a, b) for(register int i = (a); i <= (b); ++i)
#define Rof(i, a, b) for(register int i = (a); i >= (b); --i)
#define For_Edge(i, x) for(auto i : edge[x])
#define For_Mul(i, a, b) for(register int i = (a); i <= (b); i += (a))
#define Zero(a) memset((a), 0, sizeof(a))
#define Size(a) (int)((a).size())
#define fi first
#define se second
#define pii pair <int, int>
#define eb emplace_back
#define pb push_back
#define mp make_pair
using namespace std;
inline long long read() {
    long long x = 0;
    char c = getchar();
    bool f = 0;
    while(!isdigit(c)) f |= (c == '-'), c = getchar();
    while(isdigit(c)) x = (x * 10) + (c ^ 48), c = getchar();
    return f ? -x : x;
}
void write(int x) {
    if(x < 0) { x = -x; putchar('-'); }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
inline void Checkmin(int &x, int y) { x = x < y ? x : y; }
inline void Checkmax(int &x, int y) { x = x > y ? x : y; }
const int maxn = 15;
int T, d[maxn], Answer;
long long x, K;
inline int Sum(__int128 x) {
    long long sum = 0;
    while(x) sum += x % 10, x /= 10;
    return sum;
}
inline int Solve(__int128 x) { 
    int Cnt = 0;
    while(x > 9) Cnt++, x = Sum(x);
    return Cnt;
}
inline void Search(int S, __int128 x) {
    if(S > d[Answer]) return;
    if(x < 10) { d[x] = min(d[x], S); return; }
    Search(S + 1, Sum(x)), Search(S + 1, x * K);
}
signed main() {
    freopen("sky.in", "r", stdin);
    freopen("sky.out", "w", stdout);
    T = read();
    while(T--) {
        x = read(), K = read();
        memset(d, 0x3f, sizeof(d));
        __int128 p = x;
        For(i, 0, 8) {
            d[(p - 1) % 9 + 1] = min(d[(p - 1) % 9 + 1], i + Solve(p));
            p = p * K;
        }
        For(i, 1, 9)
            if(d[i] < 1e6) { Answer = i; break; }
        Search(0, x);
        printf("%d %d\n", Answer, d[Answer]);
    }
  return 0;
}
```