#include "testlib.h"

const int N_MIN = 1;
const int N_MAX = 100000;
const int Q_MIN = 1;
const int Q_MAX = 100000;
const int COLOR_MIN = -1000000000;
const int COLOR_MAX = +1000000000;

int main()
{
    registerValidation();

    int n = inf.readInt(N_MIN, N_MAX);
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(COLOR_MIN, COLOR_MAX);
        if (i == n - 1) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    int q = inf.readInt(Q_MIN, Q_MAX);
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        inf.readInt(1, n);
        inf.readSpace();
        inf.readInt(COLOR_MIN, COLOR_MAX);
        inf.readEoln();
    }

    inf.readEof();

    return 0;
}
