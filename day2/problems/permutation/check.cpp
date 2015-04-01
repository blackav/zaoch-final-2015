#include <iostream>
#include "testlib.h"

using namespace std;

int main(int argc, char **argv)
{
    registerTestlibCmd(argc, argv);

    int n = inf.readInt(1, 1000000);
    vector<int> p (n + 1);
    for (int i = 1; i <= n; ++i) {
    	p[i] = inf.readInt(1, n);
    }
    int ai = ans.readInt(-1, n);
    int aj = ans.readInt(-1, n);
    int oi = ouf.readInt(-1, n);
    int oj = ouf.readInt(-1, n);

    if (int (ai == -1) != int (aj == -1)) quitf(_fail, "Jury's output is incorrect");
    if (ai != -1 && (ai == 0 || aj == 0 || ai == aj)) quitf(_fail, "Jury's output is incorrect");

    if (int (oi == -1) != int (oj == -1)) quitf(_wa, "Participant's output is incorrect");
    if (oi != -1 && (oi == 0 || oj == 0 || oi == oj)) quitf(_wa, "Participant's output is incorrect");

    if (ai > aj) swap (ai, aj);
    if (oi > oj) swap (oi, oj);

    int i_ans = 0;
    if (ai != -1) {
	    i_ans += int (p[ai] > p[aj]) - int (p[ai] < p[aj]);
	    for (int i = ai + 1; i < aj; i++)
    		i_ans += int (p[ai] > p[i]) + int (p[i] > p[aj]) - int (p[ai] < p[i]) - int (p[i] < p[aj]);
    }

    int i_out = 0;
    if (oi != -1) {
		i_out += int (p[oi] > p[oj]) - int (p[oi] < p[oj]);
        for (int i = oi + 1; i < oj; i++) {
    		i_out += int (p[oi] > p[i]) + int (p[i] > p[oj]) - int (p[oi] < p[i]) - int (p[i] < p[oj]);
		}
	}

    if (i_ans > i_out)
    	quitf(_wa, "Participant's output is not optimal, jury = original%c%d, participant = original%c%d", i_ans > 0 ? '-' : '+', abs (i_ans), i_out > 0 ? '-' : '+', abs (i_out));

    if (i_ans < i_out)
    	quitf(_fail, "Participant's output is better than jury's, jury = original%c%d, participant = original%c%d", i_ans > 0 ? '-' : '+', abs (i_ans), i_out > 0 ? '-' : '+', abs (i_out));

    quitf(_ok, "Output is ok");

    return 0;
}
