#include <bits/stdc++.h>
using namespace std;
namespace IO{
inline void read(int &x) {
    x = 0;
    char c = getchar();
    while('0' > c || c > '9') c = getchar();
    while('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
}
}
int main(){
    int x;
    IO::read(x);
    return 0;
}