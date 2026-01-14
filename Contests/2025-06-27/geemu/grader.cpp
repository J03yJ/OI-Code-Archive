#include"geemu.h"
#include<bits/stdc++.h>
using namespace std;

const int N = 1009;

namespace 
{
    int p[N], l1, l2, n;
}

int s1, s2;

int mp[N];

int ask(int l, int r)
{
    ++ s1;
    int ans = r - l + 1;
    for (int i = l;i <= r;++ i)
        ans -= mp[::p[i] - 1] + mp[::p[i] + 1], mp[::p[i]] = 1;
    for (int i = l;i <= r;++ i)
        mp[::p[i]] = 0;
    return ans;
}

void swp(int x, int y)
{
    ++ s2;
    swap(::p[x], ::p[y]);
}

int main()
{
    string s;
    cin >> s;
    scanf("%d%d%d", &::n, &::l1, &::l2);
    for (int i = 1;i <= ::n;++ i)
        scanf("%d", &::p[i]);
    vector < int > res = report(::n, ::l1, ::l2);
    if ((int)res.size() != ::n + 1)
    {
        puts("用户的答案 vector 长度错误");
        return 1;
    }
    int ans = 0;
    for (int ty : {0, 1})
    {
        int fl = 0;
        for (int i = 1;i <= n;++ i)
            fl |= (ty ? (::p[i] != res[i]) : (n - ::p[i] + 1 != res[i]));
        if (!fl)
            ans = 1;
    }
    if (!ans)
    {
        puts("用户答案错误。");
        puts("用户的答案: ");
        for (int i = 1;i <= n;++ i)
            printf("%d ", res[i]);
        puts("\n通过用户操作2 后的答案");
        for (int i = 1;i <= n;++ i)
            printf("%d ", ::p[i]);
        printf("\n");
        return 3;
    }
    int f1 = (s1 > ::l1), f2 = (s2 > ::l2);
	printf("s1 : %d, s2 : %d\n", s1, s2);
    if (f1 && f2)
    {
        puts("用户操作 1, 操作 2 次数都超过限制。");
        return 4;
    }
    else if (f1)
    {
        puts("用户操作 1 次数超过限制。");
        return 5;    
    }
    else if (f2)
    {
        puts("用户操作 2 次数超过限制。");
        return 6;
    }
    puts("可以接受的答案。");


    return 0;
}
