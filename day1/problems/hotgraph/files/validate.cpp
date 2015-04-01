#include <cstdio>
#include "testlib.h"
using namespace std;

const int N = 100 * 1000;
const int M = 1000 * 1000;
const int T = 1000 * 1000 * 1000;
const int Q = 10;

int main()
{
    registerValidation();
    int n = inf.readInt(1, N);
    inf.readSpace();
    int m = inf.readInt(1, M);
    inf.readEoln();
    int last_t = -T - 1;
    for (int i = 0; i < m; i++)
    {
        int a = inf.readInt(1, n);
        inf.readSpace();
        int b = inf.readInt(1, n);
        inf.readSpace();
        int t = inf.readInt(-T, T);
        quitif(last_t > t, _fail, "temperatures should form a non-decreasing sequence (i = %d)", i);
        last_t = t;
        inf.readEoln();
    }
    int q = inf.readInt(1, Q);
    inf.readEoln();
    for (int i = 0; i < q; i++)
    {
        int a = inf.readInt(1, n);
        inf.readSpace();
        int b = inf.readInt(1, n);
        inf.readSpace();
        int d = inf.readInt(0, 2 * T);
        inf.readEoln();
    }
    inf.readEof();
}
