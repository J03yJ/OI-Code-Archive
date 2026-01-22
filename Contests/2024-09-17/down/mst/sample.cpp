#include <bits/stdc++.h>

namespace IO
{
    const int P = (1ll << 31) - 1;
    int N, M, V, A, B;
    void GetSeed(int &n, int &m, int &v)
    {
        scanf("%d%d%d%d%d", &N, &M, &V, &A, &B);
        n = N, m = M, v = V;
    }
    int GetInt()
    {
        A = ((A ^ B) + (B >> 16) + (B << 16)) & P;
        B = ((A ^ B) + (A >> 16) + (A << 16)) & P;
        return (A ^ B) % V;
    }
    int GetPos()
    {
        A = ((A ^ B) + (B >> 16) + (B << 16)) & P;
        B = ((A ^ B) + (A >> 16) + (A << 16)) & P;
        return (A ^ B) % N + 1;
    }
    void GetSeg(int &l, int &r)
    {
        l = GetPos(), r = GetPos();
        if (l > r)
            std::swap(l, r);
    }
}

const int N = 2e5 + 5;

int n, m, v, a[N];

long long Solve(int l, int r)
{
    return 0;
}

int main()
{
    IO::GetSeed(n, m, v);
    for (int i = 1; i <= n; ++i)
        a[i] = IO::GetInt();
    for (int i = 1; i <= m; ++i)
    {
        int l, r;
        IO::GetSeg(l, r);
        printf("%lld\n", Solve(l, r));
    }
    return 0;
}
