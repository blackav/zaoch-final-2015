#include "testlib.h"

#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#include <climits>
#include <iostream>

using namespace std;

int dx[255];
int dy[255];


const int MORE_THAN_MAX_ITER = 200 * 1000 + 1;


int main(int argc, char* argv[])
{
    registerInteraction(argc, argv);

    dx['R'] = 1;
    dx['L'] = -1;
    dy['U'] = 1;
    dy['D'] = -1;

    
    
    //int n = inf.readInt();
    //int m = inf.readInt();
    int S = inf.readInt(); //n * m;
    vector <int> d;
    for (int i = 1; i * i <= S; ++i)
    {
        if (S % i == 0)
        {
            d.push_back(i);
            if (i != S / i)
                d.push_back(S / i);
        }
    }
    int dc = d.size();
    
    vector <vector <vector <bool> > > f(dc);
    vector <pair<int, int> > nms(dc);
    vector <pair<int, int> > pos(dc, make_pair(0, 0));
    vector <int> freeCells(dc);
    for (int i = 0; i < dc; ++i)
    {
        nms[i] = make_pair(d[i], S / d[i]);
        f[i] = vector <vector <bool> > (d[i], vector <bool> (S / d[i], 0));
        f[i][0][0] = 1;
        freeCells[i]  = S - 1;
    }
    
    

    pair<int, int> last = make_pair(1, S);
    int iter = 0;
    string s;
    while (true)
    {
        s = ouf.readToken();
        ++iter;
        if (iter == MORE_THAN_MAX_ITER)
        {
            cout << iter << endl;
            tout << last.first << " " << last.second << endl;
            printf("E\n");
            fflush(stdout);
            quitf(_wa, "Too many moves.\n");
        }
        if (s[0] != 'U' && s[0] != 'D' && s[0] != 'L' && s[0] != 'R')
        {
            printf("E\n");
            fflush(stdout);
            quitf(_pe, "Can't recognize move %c.\n", s[0]);
        }
        bool everything = true;
        for (int i = 0; i < dc; ++i)
        {
            pos[i].first += dx[s[0]];
            if (pos[i].first == nms[i].first)
                pos[i].first = 0;
            if (pos[i].first < 0)
                pos[i].first = nms[i].first - 1;
            
            pos[i].second += dy[s[0]];
            if (pos[i].second == nms[i].second)
                pos[i].second = 0;
            if (pos[i].second < 0)
                pos[i].second = nms[i].second - 1;
            
            freeCells[i] -= (1 - f[i][pos[i].first][pos[i].second]);
            f[i][pos[i].first][pos[i].second] = 1;
            if (freeCells[i])
            {
                last = nms[i];
                everything = false;
            }
        }
        if (everything)
        {
            printf("Y\n");
            fflush(stdout);
            tout << iter << endl;
            tout << last.first << " " << last.second << endl;
            quitf(_ok, "Cake found in %d moves.\n", iter);
        }
        printf("N\n");
        fflush(stdout);
    }
    return 0;
}
