#include "testlib.h"
#include <cmath>
#include <algorithm>

using std::min;

/*
long double log2(double x)
{
    return log(x) / log(2.0);
}
*/

const double eps = 1e-9;

int main(int argc, char* argv[])
{
    registerTestlibCmd(argc, argv);
    int S = inf.readInt();
    int group = inf.readInt();
    
    int iter = ouf.readInt();
    int N = ouf.readInt();
    int M = ouf.readInt();
    
    double C1 = 1.0, C2 = 1.0;
    switch (group)
    {
        case 1:
            quitf(_ok, "Group = %d, Q = %d, S = %d, log Q = %.3lf, log S = %.3lf, last: %d x %d", group, iter, S, log2(iter), log2(S), N, M);
        break; case 2:
            C1 = 2.0;
            C2 = 2.0;
        break; case 3:
            C1 = 1.5;
            C2 = 2.5;
        break; case 4:
            C1 = 1.0;
            C2 = 5.0;
        break; default:
            quitf(_fail, "No such group: %d\n", group);
    }
    
    if (log2(iter) < C1 * log2(S) + C2 + eps)
        quitf(_ok, "Group = %d, Q = %d, S = %d, log Q = %.3lf, log S = %.3lf, last: %d x %d", group, iter, S, log2(iter), log2(S), N, M);
    else
        quitf(_wa, "Group = %d, Q = %d, S = %d, log Q = %.3lf, log S = %.3lf, last: %d x %d", group, iter, S, log2(iter), log2(S), N, M);
    return 0;
}
