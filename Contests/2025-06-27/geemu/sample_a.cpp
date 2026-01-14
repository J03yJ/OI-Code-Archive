#include"geemu.h"
#include<bits/stdc++.h>
using namespace std;

vector < int > report(int n, int l1, int l2)
{
    vector < int > res(n + 1);
    res[0] = 114514;
    for (int i = 1;i <= n;++ i)
        res[i] = i;
    return res;
}
