#include <bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define ll long long int
int n, block[maxn];
int odd[maxn], even[maxn];
ll sum1, sum2, sum, cnt, level;
int x[maxn];
int main(){
    freopen("brick.in", "r", stdin);
    freopen("brick.out", "w", stdout);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &block[i]), sum += block[i];
    }
    if(n & 1){
        int delta = (sum & 1);
        x[1] = -block[1];
        int flg = -1;
        for(int i = 2; i <= n; i++){
            x[1] += flg * block[i];
            flg *= -1;
        }
        x[1] = (x[1] + delta) / 2;
        for(int i = 2; i <= n; i++) x[i] = (delta - block[i]) - x[i - 1];
        nth_element(x + 1,x + (n + 1) / 2, x + n + 1);
        level = delta - 2 * x[(n + 1) / 2];
        //assert(level >= 0);
        for(int i = 1; i <= n; i++) cnt += abs(x[i] - x[(n + 1)/2]);
        printf("%lld %lld\n", level, cnt);
    }
    else{
        for(int i = 1; i <= n; i = i + 2)
            sum1 += block[i];
        sum2 = sum - sum1;
        if(sum1 != sum2){
            printf("-1 -1\n");
            return 0;
        }
        else{
            level = 0;
            x[1] = 0;
            for(int i = 2; i <= n; i++) x[i] = -block[i] - x[i - 1];
            int t = 0;
            for(int i = 1; i <= n; i = i + 2) odd[++t] = x[i];
            t = 0;
            for(int i = 2; i <= n; i = i + 2) even[++t] = x[i];
            int mid = t / 2 + 1;
            nth_element(odd + 1, odd + mid, odd + t + 1);
            nth_element(even + 1, even + mid, even + t + 1);
            for(int i = 1; i <= t; i++) cnt += abs(odd[i] - odd[mid]);
            for(int i = 1; i <= t; i++) cnt += abs(even[i] - even[mid]);
            level = -(odd[mid] + even[mid]);
            printf("%lld %lld\n", level, cnt);
        }
    }
    return 0;
}