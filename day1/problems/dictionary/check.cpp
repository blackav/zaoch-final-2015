#include "testlib.h"
#include <string>
using namespace std;
const int N = (int) 2e5 + 1;
const int D = 3;
char fmt[25];
string s, word[D]; 
int good[N], n, l, len[D];

int check(InStream& in) {
	int d = in.readInt(1, D);
	for (int i = 0; i < d; ++i) {
		word[i] = in.readWord(fmt);
		len[i] = (int) word[i].size();
	}
	for (int i = 0; i <= n; ++i)
		good[i] = (int) (i == 0);
	for (int i = 0; i < n; ++i) {
		if (!good[i]) continue;
		for (int j = 0; j < d; ++j)
			if (strncmp(s.data() + i, word[j].data(), len[j]) == 0) good[i + len[j]] = true;
	}
	if (!good[n])
		in.quitf(_wa, "the initial string can't be represented using this dictionary");
	return d;
}

int main(int argc, char ** argv) {
	registerTestlibCmd(argc, argv);
	l = inf.readInt(), s = inf.readWord(), n = (int) s.size();
	sprintf(fmt, "[a-c]{1,%d}", l);
	int contestant = check(ouf), jury = check(ans);
	if (contestant > jury)
		quitf(_wa, "contestant's answer is not optimal: %d instead of %d\n", contestant, jury);
	if (contestant < jury)
		quitf(_fail, "jury's answer is not optimal: %d instead of %d\n", jury, contestant);
	quitf(_ok, "%d words\n", jury);
	return 0;
}
