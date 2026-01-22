#include "testlib.h"
 
#include <string>
 
using namespace std;

pattern pnum("0|[1-9][0-9]*");
 
bool isNumeric(const string& p) {
    return pnum.matches(p);
}
bool check(const string& ja, const string& pa, int mod) {
    long long ja_mod = 0, pa_mod = 0;
    for (int i = 0; i < ja.size(); i++) ja_mod = (ja_mod * 10 + (ja[i] - '0')) % mod;
    for (int i = 0; i < pa.size(); i++) pa_mod = (pa_mod * 10 + (pa[i] - '0')) % mod;
    return ja_mod == pa_mod;
}
int main(int argc, char * argv[]) {
    setName("compare two signed huge integers");
    registerTestlibCmd(argc, argv);
    
    int c = inf.readInt();
    int T = inf.readInt();

    bool correct = 1;
    bool partial_correct = 1;

    for (int i = 0; i < T; i++) {
        string ja = ans.readWord();
        string pa = ouf.readWord();
    
        if (!isNumeric(ja))
            quitf(_fail, "answer is not a valid nonnegative integer");
        
        if (!isNumeric(pa))
            quitf(_pe, "your answer is not a valid nonnegative integer");

        if (pa.size() > 1024)
            quitf(_pe, "your answer is too long (longer than 1024 characters)");
    
        if (!check(ja, pa, 1000000007))
            correct = 0;

        if (!check(ja, pa, 4))
            partial_correct = 0;
    }

    if (!ans.seekEof())
        quitf(_fail, "expected exactly %d token in the answer file", T);

    if (correct) 
        quitf(_ok, "Asuka, your answer is correct (when mod 1000000007)");

    if (partial_correct)
        quitp(0.2, "Minato, your answer is partially correct (when mod 4)");
    
    quitf(_wa, "your answer is incorrect");
    
}
